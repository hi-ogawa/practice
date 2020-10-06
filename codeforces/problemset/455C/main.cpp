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

// DSU with tracking component's diameter
struct Dsu {
  vector<int> ps, diams;
  Dsu(int n) {
    ps.resize(n);
    iota(ALL(ps), 0);
    diams.resize(n);
  }
  int find(int a) {
    if (a == ps[a]) { return a; }
    return ps[a] = find(ps[a]);
  }
  void merge(int dst, int src) {
    ps[find(src)] = find(dst);
  }
  void mergeDiameter(int dst, int src) {
    dst = find(dst); src = find(src);
    if (dst == src) { return; }
    int d1 = diams[dst], d2 = diams[src];
    int d3 = (d1 + 1) / 2 + (d2 + 1) / 2 + 1;
    diams[dst] = max(d1, max(d2, d3));
    ps[src] = dst;
  }
};

// Main
void mainCase() {
  int n, m, nq; // [1, 3 x 10^5]
  cin >> n >> m >> nq;
  vector<array<int, 2>> edges(m);
  cin >> edges;
  vector<array<int, 3>> qs(nq);
  FOR(i, 0, nq) {
    cin >> qs[i][0];
    if (qs[i][0] == 1) { cin >> qs[i][1]; }
    if (qs[i][0] == 2) { cin >> qs[i][1] >> qs[i][2]; }
  }

  // Compute initial diameters of components (forest)

  vector<vector<int>> adj(n);
  Dsu dsu(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
    dsu.merge(x, y);
  }

  map<int, vector<int>> components;
  FOR(v, 0, n) {
    components[dsu.find(v)].push_back(v);
  }

  vector<int> dists(n);
  function<void(int, int)> dfs = [&](int v, int vp) {
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dists[u] = dists[v] + 1;
      dfs(u, v);
    }
  };

  auto getDiameter = [&](int root, const vector<int>& vs) -> int {
    // 1st dfs
    dists[root] = 0;
    dfs(root, root);
    int v0 = root;
    for (auto v : vs) {
      if (dists[v] > dists[v0]) { v0 = v; }
    }
    // 2nd dfs
    dists[v0] = 0;
    dfs(v0, v0);
    int v1 = v0;
    for (auto v : vs) {
      if (dists[v] > dists[v1]) { v1 = v; }
    }
    return dists[v1];
  };

  for (auto& [root, vs] : components) {
    dsu.diams[root] = getDiameter(root, vs);
  }

  // Answer query and merge diameter

  for (auto [t, x, y] : qs) {
    dbg(dsu.diams);
    x--; y--;
    if (t == 1) {
      int res = dsu.diams[dsu.find(x)];
      cout << res << "\n";
    }
    if (t == 2) {
      dsu.mergeDiameter(x, y);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/455C/main.cpp --check

%%%% begin
10 6 7
1 2
2 3
1 4
3 5
1 6
5 7
1 1
2 8 10
1 10
2 9 5
1 7
1 4
2 1 9
%%%%
5
1
5
5
%%%% end

%%%% begin
6 0 6
2 1 2
2 3 4
2 5 6
2 3 2
2 5 3
1 1
%%%%
4
%%%% end
*/
