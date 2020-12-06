#!/bin/bash

DIR=$(dirname $BASH_SOURCE)

python misc/run.py $DIR/main.cpp --no-run || exit 1

for ((i = 1; ; i++)); do
  echo $i
  python $DIR/generate.py 100 1000000 $i > $DIR/test-in.txt || exit 1
  ./build/main < $DIR/test-in.txt > $DIR/test-out.txt || break
done
