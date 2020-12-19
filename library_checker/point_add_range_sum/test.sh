#!/bin/bash

DIR=$(dirname $BASH_SOURCE)

python misc/run.py $DIR/main_v2.cpp --no-run || exit 1

for ((i = ${SEED:-0}; ; i++)); do
  echo $i
  # python $DIR/generate.py 1000 2000 1000 2000 1000 2000 $i > $DIR/test-in.txt || exit 1
  # python $DIR/generate.py 100000 200000 1000 2000 1000 2000 $i > $DIR/test-in.txt || exit 1
  python $DIR/generate.py 500000 500001 500000 500001 0 1000000000 $i > $DIR/test-in.txt || exit 1
  TIME_BEGIN=$(date +%s.%N)
  ./build/main < $DIR/test-in.txt > $DIR/test-out.txt || break
  TIME_END=$(date +%s.%N)
  [ -n "$SHOW_TIME" ] && python -c "print('time : {:.5f}'.format(${TIME_END} - ${TIME_BEGIN}))"
done
