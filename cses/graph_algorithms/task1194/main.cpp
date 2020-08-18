// TLE

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

  vector<vector<char>> board(n, vector<char>(m, '?'));
  cin >> board;
  // DD2(board);

  tuple<int, int> A;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == 'A') {
        A = {i, j};
        break;
      }
    }
  }
  // DD(A);

  set<tuple<int, int>> goals;
  FOR(i, 0, n) {
    for (auto j : {0, m - 1}) {
      if (board[i][j] != '#' && board[i][j] != 'M') { goals.insert({i, j}); }
    }
  }
  FOR(j, 0, m) {
    for (auto i : {0, n - 1}) {
      if (board[i][j] != '#' && board[i][j] != 'M') { goals.insert({i, j}); }
    }
  }
  // DD(goals);

  // WIN  <=>  ∃g. ∀M. path(A, g) < path(A, M)
  bool win = 0;
  tuple<int, int> win_goal;
  vector<vector<tuple<int, int>>> win_parents;

  // BFS from each goal
  for (auto [ig, jg] : goals) {
    vector<vector<int>> dists(n, vector<int>(m, -1));
    vector<vector<tuple<int, int>>> parents(n, vector<tuple<int, int>>(m, {0, 0}));
    deque<tuple<int, int>> queue;

    queue.push_back({ig, jg});
    dists[ig][jg] = 0;
    int a_dist = 1 << 30;
    int m_dist = 1 << 30;
    while (!queue.empty()) {
      auto [i, j] = queue.front(); queue.pop_front();
      if (tie(i, j) == A) {
        a_dist = min(a_dist, dists[i][j]);
      }
      if (board[i][j] == 'M') {
        m_dist = min(m_dist, dists[i][j]);
      }
      if (max(a_dist, m_dist) < dists[i][j]) { // Wait until all node up to this depth is popped
        break;
      }
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
    // DD(tie(ig, jg, a_dist, m_dist));
    if (a_dist < m_dist) {
      win = 1;
      win_goal = {ig, jg};
      win_parents = parents;
      break;
    }
  }
  // DD(win);
  // DD(win_goal);
  // DD2(win_parents);

  if (!win) {
    cout << "NO" << endl;
    return;
  }

  vector<char> res;
  {
    // Back tracking
    auto [i, j] = A;
    map<tuple<int, int>, char> mapping = {{{1, 0}, 'D'}, {{-1, 0}, 'U'}, {{0, 1}, 'R'}, {{0, -1}, 'L'}};
    while (tie(i, j) != win_goal) {
      auto [ii, jj] = win_parents[i][j];
      res.push_back(mapping[{ii - i, jj - j}]);
      i = ii; j = jj;
    }
  }

  cout << "YES" << endl;
  cout << res.size() << endl;
  for (auto c : res) { cout << c; }
  cout << endl;
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
python misc/run.py cses/graph_algorithms/task1194/main.cpp --check

%%%% begin
1 3
##A
%%%%
YES
0

%%%% end

%%%% begin
5 8
########
#M..A..#
#.#.M#.#
#M#..#..
#.######
%%%%
YES
5
RRDDR
%%%% end
*/
