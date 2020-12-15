#!/bin/bash

DIR=$(dirname $BASH_SOURCE)

python misc/run.py $DIR/main_v2.cpp --no-run || exit 1
python misc/run.py $DIR/brute.cpp --no-run --exec-file=./build/brute || exit 1

for ((i = 1; ; i++)); do
  echo $i
  # python $DIR/generate.py 1 2 10 20 $i > $DIR/test-in.txt || exit 1
  python $DIR/generate.py 10 11 100000 200000 $i > $DIR/test-in.txt || exit 1
  ./build/main < $DIR/test-in.txt > $DIR/test-out.txt || break
  ./build/brute < $DIR/test-in.txt > $DIR/test-out-brute.txt || break
  diff $DIR/test-{out,out-brute}.txt || break
done
