#!/bin/bash
set -eu -o pipefail

DIR=$(dirname "${BASH_SOURCE[0]}")

python misc/run.py "$DIR/main.rs" --no-run

for ((i = ${SEED:-0}; ; i++)); do
  echo "$i"
  python "$DIR/generate.py" 10 "$i" > "$DIR/test-in.txt"
  python "$DIR/brute.py" < "$DIR/test-in.txt" > "$DIR/test-out-brute.txt"
  ./build/main < "$DIR/test-in.txt" > "$DIR/test-out.txt"
  diff "$DIR"/test-{out,out-brute}.txt
done
