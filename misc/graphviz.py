def readline_ints():
  import sys
  return list(map(int, sys.stdin.readline().strip().split()))


def main(name, directed, zero_based):
  n, m = readline_ints()
  edges = [readline_ints() for _ in range(m)]

  if zero_based:
    edges = [[x - 1, y - 1] for x, y in edges]

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
  for x, y in edges:
    res += f"  {x} {sep} {y};\n"
  res += "}"

  print(res)


def main_cli():
  import argparse
  parser = argparse.ArgumentParser()
  parser.add_argument("--name", type=str, default="G")
  parser.add_argument("--directed", action="store_true", default=False)
  parser.add_argument("--zero-based", action="store_true", default=False)
  main(**parser.parse_args().__dict__)


if __name__ == "__main__":
  main_cli()
