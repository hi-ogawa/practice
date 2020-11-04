def readline_ints():
  import sys
  return list(map(int, sys.stdin.readline().strip().split()))


def convert_parents_to_edges(parents):
  n = len(parents)
  edges = []
  for v in range(n):
    vp, *extra = parents[v]
    if vp > 0:
      edges.append([vp, v + 1])
  return edges


def main(name, directed, zero_based, tree, parent):
  if tree or parent:
    n = readline_ints()[0]
    m = n - 1
  else:
    n, m = readline_ints()

  if parent:
    parents = [readline_ints() for _ in range(n)]
    edges = convert_parents_to_edges(parents)
  else:
    edges = [readline_ints() for _ in range(m)]

  if zero_based:
    edges = [[x - 1, y - 1, *extra] for x, y, *extra in edges]

  #
  # Example
  #   graph G { node []; x; y; ...; x -> y; ...; }
  #

  typ = "graph"
  sep = "--"
  if directed:
    typ = "digraph"
    sep = "->"

  res = f"{typ} {name}" + " {\n"
  res += "  node [];" + "".join(f" {i + int(not zero_based)};" for i in range(n)) + "\n"
  for x, y, *extra in edges:
    label = ', '.join(map(str, extra))
    res += f"  {x} {sep} {y} [ label = \"{label}\" ];\n"
  res += "}"

  print(res)


def main_cli():
  import argparse
  parser = argparse.ArgumentParser()
  parser.add_argument("--name", type=str, default="G")
  parser.add_argument("--directed", action="store_true", default=False)
  parser.add_argument("--zero-based", action="store_true", default=False)
  parser.add_argument("--tree", action="store_true", default=False)
  parser.add_argument("--parent", action="store_true", default=False)
  main(**parser.parse_args().__dict__)


if __name__ == "__main__":
  main_cli()
