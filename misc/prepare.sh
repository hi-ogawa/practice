#!/bin/bash

#
# Example:
#   bash misc/prepare.sh codeforces/problemset/321C/main.cpp https://codeforces.com/problemset/problem/321/C
#

FILE="${1}"
URL="${2}"
TEMPLATE_MAIN="misc/templates/main.cpp"

if [ -z "$FILE" ]; then
  echo "Usage: bash $BASH_SOURCE <file> <url>"
  exit 1
fi

echo ":: Creating... [$FILE]"
mkdir -p $(dirname $FILE)
cp -i $TEMPLATE_MAIN $FILE
perl -pi -e "s#{{FILE}}#$FILE#" $FILE

if [ -n "$URL" ]; then
  echo ":: Downloading... [$URL]"
  TESTS=$(python misc/download.py $URL --quiet)
  perl -pi -e "s/{{TESTS}}/$TESTS/" $FILE
fi

echo ":: Finished"
