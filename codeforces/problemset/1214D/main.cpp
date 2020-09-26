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
  int n, m; // n x m \in [3, 10^6]
  cin >> n >> m;
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;

  int i_beg = 0,     j_beg = 0;
  int i_end = n - 1, j_end = m - 1;

  // BFS for reachability
  auto bfs = [&](int i0, int j0, vector<vector<int>>& dists, bool transpose) {
    deque<array<int, 2>> q;
    dists[i0][j0] = 0;
    q.push_back({i0, j0});
    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop_front();
      constexpr array<int, 2> kDirs[] = {{1, 0}, {0, 1}};
      for (auto [di, dj] : kDirs) {
        if (transpose) { di *= -1, dj *= -1; }
        int ii = i + di, jj = j + dj;
        if (0 <= ii && ii < n && 0 <= jj && jj < m) {
          if (board[ii][jj] == '.' && dists[ii][jj] == -1) {
            dists[ii][jj] = dists[i][j] + 1;
            q.push_back({ii, jj});
          }
        }
      }
    }
  };
  vector<vector<int>> dists(n, vector<int>(m, -1));
  vector<vector<int>> distsT(n, vector<int>(m, -1));
  bfs(i_beg, j_beg, dists,  false);
  bfs(i_end, j_end, distsT, true);
  dbg2(dists);

  // Not reachable
  if (dists[i_end][j_end] == -1) { cout << 0 << endl; return; }

  // Count reachable cells after d steps
  vector<int> cnts(n + m - 1);
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (dists[i][j] == -1 || distsT[i][j] == -1) { continue; }
      cnts[dists[i][j]]++;
    }
  }

  int res = 2;
  FOR(d, 1, n + m - 2) {
    assert(cnts[d] >= 1);
    if (cnts[d] == 1) {
      res = 1; break;
    }
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1214D/main.cpp --check

%%%% begin
5 4
....
.##.
...#
....
....
%%%%
1
%%%% end

%%%% begin
2 2
..
..
%%%%
2
%%%% end

%%%% begin
4 4
....
#.#.
....
.#..
%%%%
1
%%%% end

%%%% begin
3 4
....
.##.
....
%%%%
2
%%%% end
*/
