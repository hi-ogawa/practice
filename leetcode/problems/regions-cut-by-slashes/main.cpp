// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// DSU
struct Dsu {
  vector<int> ps;
  Dsu(int n) { ps.resize(n); iota(ALL(ps), 0); }
  int find(int a) {
    if (a == ps[a]) { return a; }
    return ps[a] = find(ps[a]);
  }
  void merge(int dst, int src) {
    ps[find(src)] = find(dst);
  }
};

// Main
int mainSolve(const vector<string>& board) {
  int n = board.size(); // [1, 30]

  // Encode parts (split single cell into four parts)
  //  | \ 0 / |
  //  | 3 x 1 |
  //  | / 2 \ |
  auto enc = [&](int i, int j, int k) -> int {
    return (i * n + j) * 4 + k;
  };

  auto inside = [&](int i, int j) -> bool {
    return 0 <= i && i < n && 0 <= j && j < n;
  };

  Dsu dsu(enc(n, n, 4));
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      // Connect to neighbors
      if (inside(i + 1, j)) {
        dsu.merge(enc(i, j, 2), enc(i + 1, j, 0));
      }
      if (inside(i - 1, j)) {
        dsu.merge(enc(i, j, 0), enc(i - 1, j, 2));
      }
      if (inside(i, j + 1)) {
        dsu.merge(enc(i, j, 1), enc(i, j + 1, 3));
      }
      if (inside(i, j - 1)) {
        dsu.merge(enc(i, j, 3), enc(i, j - 1, 1));
      }

      // Connect within cell
      if (board[i][j] == '/') {
        dsu.merge(enc(i, j, 0), enc(i, j, 3));
        dsu.merge(enc(i, j, 1), enc(i, j, 2));
        continue;
      }
      if (board[i][j] == '\\') {
        dsu.merge(enc(i, j, 0), enc(i, j, 1));
        dsu.merge(enc(i, j, 2), enc(i, j, 3));
        continue;
      }
      dsu.merge(enc(i, j, 0), enc(i, j, 1));
      dsu.merge(enc(i, j, 0), enc(i, j, 2));
      dsu.merge(enc(i, j, 0), enc(i, j, 3));
    }
  }

  map<int, int> components;
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      FOR(k, 0, 4) {
        components[dsu.find(enc(i, j, k))]++;
      }
    }
  }
  int res = components.size();
  return res;
}

// Submission
class Solution {
public:
  int regionsBySlashes(vector<string>& grid) {
    return mainSolve(grid);
  }
};

// Local testing
int main() {
  int n;
  cin >> n;
  vector<string> board(n);
  cin >> board;
  cout << mainSolve(board) << "\n";
  return 0;
};

/*
python misc/run.py leetcode/problems/regions-cut-by-slashes/main.cpp

%%%% begin
2
./
/.
%%%%
2
%%%% end
*/
