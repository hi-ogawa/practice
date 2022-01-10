#!/bin/bash

#
# Example:
#   bash misc/prepare.sh codeforces/problemset/321C/main.cpp https://codeforces.com/problemset/problem/321/C
#   bash misc/prepare.sh codeforces/problemset/1609C/main.py https://codeforces.com/contest/1609/problem/C
#

# Input
file_path="$1"
problem_url="$2"

if [ "$file_path" = "" ]; then
  echo "Usage: bash ${BASH_SOURCE[0]} <file> <url>"
  exit 1
fi

this_dir=$(dirname "${BASH_SOURCE[0]}")
runpy_path=$(realpath --relative-to="$PWD" "$this_dir/run.py")
file_extension="${file_path##*.}"
main_template="$this_dir/templates/main.$file_extension"

echo ":: Creating... [$file_path]"
mkdir -p "$(dirname "$file_path")"
cp --interactive "$main_template" "$file_path"
perl -pi -e "s#{{FILE}}#$file_path#" "$file_path"
perl -pi -e "s#{{RUNPY}}#$runpy_path#" "$file_path"

if [ -n "$problem_url" ]; then
  echo ":: Downloading... [$problem_url]"
  tests=$(python misc/download.py "$problem_url" --quiet)
  perl -pi -e "s/{{TESTS}}/$tests/" "$file_path"
fi

echo ":: Finished"
