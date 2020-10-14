// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// DSU
struct Dsu {
  vector<int> ps;
  Dsu(int n) { ps.resize(n); iota(ALL(ps), 0); }
  int find(int a) {
    if (a == ps[a]) { return a; }
    return ps[a] = find(ps[a]);
  }
  void merge(int dst, int src) {
    ps[find(src)] = find(dst);
  }
};

// Main
void mainCase() {
  int n, m; // [1, 2 x 10^5]
  cin >> n >> m;
  vector<array<int, 3>> edges(m); // weight \in [1, 10^9]
  cin >> edges;
  for (auto& [x, y, _w] : edges) { x--; y--; }

  vector<int> order(m);
  iota(ALL(order), 0);
  sort(ALL(order), [&](int x, int y) { return edges[x][2] < edges[y][2]; });

  Dsu dsu(n);
  vector<int> mst(m);
  ll mst_w = 0;
  FOR(i, 0, m) {
    int e = order[i];
    auto [x, y, w] = edges[e];
    if (dsu.find(x) == dsu.find(y)) { continue; }
    dsu.merge(x, y);
    mst[e] = 1;
    mst_w += w;
  }
  dbg(mst_w, mst);

  // DFS for parents
  vector<vector<array<int, 2>>> adj(n);
  FOR(e, 0, m) {
    if (!mst[e]) { continue; }
    auto [x, y, w] = edges[e];
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }
  vector<array<int, 2>> parents(n); // (vertex, weight)
  vector<int> depths(n);
  function<void(int, int)> dfs = [&](int v, int vp) {
    for (auto [u, w] : adj[v]) {
      if (u == vp) { continue; }
      parents[u] = {v, w};
      depths[u] = depths[v] + 1;
      dfs(u, v);
    }
  };
  dfs(0, 0);

  // Binary lifting
  int b_lim = 0;
  while ((1 << b_lim) <= n) { b_lim++; }
  vector<vector<array<int, 2>>> table(b_lim, vector<array<int, 2>>(n));
  table[0] = parents;
  FOR(b, 1, b_lim) {
    FOR(v, 0, n) {
      auto [u1, w1] = table[b - 1][v];
      auto [u2, w2] = table[b - 1][u1];
      table[b][v] = {u2, max(w1, w2)};
    }
  }

  auto lift = [&](int x, int e) -> int {
    int b = 0;
    while (e > 0) {
      if (e & 1) { x = table[b][x][0]; }
      e >>= 1; b++;
    }
    return x;
  };

  auto liftAndFindMax = [&](int x, int e) -> int {
    int b = 0, res = 0;
    while (e > 0) {
      if (e & 1) {
        auto [y, w] = table[b][x];
        x = y; res = max(res, w);
      }
      e >>= 1; b++;
    }
    return res;
  };

  auto getLCA = [&](int x, int y) -> int {
    int dx = depths[x], dy = depths[y];
    if (dx > dy) { swap(dx, dy); swap(x, y); }
    y = lift(y, dy - dx);
    if (x == y) { return x; }
    int b = b_lim - 1;
    while (b >= 0) {
      int xx = table[b][x][0], yy = table[b][y][0];
      if (xx == yy) { b--; continue; }
      x = xx; y = yy;
    }
    return table[0][x][0];
  };

  // Find tree edge to replace (maximum weight edge along path(x, y))
  auto solve = [&](int x, int y) -> int {
    int z = getLCA(x, y);
    int dx = depths[x], dy = depths[y], dz = depths[z];
    int w1 = liftAndFindMax(x, dx - dz);
    int w2 = liftAndFindMax(y, dy - dz);
    return max(w1, w2);
  };

  // Cut MST
  vector<ll> res(m, mst_w);
  FOR(e, 0, m) {
    auto [x, y, w] = edges[e];
    // Skip MST edge
    if (mst[e]) { continue; }

    // Replace MST edge
    int ww = solve(x, y);
    assert(w >= ww);
    res[e] += w - ww;
  }
  dbg(res);

  FOR(e, 0, m) {
    cout << res[e] << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/609E/main.cpp

%%%% begin
8 10
2 5 4
7 5 2
7 3 28
4 5 14
3 2 15
1 2 3
6 2 5
2 8 17
4 6 2
1 4 10
%%%%
48
48
61
57
48
48
48
48
48
53
%%%% end

%%%% begin
5 7
1 2 3
1 3 1
1 4 5
2 3 2
2 5 3
3 4 2
4 5 4
%%%%
9
8
11
8
8
8
9
%%%% end
*/
