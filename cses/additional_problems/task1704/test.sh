#!/bin/bash

python misc/run.py cses/additional_problems/task1704/main.cpp --no-run
python misc/run.py cses/additional_problems/task1704/check.cpp --no-run --exec-file=./build/check

for ((i = 1; ; i++)); do
    echo $i
    python cses/additional_problems/task1704/generate.py $i > ./build/in.txt
    ./build/main < ./build/in.txt > ./build/out.txt
    ./build/check ./build/in.txt ./build/out.txt || break
done
