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
  int n, m, nq; // <= 10^6
  cin >> n >> m >> nq;
  vector<tuple<int, int>> edges(m, {0, 0});
  cin >> edges;
  vector<tuple<int, int, int>> qs(nq, {0, 0, 0});
  cin >> qs;
  for (auto& [x, y] : edges) { x--; y--; if (x > y) swap(x, y); }
  for (auto& [x, y, z] : qs) { x--; y--; z--; }
  sort(ALL(edges));
  edges.erase(unique(ALL(edges)), edges.end());
  dbg(edges);

  // (Original) connected components
  Dsu dsu(n);
  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
    dsu.merge(x, y);
  }

  // Critical vertex
  vector<int> in_time(n, -1);
  vector<int> parent(n, -1);
  vector<int> depth(n, -1);
  vector<int> ls(n, -1); // in-time of DFS subtree
  {
    int t = 0;
    function<void(int)> dfs = [&](int v) {
      dbg(v);
      int res = in_time[v] = t++;
      for (auto u : adj[v]) {
        // tree edge (parent)
        if (parent[v] == u) { continue; }
        // back edge
        if (in_time[u] >= 0) {
          res = min(res, in_time[u]);
          continue;
        }
        // tree edge (child)
        parent[u] = v;
        depth[u] = depth[v] + 1;
        dfs(u);
        res = min(res, ls[u]);
      }
      ls[v] = res;
    };
    FOR(v, 0, n) {
      if (in_time[v] == -1) {
        parent[v] = v; // for binary lifting to be simple
        depth[v] = 0;
        dfs(v);
      }
    }
  }
  dbg(parent);
  dbg(depth);
  dbg(ls);

  // Binary lifting
  int b_lim = 0;
  while ((1 << b_lim) <= n) { b_lim++; }
  vector<vector<int>> table(b_lim, vector<int>(n, 0));
  table[0] = parent;
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

  // Answer query
  auto solve = [&](int a, int b, int c) -> bool {
    if (dsu.find(a) != dsu.find(b)) { return 0; }
    if (a == c || b == c) { return 0; }
    if (a == b) { return 1; }
    int da = depth[a], db = depth[b], dc = depth[c];

    // a, b in subtree(c)
    bool ainc = da > dc && lift(a, da - dc) == c;
    bool binc = db > dc && lift(b, db - dc) == c;
    if (!ainc && !binc) { return 1; }
    if (!binc) { swap(a, b); swap(da, db); swap(ainc, binc); }

    // a not in c
    // b in c
    if (!ainc) {
      b = lift(b, db - dc - 1);
      return ls[b] < in_time[c]; // some back edge goes over "c"
    }

    // a in c
    // b in c
    {
      a = lift(a, da - dc - 1);
      b = lift(b, db - dc - 1);
      bool ok1 = a == b; // LCA in c
      bool ok2 = ls[a] < in_time[c] && ls[b] < in_time[c]; // both can go over "c"
      dbgv(ok1, ok2);
      return ok1 || ok2;
    }
  };

  for (auto [a, b, c] : qs) {
    bool res = solve(a, b, c);
    cout << (res ? "YES" : "NO") << endl;
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
python misc/run.py cses/additional_problems/task1750/main.cpp --check

%%%% begin
6 8 1
4 2
4 3
6 1
5 4
6 3
1 5
1 4
1 3
2 6 3
%%%%
YES
%%%% end

%%%% begin
5 6 1
1 2
2 3
1 3
3 4
4 5
3 5
1 5 3
%%%%
NO
%%%% end

%%%% begin
5 6 3
1 2
1 3
2 3
2 4
3 4
4 5
1 4 2
3 5 4
3 5 2
%%%%
YES
NO
YES
%%%% end
*/
