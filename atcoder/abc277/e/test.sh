#!/bin/bash
set -eu -o pipefail

# bash atcoder/abc277/e/test.sh

DIR=$(dirname "${BASH_SOURCE[0]}")

python misc/run.py "$DIR/main.rs" --no-run || exit 1

for ((i = ${SEED:-0}; ; i++)); do
  echo "$i"
  python "$DIR/generate.py" 5 10 5 10 "$i" > "$DIR/test-in.txt" || exit 1
  ./build/main < "$DIR/test-in.txt" > "$DIR/test-out.txt" || exit 1
done
