import re
import subprocess
from subprocess import PIPE, STDOUT
import argparse
import timeit
import os.path
from typing import Any


def find_inline_tests(file):
    with open(file) as f:
        s = f.read()
    ls = re.finditer("%%%% begin\n(.*?)%%%%\n(.*?)%%%% end", s, re.DOTALL)
    tests = [m.groups() for m in ls]
    return tests


def monitor_memory_usage(proc, mem_info):
    # Monkey patch "Popen" instance to read /proc/<pid>/status before process exiting
    # (cf. https://github.com/python/cpython/blob/3.8/Lib/subprocess.py#L1772)
    # TODO: sometimes we get a weird number especially when running debug build (something like "21474904184 kB")
    method_name = "_remaining_time"  # This seems to be a good choice since it's called during "select" loop
    proc_file = f"/proc/{proc.pid}/status"
    old_method = getattr(proc, method_name)

    def new_method(self, *args):
        if os.path.isfile(proc_file):
            m = re.search("VmPeak:(.*)", open(proc_file).read())
            if m:
                mem_info[0] = m.group(1).strip()
        return old_method(*args)

    setattr(proc, method_name, new_method.__get__(proc))


def run_test(
    popen_kwargs: dict[str, Any],
    name,
    inp,
    outp,
    check,
    timeout,
    truncate,
    coverage,
) -> None:
    print(f":: Running test ({name})")
    time_begin = timeit.default_timer()
    # TODO: stderr included in stdout?
    proc = subprocess.Popen(**popen_kwargs, stdin=PIPE, stdout=PIPE, stderr=STDOUT)
    mem_info = [None]
    monitor_memory_usage(proc, mem_info)
    try:
        proc_stdout, *_ = proc.communicate(input=bytes(inp, "utf-8"), timeout=timeout)
    except subprocess.TimeoutExpired:
        proc.kill()
        print(f":: Timeout ({timeout}s). Process killed.")
        print(proc.stdout.read().decode())
        return
    time_end = timeit.default_timer()
    print(
        f":: exit: {proc.returncode}, time: {time_end - time_begin:.4f}, memory: {mem_info[0]}"
    )
    if coverage:
        print(f":: Generating coverage report")
        info_file = "./build/coverage.info"
        genhtml_dir = "./build/coverage.genhtml"
        command1 = f"lcov -c -d . -o {info_file}"
        command2 = f"genhtml {info_file} -o {genhtml_dir}"
        subprocess.run(command1, shell=True, check=True, capture_output=True)
        subprocess.run(command2, shell=True, check=True, capture_output=True)
        print(f":: Finished [{os.path.abspath(genhtml_dir)}/index.html]")
        return
    proc_outp = proc_stdout.decode()
    if truncate:
        proc_outp = proc_outp[:truncate] + f" [truncate={truncate}]"
    if proc.returncode != 0:
        print(proc_outp)
        return
    if not check:
        print(proc_outp)
        return
    if proc_outp == outp:
        print(":: Check success")
        return
    print(":: Check failed")
    print(":::: EXPECTED")
    print(outp)
    print(":::: ACTUAL")
    print(proc_outp)


def build_cpp(
    file: str,
    check: bool,
    test: str,
    no_pch: bool,
    no_run: bool,
    exec_file: str,
    debug: bool,
    timeout: float,
    truncate: int,
    coverage: bool,
) -> dict[str, Any]:
    compiler = "clang++"
    default_option = "-std=c++17 -Wall -Wextra -Wshadow -Wno-missing-braces"
    options = []

    if debug:
        pch_file = "./build/pch.hpp.gch-debug"
        options.append("-g -DDEBUG -fsanitize=address -fsanitize=undefined")
        options.append(
            "--rtlib=compiler-rt -lgcc_s"
        )  # Workaround clang's int128 bug (cf. https://bugs.llvm.org/show_bug.cgi?id=16404)
    elif coverage:
        compiler = "g++"  # Use gcc since lcov is not completely compatible with clang
        no_pch = True
        options.append(f"-g --coverage")
    else:
        pch_file = "./build/pch.hpp.gch"
        options.append("-O2 -march=native")

    if compiler == "clang++":
        options.append("-fcolor-diagnostics")

    if not no_pch:
        options.append(f"-include-pch {pch_file}")

    options.append(f"-o {exec_file} {file}")
    command = " ".join([compiler, default_option] + options)

    print(f":: Compiling... [{command}]")
    time_begin = timeit.default_timer()
    proc = subprocess.run(command, shell=True, stdout=PIPE, stderr=STDOUT)
    time_end = timeit.default_timer()

    if proc.returncode != 0:
        print(":: Compile failure")
        print(proc.stdout.decode())
        raise RuntimeError("Compile failure")

    print(f":: Compile success (time: {time_end - time_begin:.4f})")
    if proc.stdout:  # Compile warning if any
        print(proc.stdout.decode())

    return dict(args=exec_file)


def build_py(
    file: str,
    check: bool,
    test: str,
    no_pch: bool,
    no_run: bool,
    exec_file: str,
    debug: bool,
    timeout: float,
    truncate: int,
    coverage: bool,
) -> list[str]:
    args = ["python", file]
    env = dict(DEBUG="1") if debug else None
    return dict(args=args, env=env)


def run(
    file: str,
    check: bool,
    test: str,
    no_pch: bool,
    no_run: bool,
    exec_file: str,
    debug: bool,
    timeout: float,
    truncate: int,
    coverage: bool,
) -> None:
    if file.endswith(".cpp"):
        build = build_cpp
    elif file.endswith(".py"):
        build = build_py
    else:
        raise RuntimeError("Unsuported file: {file}")
    popen_args = build(
        file,
        check,
        test,
        no_pch,
        no_run,
        exec_file,
        debug,
        timeout,
        truncate,
        coverage,
    )

    if no_run:
        return

    if test.startswith("inline:"):
        test = test[len("infile:") :]
        inline_tests = find_inline_tests(file)
        if test == "all":
            selected = list(range(len(inline_tests)))
        else:
            selected = [int(x) for x in test.split(",")]
        print(f":: Run inline tests: {selected}")
        for i, (inp, outp) in enumerate(inline_tests):
            if not i in selected:
                continue
            run_test(
                popen_args,
                f"inline:{i}",
                inp,
                outp,
                check,
                timeout,
                truncate,
                coverage,
            )
        return

    if test.startswith("file:"):
        test = test[len("file:") :]
        infile, outfile = test.split(":") if ":" in test else [test, None]
        inp = open(infile).read()
        outp = open(outfile).read() if outfile else ""
        run_test(
            popen_args,
            f"{infile}, {outfile}",
            inp,
            outp,
            check,
            timeout,
            truncate,
            coverage,
        )
        return

    raise RuntimeError(f"Found unsupported test: {test}")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("file", type=str)
    parser.add_argument("--check", action="store_true", default=False)
    parser.add_argument(
        "--test",
        type=str,
        default="inline:all",
        help='e.g. "inline:all", "inline:0,1,2", "file:in.txt:out.txt"',
    )
    parser.add_argument("--no-pch", action="store_true", default=False)
    parser.add_argument("--no-run", action="store_true", default=False)
    parser.add_argument("--exec-file", type=str, default="./build/main")
    parser.add_argument("--debug", action="store_true", default=False)
    parser.add_argument("--coverage", action="store_true", default=False)
    parser.add_argument("--timeout", type=float, default=5)
    parser.add_argument("--truncate", type=int, default=None)
    args = parser.parse_args()
    run(**args.__dict__)


if __name__ == "__main__":
    main()
