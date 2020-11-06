// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
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

// Segment tree for range set and range OR-sum
struct SegmentTree {
  int n = 1;
  vector<ull> data, lazy;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, 0);
    lazy.assign(2 * n, 0);
  }

  ull value(int /* l */, int /* r */, int j) {
    if (lazy[j] == 0) { return data[j]; }
    return lazy[j];
  }

  void push(int l, int r, int j) {
    if (lazy[j] == 0) { return; }
    data[j] = value(l, r, j);
    lazy[2 * j] = lazy[j];
    lazy[2 * j + 1] = lazy[j];
    lazy[j] = 0;
  }

  void set(int ql, int qr, ull qv) {
    function<ull(int, int, int)> rec = [&](int l, int r, int j) -> ull {
      if (qr <= l || r <= ql) { return value(l, r, j); }
      if (ql <= l && r <= qr) { lazy[j] = qv; return value(l, r, j); }
      push(l, r, j);
      int m = (l + r) / 2;
      return data[j] = rec(l, m, 2 * j) | rec(m, r, 2 * j + 1);
    };
    rec(0, n, 1);
  }

  ull reduce(int ql, int qr) {
    function<ull(int, int, int)> rec = [&](int l, int r, int j) -> ull {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return value(l, r, j); }
      push(l, r, j);
      int m = (l + r) / 2;
      return rec(l, m, 2 * j) | rec(m, r, 2 * j + 1);
    };
    return rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 4 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [1, 60]
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  vector<array<int, 3>> qs(nq);
  for (auto& q : qs) {
    cin >> q[0];
    if (q[0] == 1) {
      cin >> q[1] >> q[2];
    }
    if (q[0] == 2) {
      cin >> q[1];
    }
  }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS for subtree size and in-time
  vector<int> sizes(n);
  vector<int> in_times(n);
  int time = 0;
  function<void(int, int)> dfs = [&](int v, int vp) {
    in_times[v] = time++;
    sizes[v] = 1;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v);
      sizes[v] += sizes[u];
    }
  };
  dfs(0, 0);
  dbg(sizes);
  dbg(in_times);

  // Subtree as segment
  SegmentTree tree(n);
  FOR(x, 0, n) {
    int i = in_times[x];
    int b = ls[x] - 1; // [0, 59]
    tree.set(i, i + 1, (1ULL << b));
  }

  for (auto [t, x, y] : qs) {
    x--; y--;
    int i = in_times[x];
    int s = sizes[x];
    if (t == 1) {
      tree.set(i, i + s, (1ULL << y));
    }
    if (t == 2) {
      ull z = tree.reduce(i, i + s);
      int res = __builtin_popcountll(z);
      cout << res << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/620E/main_v2.cpp

%%%% begin
7 10
1 1 1 1 1 1 1
1 2
1 3
1 4
3 5
3 6
3 7
1 3 2
2 1
1 4 3
2 1
1 2 5
2 1
1 6 4
2 1
2 2
2 3
%%%%
2
3
4
5
1
2
%%%% end

%%%% begin
23 30
1 2 2 6 5 3 2 1 1 1 2 4 5 3 4 4 3 3 3 3 3 4 6
1 2
1 3
1 4
2 5
2 6
3 7
3 8
4 9
4 10
4 11
6 12
6 13
7 14
7 15
7 16
8 17
8 18
10 19
10 20
10 21
11 22
11 23
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4
1 12 1
1 13 1
1 14 1
1 15 1
1 16 1
1 17 1
1 18 1
1 19 1
1 20 1
1 21 1
1 22 1
1 23 1
2 1
2 5
2 6
2 7
2 8
2 9
2 10
2 11
2 4
%%%%
6
1
3
3
2
1
2
3
5
5
1
2
2
1
1
1
2
3
%%%% end
*/
