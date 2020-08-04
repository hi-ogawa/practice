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


def run_cpp(file, option, check, test_infile, test_outfile, no_pch):
    compiler = "clang++"
    default_option = "-std=c++17 -O2 -march=native -Wall -Wextra -Wshadow"
    exec_file = "./build/main"
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

    if test_infile:
        print(f":: Running test ({test_infile})")
        with open(test_infile) as f:
            proc = subprocess.Popen(exec_file, stdin=f, stdout=PIPE)
            proc_stdout, proc_stderr = proc.communicate()
            proc_outp = proc_stdout.decode()
            if not test_outfile:
                print(proc_outp)
        return

    tests = find_tests(file)
    for i, (inp, outp) in enumerate(tests):
        print(f":: Running test ({i + 1})")
        proc = subprocess.Popen(exec_file, stdin=PIPE, stdout=PIPE)
        proc_stdout, proc_stderr = proc.communicate(input=bytes(inp, "utf-8"))
        if proc.returncode != 0:
            print(f":: returncode: {proc.returncode}")  # e.g. -11 for segfault
            print(proc_stdout.decode())
            continue
        proc_outp = proc_stdout.decode()
        if not check:
            print(proc_outp)
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
    parser.add_argument("--option", type=str)
    parser.add_argument("--check", action="store_true", default=False)
    parser.add_argument("--test-infile", type=str)
    parser.add_argument("--test-outfile", type=str)
    parser.add_argument("--no-pch", action="store_true", default=False)
    args = parser.parse_args()
    run_cpp(**args.__dict__)


if __name__ == "__main__":
    main()
