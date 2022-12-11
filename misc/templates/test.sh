#!/bin/bash
set -eu -o pipefail

DIR=$(dirname "${BASH_SOURCE[0]}")

python misc/run.py "$DIR/main.cpp" --no-run
# python misc/run.py "$DIR/brute.cpp" --no-run --exec-file=./build/brute
# python misc/run.py "$DIR/check.cpp" --no-run --exec-file=./build/check

for ((i = ${SEED:-0}; ; i++)); do
  echo "$i"
  python "$DIR/generate.py" 10 20 10 20 "$i" > "$DIR/test-in.txt"
  # ./build/brute < "$DIR/test-in.txt" > "$DIR/test-out-brute.txt"
  # TIME_BEGIN=$(date +%s.%N)
  ./build/main < "$DIR/test-in.txt" > "$DIR/test-out.txt"
  # TIME_END=$(date +%s.%N)
  # [ -n "$SHOW_TIME" ] && python -c "print('time : {:.5f}'.format(${TIME_END} - ${TIME_BEGIN}))"
  # diff "$DIR"/test-{out,out-brute}.txt
  # ./build/check "$DIR"/test-{in,out,out-brute}.txt
done
