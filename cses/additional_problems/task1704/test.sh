#!/bin/bash

DIR=$(dirname $BASH_SOURCE)

python misc/run.py $DIR/main_v2.cpp --no-run || exit 1
python misc/run.py $DIR/check.cpp --no-run --exec-file=./build/check || exit 1

for ((i = 1; ; i++)); do
  echo $i
  python $DIR/generate.py $i > $DIR/test-in.txt || exit 1
  ./build/main < $DIR/test-in.txt > $DIR/test-out.txt || break
  ./build/check $DIR/test-{in,out}.txt || break
done
