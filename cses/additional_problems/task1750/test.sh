#!/bin/bash

# Usage:
#   bash cses/additional_problems/task1750/test.sh

DIR=$(dirname $BASH_SOURCE)
python misc/run.py $DIR/main.cpp --no-run
python misc/run.py $DIR/brute.cpp --no-run --exec-file=./build/brute

for ((i = 1; ; i++)); do
  echo $i
  python $DIR/generate.py $i > ./build/in.txt || break
  ./build/main < ./build/in.txt > ./build/out.txt || break
  ./build/brute < ./build/in.txt > ./build/out-brute.txt || break
  diff build/out.txt build/out-brute.txt || break
done
