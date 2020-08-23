// AFTER EDITORIAL, AC

// Using 0-1 BFS

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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n, m; // <= 10^3
  cin >> n >> m;
  int i_beg, j_beg, i_end, j_end;
  cin >> i_beg >> j_beg >> i_end >> j_end;
  vector<vector<char>> board(n, vector<char>(m, 0));
  cin >> board;
  i_beg--; j_beg--; i_end--; j_end--;
  // DD2(board);

  vector<vector<int>> dists(n, vector<int>(m, -1));
  deque<tuple<int, int>> queue;
  queue.push_back({i_beg, j_beg});
  dists[i_beg][j_beg] = 0;
  while (!queue.empty()) {
    // DD(queue);
    // DD2(dists);
    auto [i, j] = queue.front(); queue.pop_front();
    if (i == i_end && j == j_end) { break; }
    int d = dists[i][j];

    // No-magic move
    constexpr array<int, 2> dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto [di, dj] : dirs) {
      int ii = i + di, jj = j + dj;
      if (0 <= ii && ii < n && 0 <= jj && jj < m) {
        if (board[ii][jj] == '#') { continue; }
        int dd = dists[ii][jj];
        if (dd == -1 || dd > d) {
          dists[ii][jj] = d;
          queue.push_front({ii, jj});
        }
      }
    }

    // Magic move
    FOR(di, -2, 3) {
      FOR(dj, -2, 3) {
        int ii = i + di, jj = j + dj;
        if (0 <= ii && ii < n && 0 <= jj && jj < m) {
          if (board[ii][jj] == '#') { continue; }
          int dd = dists[ii][jj];
          if (dd == -1 || dd > d + 1) {
            dists[ii][jj] = d + 1;
            queue.push_back({ii, jj});
          }
        }
      }
    }
  }
  // DD2(dists);

  int res = dists[i_end][j_end];
  cout << res << endl;
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
python misc/run.py atcoder/abc176/d/main_v2.cpp --check

%%%% begin
4 5
1 2
2 5
#.###
####.
#..##
#..##
%%%%
2
%%%% end
*/
