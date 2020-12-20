#!/bin/bash

DIR=$(dirname $BASH_SOURCE)

python misc/run.py $DIR/main_v2.cpp --no-run || exit 1
python misc/run.py $DIR/brute.cpp --no-run --exec-file=./build/brute || exit 1

for ((i = ${SEED:-0}; ; i++)); do
  echo $i
  python $DIR/generate.py 1000 2000 1000 2000 $i > $DIR/test-in.txt || exit 1
  ./build/brute < $DIR/test-in.txt > $DIR/test-out-brute.txt || break
  ./build/main < $DIR/test-in.txt > $DIR/test-out.txt || break
  diff $DIR/test-{out,out-brute}.txt || break
done
