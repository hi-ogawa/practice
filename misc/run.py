import re
import subprocess
from subprocess import PIPE, STDOUT
import argparse
import io


def find_inline_tests(file):
    with open(file) as f:
        s = f.read()
    ls = re.finditer("%%%% begin\n(.*?)%%%%\n(.*?)%%%% end", s, re.DOTALL)
    tests = [m.groups() for m in ls]
    return tests


def test_cpp(exec_file, name, inp, outp, check):
    print(f":: Running test ({name})")
    proc = subprocess.Popen(exec_file, stdin=PIPE, stdout=PIPE)
    # TODO: print before process exits (so that we can debug infinite loop etc...)
    try:
        proc_stdout, proc_stderr = proc.communicate(
            input=bytes(inp, "utf-8"), timeout=2.0
        )
    except subprocess.TimeoutExpired:
        proc.kill()
        print(f":: Timeout. Process killed.")
        print(proc.stdout.read().decode())
        return
    proc_outp = proc_stdout.decode()
    if proc.returncode != 0:
        print(f":: returncode: {proc.returncode}")  # e.g. -11 for segfault
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


def run_cpp(file, option, check, test, no_pch, no_run, exec_file):
    compiler = "clang++"
    default_option = "-std=c++17 -O2 -march=native -Wall -Wextra -Wshadow"
    pch_file = "./build/pch.hpp.gch"
    command = f"{compiler} {default_option} -o {exec_file} {file}"
    if option:
        command += f" {option}"
    if not no_pch:
        command += f" -include-pch {pch_file}"

    print(f":: Compiling... [{command}]")
    proc = subprocess.run(command, shell=True, stdout=PIPE, stderr=STDOUT)

    if proc.returncode != 0:
        print(":: Compile failure")
        print(proc.stdout.decode())
        return

    print(":: Compile success")
    if proc.stdout:  # Compile warning if any
        print(proc.stdout.decode())

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
            test_cpp(exec_file, f"inline:{i}", inp, outp, check)
        return

    if test.startswith("file:"):
        test = test[len("file:") :]
        infile, outfile = test.split(":") if ":" in test else [test, None]
        inp = open(infile).read()
        outp = open(outfile).read() if outfile else ""
        test_cpp(exec_file, f"{infile}, {outfile}", inp, outp, check)
        return

    raise RuntimeError(f"Found unsupported test: {test}")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("file", type=str)
    parser.add_argument("--option", type=str)
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
    args = parser.parse_args()
    run_cpp(**args.__dict__)


if __name__ == "__main__":
    main()
