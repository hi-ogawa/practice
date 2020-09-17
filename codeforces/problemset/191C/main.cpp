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

// Fenwick tree for sum
struct FenwickTree {
  int n_;
  vector<int> data_;
  FenwickTree(int n) { n_ = n; data_.resize(n); }
  void incr(int i, int v) {
    while (i < n_) {
      data_[i] += v;
      i = (i | (i + 1));
    }
  }
  int reduce(int r) { // [0, r)
    int i = r - 1;
    int res = 0;
    while (i >= 0) {
      res += data_[i];
      i = (i & (i + 1)) - 1;
    }
    return res;
  }
  int reduce(int l, int r) { return reduce(r) - reduce(l); }
};

// Main
void mainCase() {
  int n;
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  int nq;
  cin >> nq;
  vector<array<int, 2>> qs(nq);
  cin >> qs;
  for (auto& [x, y] : edges) { x--; y--; }
  for (auto& [x, y] : qs) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS
  vector<int> parents(n, -1);
  vector<int> depths(n, -1);
  vector<int> in_time(n);
  vector<int> sizes(n); // Subtree size
  int time = 0;
  function<void(int)> dfs = [&](int v) {
    sizes[v] = 1;
    in_time[v] = time++;
    for (auto u : adj[v]) {
      if (parents[u] == -1) {
        parents[u] = v;
        depths[u] = depths[v] + 1;
        dfs(u);
        sizes[v] += sizes[u];
      }
    }
  };
  parents[0] = 0;
  depths[0] = 0;
  dfs(0);

  // Binary lifting
  int b_lim = 0;
  while ((1 << b_lim) < n) { b_lim++; }
  vector<vector<int>> table(b_lim, vector<int>(n));
  table[0] = parents;
  FOR(b, 1, b_lim) {
    FOR(v, 0, n) {
      table[b][v] = table[b - 1][table[b - 1][v]];
    }
  }
  auto lift = [&](int x, int e) -> int {
    int b = 0;
    while (e > 0) {
      if (e & 1) { x = table[b][x]; }
      e >>= 1; b++;
    }
    return x;
  };

  auto getLCA = [&](int x, int y) -> int {
    int dx = depths[x], dy = depths[y];
    if (dx > dy) { swap(x, y); swap(dx, dy); }
    y = lift(y, dy - dx);
    if (x == y) { return x; }

    int b = b_lim - 1;
    while (b >= 0) {
      int xx = table[b][x], yy = table[b][y];
      if (xx == yy) { b--; continue; }
      x = xx; y = yy;
    }
    return table[0][x];
  };

  // Subtree as "in_time"-ordered segment
  FenwickTree tree(n);
  for (auto [x, y] : qs) {
    int z = getLCA(x, y);
    tree.incr(in_time[x], 1);
    tree.incr(in_time[y], 1);
    tree.incr(in_time[z], -2);
  }

  vector<int> res(n - 1);
  FOR(i, 0, n - 1) {
    auto [x, y] = edges[i]; // Identify tree edge as child vertex
    if (parents[y] == x) { swap(x, y); }
    assert(parents[x] == y);
    int ix = in_time[x];
    res[i] = tree.reduce(ix, ix + sizes[x]);
  }

  FOR(i, 0, n - 1) {
    cout << res[i] << " \n"[i == n - 2];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/191C/main.cpp --check

%%%% begin
5
1 2
1 3
2 4
2 5
2
1 4
3 5
%%%%
2 1 1 1
%%%% end

%%%% begin
5
3 4
4 5
1 4
2 4
3
2 3
1 3
3 5
%%%%
3 1 1 1
%%%% end
*/
