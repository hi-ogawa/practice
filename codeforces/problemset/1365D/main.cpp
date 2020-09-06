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
void mainCase() {
  int n, m; // [1, 50]
  cin >> n >> m;
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;

  vector<array<int, 2>> gs, bs;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == 'G') { gs.push_back({i, j}); }
      if (board[i][j] == 'B') { bs.push_back({i, j}); }
    }
  }
  // We can block all
  if (gs.size() == 0) { cout << "Yes" << endl; return; }

  //
  // PROP.
  //   ok iff "G" can reach goal without passing "B" neighbors
  //

  // Block "B" neighbors
  for (auto [i, j] : bs) {
    constexpr array<int, 2> dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto [di, dj] : dirs) {
      int ii = i + di, jj = j + dj;
      if (0 <= ii && ii < n && 0 <= jj && jj < m) {
        board[ii][jj] = '#';
      }
    }
  }
  if (board[n - 1][m - 1] == '#') {
    cout << "No" << endl; return;
  }

  // Check if "G" reachable to goal without passing "B" neighbors
  vector<vector<int>> dists(n, vector<int>(m, -1));
  deque<array<int, 2>> q;
  q.push_back({n - 1, m - 1});
  dists[n - 1][m - 1] = 0;
  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop_front();
    constexpr array<int, 2> dirs[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto [di, dj] : dirs) {
      int ii = i + di, jj = j + dj;
      if (0 <= ii && ii < n && 0 <= jj && jj < m) {
        if (board[ii][jj] != '#' && dists[ii][jj] == -1) {
          dists[ii][jj] = dists[i][j] + 1;
          q.push_back({ii, jj});
        }
      }
    }
  }
  dbg2(dists);

  bool ok = 1;
  for (auto [i, j] : gs) {
    if (dists[i][j] == -1) { ok = 0; break; }
  }
  cout << (ok ? "Yes" : "No") << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1365D/main.cpp --check


%%%% begin
6
1 1
.
1 2
G.
2 2
#B
G.
2 3
G.#
B#.
3 3
#B.
#..
GG.
2 2
#B
B.
%%%%
Yes
Yes
No
No
Yes
Yes
%%%% end
*/
