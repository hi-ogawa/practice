#!/bin/bash

DIR=$(dirname $BASH_SOURCE)

python misc/run.py $DIR/main.cpp --no-run || exit 1
python misc/run.py $DIR/brute.cpp --no-run --exec-file=./build/brute || exit 1

for ((i = 1; ; i++)); do
  echo $i
  # python $DIR/generate.py 1 2 0 10 0 3 1 10 $i > $DIR/test-in.txt || exit 1
  # python $DIR/generate.py 10 20 0 1000000 0 3 1 1000000 $i > $DIR/test-in.txt || exit 1
  # python $DIR/generate.py 10 20 0 4 0 4 1 1000000000 $i > $DIR/test-in.txt || exit 1
  python $DIR/generate.py 5 6 0 1000000000 0 1000000000 1 1000000000 $i > $DIR/test-in.txt || exit 1
  ./build/main < $DIR/test-in.txt > $DIR/test-out.txt || break
  # ./build/brute < $DIR/test-in.txt > $DIR/test-out-brute.txt || break
  # diff $DIR/test-{out,out-brute}.txt || break
done
