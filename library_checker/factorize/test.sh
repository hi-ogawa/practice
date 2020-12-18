#!/bin/bash

DIR=$(dirname $BASH_SOURCE)
SEED=${1:-0}

python misc/run.py $DIR/main_v2.cpp --no-run || exit 1
python misc/run.py $DIR/main.cpp --no-run --exec-file=./build/brute || exit 1

for ((i = $SEED; ; i++)); do
  echo $i
  python $DIR/generate.py 1 2 $(( 10 ** 16 )) $(( 2 * 10 ** 16 )) $i > $DIR/test-in.txt || exit 1
  ./build/brute < $DIR/test-in.txt > $DIR/test-out-brute.txt || break
  ./build/main < $DIR/test-in.txt > $DIR/test-out.txt || break
  diff $DIR/test-{out,out-brute}.txt || break
done
