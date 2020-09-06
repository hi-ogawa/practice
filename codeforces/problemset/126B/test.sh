#!/bin/bash

DIR=$(dirname $BASH_SOURCE)

python misc/run.py $DIR/main.cpp --no-run || exit 1

for ((i = 1; ; i++)); do
  echo $i
  python $DIR/generate.py $i > ./build/in.txt || exit 1
  time ./build/main < ./build/in.txt > ./build/out.txt || exit 1
done

for FILE in ./build/{in,out}.txt; do
  echo :: $FILE
  cat $FILE
done
