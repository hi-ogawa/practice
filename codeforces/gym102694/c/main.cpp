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
  int n;
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  int nq;
  cin >> nq;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS for parents/depths
  vector<int> parents(n, -1);
  vector<int> depths(n, -1);
  function<void(int)> dfs = [&](int v) {
    for (auto u : adj[v]) {
      if (parents[u] == -1) {
        parents[u] = v;
        depths[u] = depths[v] + 1;
        dfs(u);
      }
    }
  };
  parents[0] = 0;
  depths[0] = 0;
  dfs(0);

  // Binary lifting
  int b_lim = 0; // n < 2^b
  while ((1 << b_lim) <= n) { b_lim++; }
  vector<vector<int>> table(b_lim, vector<int>(n));
  table[0] = parents;
  FOR(b, 1, b_lim) {
    FOR(v, 0, n) {
      table[b][v] = table[b - 1][table[b - 1][v]];
    }
  }
  auto lift = [&](int v, int e) -> int {
    int b = 0;
    while (e > 0) {
      if (e & 1) { v = table[b][v]; }
      e >>= 1; b++;
    }
    return v;
  };

  // LCA
  auto getLCA = [&](int x, int y) -> int {
    int dx = depths[x], dy = depths[y];
    if (dx > dy) { swap(x, y); swap(dx, dy); }
    y = lift(y, dy - dx);
    if (x == y) { return x; }

    int b = b_lim - 1;
    while (true) {
      int xx = table[b][x], yy = table[b][y];
      if (xx == yy) {
        if (b == 0) { return xx; }
        b--; continue;
      }
      x = xx; y = yy;
    }
  };

  // Answer query
  auto solve = [&](int x, int y, int c) -> int {
    int z = getLCA(x, y);
    int dx = depths[x], dy = depths[y], dz = depths[z];
    int dist = dx + dy - 2 * dz;
    if (c >= dist) { return y; }
    if (c < dx - dz) { return lift(x, c); } // x --c--> z
    return lift(y, dist - c); // x --> z --c--> y
  };

  for (auto [x, y, c] : qs) {
    x--; y--;
    int res = solve(x, y, c);
    cout << (res + 1) << endl;
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
python misc/run.py codeforces/gym102694/c/main.cpp --check

%%%% begin
5
4 2
1 4
5 4
3 4
5
3 5 2
3 5 4
1 5 5
4 5 4
1 5 4
%%%%
5
5
5
5
5
%%%% end
*/
