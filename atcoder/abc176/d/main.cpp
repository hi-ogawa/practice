// CONTEST, AC

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

// DSU
struct Dsu {
  vector<int> data_;
  Dsu(int n) { data_.resize(n); iota(ALL(data_), 0); }
  int find(int a) {
    if (data_[a] == a) { return a; }
    return data_[a] = find(data_[a]);
  }
  void merge(int dst, int src) {
    data_[find(src)] = find(dst);
  }
};

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

  int k = n * m;
  auto enc = [&](int i, int j) { return i * m + j; };
  Dsu dsu(k);

  // "no-magic" components
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == '#') { continue; }
      if (i + 1 < n && board[i + 1][j] == '.') {
        dsu.merge(enc(i, j), enc(i + 1, j));
      }
      if (j + 1 < m && board[i][j + 1] == '.') {
        dsu.merge(enc(i, j), enc(i, j + 1));
      }
    }
  }
  vector<vector<int>> compos(n, vector<int>(m, -1));
  map<int, vector<int>> compos_enc;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == '.') {
        compos[i][j] = dsu.find(enc(i, j));
        compos_enc[dsu.find(enc(i, j))].push_back(enc(i, j));
      }
    }
  }
  // DD(compos_enc);
  // DD2(compos);

  // "magic" graph
  vector<set<int>> adj(k);
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == '#') { continue; }
      FOR(di, -2, 3) {
        FOR(dj, -2, 3) {
          int ii = i + di, jj = j + dj;
          if (0 <= ii && ii < n && 0 <= jj && jj < m && board[ii][jj] == '.') {
            int e1 = dsu.find(enc(i, j));
            int e2 = dsu.find(enc(ii, jj));
            adj[e1].insert(e2); adj[e2].insert(e1);
          }
        }
      }
    }
  }
  // DD(adj);

  // Shortest path in "magic" graph by BFS
  int v_beg = dsu.find(enc(i_beg, j_beg));
  int v_end = dsu.find(enc(i_end, j_end));
  // DD(tie(v_beg, v_end));

  vector<int> depths(k, -1);
  deque<int> queue;
  queue.push_back(v_beg);
  depths[v_beg] = 0;
  while (!queue.empty()) {
    int v = queue.front(); queue.pop_front();
    if (v == v_end) { break; }
    for (auto u : adj[v]) {
      if (depths[u] != -1) { continue; }
      depths[u] = depths[v] + 1;
      queue.push_back(u);
    }
  }
  // DD(depths);

  int res = depths[v_end];
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
python misc/run.py atcoder/abc176/d/main.cpp --check

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
