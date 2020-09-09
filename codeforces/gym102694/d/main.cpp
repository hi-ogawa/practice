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
  int n, m;
  cin >> n >> m;
  assert(m == n - 1);
  vector<array<int, 3>> edges(n - 1);
  cin >> edges;
  int nq;
  cin >> nq;
  vector<array<int, 2>> qs(nq);
  cin >> qs;
  for (auto& [x, y, _w] : edges) { x--; y--; }
  for (auto& [x, y] : qs) { x--; y--; }

  vector<vector<array<int, 2>>> adj(n);
  for (auto [x, y, w] : edges) {
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }

  // DFS
  int kInf = 1 << 30;
  vector<int> depths(n, -1);
  vector<pair<int, int>> parents(n, {-1, kInf});
  function<void(int)> dfs = [&](int v) {
    for (auto [u, w] : adj[v]) {
      if (depths[u] == -1) {
        depths[u] = depths[v] + 1;
        parents[u] = {v, w};
        dfs(u);
      }
    }
  };
  depths[0] = 0;
  parents[0] = {0, kInf};
  dfs(0);

  // Binary lifting
  int b_lim = 0;
  while ((1 << b_lim) < n) { b_lim++; }
  vector<vector<pair<int, int>>> table(b_lim, vector<pair<int, int>>(n));
  table[0] = parents;
  FOR(b, 1, b_lim) {
    FOR(v, 0, n) {
      auto [u, w1] = table[b - 1][v];
      auto [t, w2] = table[b - 1][u];
      table[b][v] = {t, min(w1, w2)};
    }
  }
  auto lift = [&](int v, int e) -> pair<int, int> {
    int b = 0;
    int w = kInf;
    while (e > 0) {
      if (e & 1) {
        auto [vv, ww] = table[b][v];
        v = vv;
        w = min(w, ww);
      }
      e >>= 1; b++;
    }
    return {v, w};
  };

  // LCA
  auto getLCA = [&](int x, int y) -> int {
    int dx = depths[x], dy = depths[y];
    if (dx > dy) { swap(x, y); swap(dx, dy); }
    int w;
    tie(y, w) = lift(y, dy - dx);
    if (x == y) { return w; }

    int xx, yy, w1, w2;
    int b = b_lim - 1;
    while (true) {
      tie(xx, w1) = table[b][x];
      tie(yy, w2) = table[b][y];
      if (xx == yy) {
        if (b == 0) { return min(w, min(w1, w2)); }
        b--; continue;
      }
      x = xx; y = yy; w = min(w, min(w1, w2));
    }
  };

  for (auto [x, y] : qs) {
    int res = getLCA(x, y);
    cout << res << endl;
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
python misc/run.py codeforces/gym102694/d/main.cpp --check

%%%% begin
5 4
1 3 2653
4 1 322
5 1 8657
2 4 4896
5
4 2
2 5
2 5
1 3
4 5
%%%%
4896
322
322
2653
322
%%%% end
*/
