#!/bin/bash

DIR=$(dirname $BASH_SOURCE)

python misc/run.py $DIR/main_v2.cpp --no-run || exit 1
python misc/run.py $DIR/main_v3.cpp --no-run --exec-file=./build/main_v3 || exit 1

for ((i = 1; ; i++)); do
  echo $i
  python $DIR/generate.py $i > ./build/in.txt || exit 1
  ./build/main < ./build/in.txt > ./build/out.txt || exit 1
  ./build/main_v3 < ./build/in.txt > ./build/out_v3.txt || exit 1
  diff ./build/out.txt ./build/out_v3.txt || break
done

for FILE in ./build/{in,out,out_v3}.txt; do
  echo :: $FILE
  cat $FILE
done
