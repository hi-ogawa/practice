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
  ll n, m; // <= 10^3
  cin >> n >> m;

  vector<vector<char>> board(n, vector<char>(m, '?'));
  cin >> board;
  // DD2(board);

  int i0, j0, i1, j1;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == 'A') { i0 = i; j0 = j; }
      if (board[i][j] == 'B') { i1 = i; j1 = j; }
    }
  }

  vector<vector<ll>> dists(n, vector<ll>(m, -1));
  vector<vector<tuple<int, int>>> parents(n, vector<tuple<int, int>>(m, {0, 0}));
  deque<tuple<int, int>> queue;

  queue.push_back({i0, j0});
  dists[i0][j0] = 0;
  while (!queue.empty()) {
    // DD2(dists);
    auto [i, j] = queue.front(); queue.pop_front();
    if (tie(i, j) == tie(i1, j1)) { break; }
    constexpr array<int, 2> dirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (auto [di, dj] : dirs) {
      int ii = i + di, jj = j + dj;
      if (0 <= ii && ii < n && 0 <= jj && jj < m) {
        if (dists[ii][jj] != -1) { continue; }
        if (board[ii][jj] == '#') { continue; }
        dists[ii][jj] = dists[i][j] + 1;
        parents[ii][jj] = {i, j};
        queue.push_back({ii, jj});
      }
    }
  }

  int res1 = dists[i1][j1];
  vector<char> res2;
  if (res1 != -1) {
    map<tuple<int, int>, char> mapping = {
        {{1, 0}, 'D'}, {{-1, 0}, 'U'}, {{0, 1}, 'R'}, {{0, -1}, 'L'}};
    int i = i1, j = j1;
    while (tie(i, j) != tie(i0, j0)) {
      auto [ii, jj] = parents[i][j];
      res2.push_back(mapping[{i - ii, j - jj}]);
      i = ii; j = jj;
    }
    reverse(ALL(res2));
  }

  if (res1 == -1) {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl << res1 << endl;
    FOR(i, 0, res1) { cout << res2[i]; }
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
python misc/run.py cses/graph_algorithms/task1193/main.cpp --check

%%%% begin
5 8
########
#.A#...#
#.##.#B#
#......#
########
%%%%
YES
9
LDDRRRRRU
%%%% end
*/
