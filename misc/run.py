import re
import subprocess
from subprocess import PIPE, STDOUT
import argparse
import io


def find_tests(file):
    with open(file) as f:
        s = f.read()
    ls = re.finditer("%%%% begin\n(.*?)%%%%\n(.*?)%%%% end", s, re.DOTALL)
    tests = [m.groups() for m in ls]
    return tests


def run_cpp(file, option, check):
    exec_file = "./build/main"
    default_command = (
        f"clang++ -std=c++17 -O2 -march=native -Wall -Wextra -o {exec_file}"
    )
    command = " ".join([default_command, option, file])

    print(f":: Compiling... [{command}]")
    proc = subprocess.run(command, shell=True, stdout=PIPE, stderr=STDOUT)

    if proc.returncode != 0:
        print(":: Compile failure")
        print(proc.stdout.decode())
        return

    print(":: Compile success")
    tests = find_tests(file)
    for i, (inp, outp) in enumerate(tests):
        print(f":: Running test ({i + 1})")
        proc = subprocess.Popen(exec_file, stdin=PIPE, stdout=PIPE)
        proc_stdout, proc_stderr = proc.communicate(input=bytes(inp, "utf-8"))
        proc_outp = proc_stdout.decode()
        if not check:
            print(proc_stdout.decode(), end="")
            continue
        if proc_outp == outp:
            print(":: Check success")
            continue
        print(":: Check failed")
        print(":::: EXPECTED")
        print(outp)
        print(":::: ACTUAL")
        print(proc_outp)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("file", type=str)
    parser.add_argument("--option", type=str, default="")
    parser.add_argument("--check", action="store_true", default=False)
    args = parser.parse_args()
    run_cpp(**args.__dict__)


if __name__ == "__main__":
    main()
