#!/bin/bash

DIR=$(dirname $BASH_SOURCE)

python misc/run.py $DIR/main.cpp --no-run || exit 1

for ((i = 1; ; i++)); do
  echo $i
  python $DIR/generate.py 40000 50000 40000 50000 40000 50000 $i > $DIR/test-in.txt || exit 1
  TIME_BEGIN=$(date +%s.%N)
  ./build/main < $DIR/test-in.txt > $DIR/test-out.txt || break
  TIME_END=$(date +%s.%N)
  python -c "print('time : {:.5f}'.format(${TIME_END} - ${TIME_BEGIN}))"
done
