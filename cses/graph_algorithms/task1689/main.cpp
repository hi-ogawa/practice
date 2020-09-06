// AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
using ivec2 = array<int, 2>;
constexpr int n = 8;
constexpr ivec2 kMoves[] = {
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2},
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

ull enc(int i, int j) { return 1ULL << (i * n + j); }

int countMoves(int i, int j, ull hist) {
  int res = 0;
  for (auto [di, dj] : kMoves) {
    int ii = i + di, jj = j + dj;
    if (0 <= ii && ii < n && 0 <= jj && jj < n && !(hist & enc(ii, jj))) {
      res++;
    }
  }
  return res;
}

bool solve(int i, int j, ull hist, int k, vector<ivec2>& path) {
  hist |= enc(i, j);
  path[k] = {i, j};
  if (k + 1 == n * n) { return 1; }

  // Warnsdorff's heuristics
  vector<array<int, 3>> nexts;
  for (auto [di, dj] : kMoves) {
    int ii = i + di, jj = j + dj;
    if (0 <= ii && ii < n && 0 <= jj && jj < n && !(hist & enc(ii, jj))) {
      nexts.push_back({countMoves(ii, jj, hist), ii, jj});
    }
  }
  sort(ALL(nexts));

  for (auto [_c, ii, jj] : nexts) {
    if (solve(ii, jj, hist, k + 1, path)) {
      return 1;
    }
  }
  return 0;
};

void mainCase() {
  int i_beg, j_beg;
  cin >> j_beg >> i_beg;
  i_beg--; j_beg--;

  vector<ivec2> res(n * n, {0, 0});
  bool ok = solve(i_beg, j_beg, 0, 0, res);
  assert(ok);

  vector<vector<int>> board(n, vector<int>(n, -1));
  FOR(k, 0, n * n) {
    auto [i, j] = res[k];
    board[i][j] = k + 1;
  }
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      if (j) cout << " ";
      cout << board[i][j];
    }
    cout << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py cses/graph_algorithms/task1689/main.cpp --check

%%%% begin
2 1
%%%%
%%%% end
*/
