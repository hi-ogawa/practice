#!/bin/bash

# Usage:
#   bash cses/graph_algorithms/task1160/test.sh

DIR=cses/graph_algorithms/task1160

python misc/run.py $DIR/main.cpp --no-run
python misc/run.py $DIR/check.cpp --no-run --exec-file=./build/check

for ((i = 1; ; i++)); do
  echo $i
  python $DIR/generate.py $i > ./build/in.txt || break
  ./build/main < ./build/in.txt > ./build/out.txt || break
  ./build/check ./build/in.txt ./build/out.txt || break
done

echo ":: ./build/in.txt"
cat ./build/in.txt

echo ":: ./build/out.txt"
cat ./build/out.txt
