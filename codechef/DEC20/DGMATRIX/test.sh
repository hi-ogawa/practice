#!/bin/bash

DIR=$(dirname $BASH_SOURCE)

python misc/run.py $DIR/main_v2.cpp --no-run || exit 1

for ((i = ${SEED:-0}; ; i++)); do
  echo $i
  # python $DIR/generate.py 1 5 $i > $DIR/test-in.txt || exit 1
  python $DIR/generate.py 50 100 $i > $DIR/test-in.txt || exit 1
  ./build/main < $DIR/test-in.txt > $DIR/test-out.txt || break
done
