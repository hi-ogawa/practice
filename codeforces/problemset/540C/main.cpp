// AFTER EDITORIAL, AC

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
  int n, m; // [1, 500]
  cin >> n >> m;
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;
  int i_beg, j_beg, i_end, j_end;
  cin >> i_beg >> j_beg >> i_end >> j_end;
  i_beg--; j_beg--; i_end--; j_end--;

  constexpr array<int, 2> kGridDirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  // BFS for shortest "." path
  vector<vector<int>> dists(n, vector<int>(m, -1));
  {
    deque<array<int, 2>> q;
    q.push_back({i_beg, j_beg});
    dists[i_beg][j_beg] = 0;
    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop_front();
      for (auto [di, dj] : kGridDirs) {
        int ii = i + di, jj = j + dj;
        if ((ull)ii < (ull)n && (ull)jj < (ull)m) {
          if (board[ii][jj] == '.' && dists[ii][jj] == -1) {
            dists[ii][jj] = dists[i][j] + 1;
            q.push_back({ii, jj});
          }
        }
      }
    }
  }
  dbg2(board);
  dbg2(dists);

  bool ok = 0;
  if (board[i_end][j_end] == 'X') {
    // Check reachable to neighbors
    int cnt = 0;
    for (auto [di, dj] : kGridDirs) {
      int ii = i_end + di, jj = j_end + dj;
      if ((ull)ii < (ull)n && (ull)jj < (ull)m) {
        cnt += (dists[ii][jj] != -1);
      }
    }
    ok = cnt >= 1;
  } else {
    // Check reachable and non-crach neighbors
    int cnt = 0;
    for (auto [di, dj] : kGridDirs) {
      int ii = i_end + di, jj = j_end + dj;
      if ((ull)ii < (ull)n && (ull)jj < (ull)m) {
        cnt += (board[ii][jj] == '.') || (ii == i_beg && jj == j_beg);
      }
    }
    ok = dists[i_end][j_end] != -1 && cnt >= 2;
  }
  cout << (ok ? "YES" : "NO") << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/540C/main.cpp --check

%%%% begin
2 2
..
XX
2 1
1 1
%%%%
YES
%%%% end

%%%% begin
4 6
X...XX
...XX.
.X..X.
......
1 6
2 2
%%%%
YES
%%%% end

%%%% begin
5 4
.X..
...X
X.X.
....
.XX.
5 3
1 1
%%%%
NO
%%%% end

%%%% begin
4 7
..X.XX.
.XX..X.
X...X..
X......
2 2
1 6
%%%%
YES
%%%% end
*/
