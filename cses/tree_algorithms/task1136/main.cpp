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

// Fenwick tree for sum
struct FenwickTree {
  int n_;
  vector<ll> data_;
  FenwickTree(int n) { n_ = n; data_.resize(n); }
  void incr(int i, int v) {
    while (i < n_) {
      data_[i] += v;
      i = i | (i + 1);
    }
  }
  ll reduce(int r) { // [0, r)
    int i = r - 1;
    ll res = 0;
    while (i >= 0) {
      res += data_[i];
      i = (i & (i + 1)) - 1;
    }
    return res;
  }
  ll reduce(int l, int r) { // [l, r)
    return reduce(r) - reduce(l);
  }
};

// Main
void mainCase() {
  int n, nq; // <= 10^6
  cin >> n >> nq;
  vector<tuple<int, int>> edges(n - 1, {0, 0});
  cin >> edges;
  vector<tuple<int, int>> qs(nq, {0, 0});
  cin >> qs;
  for (auto& [x, y] : edges) { x--; y--; }
  for (auto& [x, y] : qs) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS
  vector<int> parent(n, -1);
  vector<int> depth(n, -1);
  vector<int> size(n, 0); // subtree size
  vector<int> in_time(n, -1);
  {
    int t = 0;
    function<void(int)> dfs = [&](int v) {
      in_time[v] = t++;
      size[v] = 1;
      for (auto u : adj[v]) {
        if (in_time[u] == -1) {
          parent[u] = v;
          depth[u] = depth[v] + 1;
          dfs(u);
          size[v] += size[u];
        }
      }
    };
    parent[0] = 0;
    depth[0] = 0;
    dfs(0);
  }
  dbg(parent); dbg(depth); dbg(size); dbg(in_time);

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

  auto getLCA = [&](int x, int y) -> int {
    int d = depth[x];
    int dd = depth[y];
    if (d > dd) { swap(x, y); swap(d, dd); }
    y = lift(y, dd - d);
    if (x == y) { return x; }

    // Binary search (TLE)
    // int d0 = 0, d1 = d; // [d0, d1)
    // while (d0 + 1 < d1) {
    //   int d2 = (d0 + d1) / 2;
    //   if (lift(x, d - d2) == lift(y, d - d2)) {
    //     d0 = d2;
    //   } else {
    //     d1 = d2;
    //   }
    // }
    // return lift(x, d - d0);

    // Lift directly
    int b = 0;
    while (true) {
      int xx = table[b][x], yy = table[b][y];
      if (xx == yy) {
        if (b == 0) { return xx; }
        b = 0;
        continue;
      }
      x = xx, y = yy;
      b++;
    }
  };

  FenwickTree tree(n);
  for (auto [x, y] : qs) {
    // Increase path sum (root -> x and root -> y)
    tree.incr(in_time[x], 1);
    tree.incr(in_time[y], 1);
    // Counter by decreasing path sum from lca
    int z = getLCA(x, y);
    dbgv(x, y, z);
    tree.incr(in_time[z], -1);
    if (z != 0) {
      tree.incr(in_time[parent[z]], -1);
    }
  }

  vector<ll> res(n, 0);
  FOR(x, 0, n) {
    int i = in_time[x];
    res[x] = tree.reduce(i, i + size[x]);
  }
  dbg(res);

  FOR(i, 0, n) {
    if (i) cout << " ";
    cout << res[i];
  }
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
python misc/run.py cses/tree_algorithms/task1136/main.cpp --check

%%%% begin
10 10
6 9
1 5
10 7
7 8
6 8
4 3
2 3
4 10
1 9
1 2
9 10
7 10
7 4
6 1
6 3
7 9
10 9
1 3
7 5
%%%%
4 1 3 4 1 8 9 7 7 7
%%%% end

%%%% begin
8 4
1 2
1 3
2 4
2 5
2 6
3 7
3 8
4 7
2 8
3 6
4 6
%%%%
3 4 3 2 0 2 1 1
%%%% end

%%%% begin
5 3
1 2
1 3
3 4
3 5
1 3
2 5
1 4
%%%%
3 1 3 1 1
%%%% end
*/
