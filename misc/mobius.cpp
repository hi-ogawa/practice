#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;

tuple<vector<bool>, vector<bool>> makeMobius(int n) {
  vector<bool> a(n, 1);
  vector<bool> b(n, 1);  // square free
  vector<bool> c(n, 1);  // liouville
  a[0] = a[1] = 0;
  int sqrtn = sqrt(n);
  for (int i = 2; i < n; i++) {
    if (a[i] == 0) {
      continue;
    }
    c[i] = !c[i];
    for (int j = 2 * i; j < n; j += i) {
      a[j] = 0;
      c[j] = !c[j];
    }
    if (i <= sqrtn) {
      int ii = i * i;
      for (int j = ii; j < n; j += ii) {
        b[j] = 0;
      }
    }
  }
  return {b, c};
}

void printMertens(ostream& ostr, int n, vector<bool>& square_free,
                  vector<bool>& liouville) {
  int mertens = 0;
  int width = floor(log10(n)) + 1;
  for (int i = 1; i <= n; i++) {
    int mobius = square_free[i] ? (2 * (int)liouville[i] - 1) : 0;
    mertens += mobius;
    auto mobius_c = mobius > 0 ? "+" : mobius < 0 ? "-" : "0";
    auto mertens_c = mertens > 0 ? "+" : "-";
    ostr << setfill(' ') << setw(width);
    ostr << i << " [" << mobius_c << "] |";
    for (int i = 0; i < abs(mertens); i++) {
      ostr << mertens_c;
    }
    ostr << endl;
  }
}

void _main(istream& istr, ostream& ostr) {
  int n;
  istr >> n;
  auto [square_free, liouville] = makeMobius(n + 1);
  printMertens(ostr, n, square_free, liouville);
}

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    puts("Usage: <program> <n>");
    return 1;
  }
  stringstream sstr(argv[1]);
  _main(sstr, cout);
  return 0;
}

/*
clang++ -std=c++17 -O2 -march=native -Wall -Wextra -o build/mobius misc/mobius.cpp
./build/mobius 100000
*/
