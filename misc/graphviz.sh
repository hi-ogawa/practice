#!/bin/bash

#
# Example:
#   $ bash misc/graphviz.sh --directed
#   :: Input graph data
#   5 4
#   1 2
#   1 3
#   4 1
#   5 1
#   :: Converting to svg...
#   :: Displaying...
#

echo ":: Input graph data"
python misc/graphviz.py "${@}" > build/graph.gv || exit 1

echo ":: Converting to svg..."
dot -Tsvg build/graph.gv > build/graph.svg || exit 1

echo ":: Displaying svg..."
xdg-open build/graph.svg || exit 1
