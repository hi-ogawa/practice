#!/bin/bash
set -eu -o pipefail

# bash atcoder/abc280/d/test.sh

DIR=$(dirname "${BASH_SOURCE[0]}")

python misc/run.py "$DIR/main.rs" --no-run
python misc/run.py "$DIR/brute.rs" --no-run --exec-file=./build/brute

for ((i = ${SEED:-0}; ; i++)); do
  echo "$i"
  python "$DIR/generate.py" 2 1000 "$i" > "$DIR/test-in.txt"
  ./build/main < "$DIR/test-in.txt" > "$DIR/test-out.txt"
  ./build/brute < "$DIR/test-in.txt" > "$DIR/test-out-brute.txt"
  diff "$DIR"/test-{out,out-brute}.txt
done
