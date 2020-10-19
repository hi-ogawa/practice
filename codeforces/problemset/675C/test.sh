#!/bin/bash

DIR=$(dirname $BASH_SOURCE)

python misc/run.py $DIR/main.cpp --no-run || exit 1
# python misc/run.py $DIR/brute.cpp --no-run --exec-file=./build/brute || exit 1
# python misc/run.py $DIR/check.cpp --no-run --exec-file=./build/check || exit 1

for ((i = 1; ; i++)); do
  echo $i
  python $DIR/generate.py $i > $DIR/test-in.txt || exit 1
  TIME_BEGIN=$(date +%s.%N)
  ./build/main < $DIR/test-in.txt > $DIR/test-out.txt || break
  TIME_END=$(date +%s.%N)
  # python -c "print('time : {:.5f}'.format(${TIME_END} - ${TIME_BEGIN}))"
  # ./build/brute < $DIR/test-in.txt > $DIR/test-out-brute.txt || break
  # diff $DIR/test-{out,out-brute}.txt || break
  # ./build/check $DIR/test-{in,out,out-brute}.txt || break
done
