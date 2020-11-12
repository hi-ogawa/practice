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

// Segment tree for 0/1 flip and sum
struct SegmentTree {
  int n = 1;
  vector<int> data, lazy;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, 0);
    lazy.assign(2 * n, 0);
  }

  array<int, 2> toRange(int j) {
    assert(j > 0);
    int b = 31 - __builtin_clz(j);
    int s = n >> b;
    int i = j ^ (1 << b);
    return {s * i, s * (i + 1)};
  }

  int value(int j) {
    if (lazy[j] == 0) { return data[j]; }
    auto [l, r] = toRange(j);
    return (r - l) - data[j];
  }

  void push(int j) {
    if (lazy[j] == 0) { return; }
    data[j] = value(j);
    lazy[2 * j] ^= 1;
    lazy[2 * j + 1] ^= 1;
    lazy[j] = 0;
  }

  void flip(int ql, int qr) {
    function<int(int, int, int)> rec = [&](int l, int r, int j) -> int {
      if (qr <= l || r <= ql) { return value(j); }
      if (ql <= l && r <= qr) { lazy[j] ^= 1; return value(j); }
      push(j);
      int m = (l + r) / 2;
      return data[j] = rec(l, m, 2 * j) + rec(m, r, 2 * j + 1);
    };
    rec(0, n, 1);
  }

  int reduce(int ql, int qr) {
    function<int(int, int, int)> rec = [&](int l, int r, int j) -> int {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return value(j); }
      push(j);
      int m = (l + r) / 2;
      return rec(l, m, 2 * j) + rec(m, r, 2 * j + 1);
    };
    return rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> parents(n - 1);
  cin >> parents;
  vector<int> ls(n); // {0, 1}
  cin >> ls;
  int nq;
  cin >> nq;
  vector<tuple<string, int>> qs(nq);
  cin >> qs;

  vector<vector<int>> adj(n);
  FOR(i, 0, n - 1) {
    int j = parents[i];
    adj[j - 1].push_back(i + 1);
  }

  // DFS for subtree size, etc...
  vector<int> in_times(n);
  vector<int> sizes(n);
  int time = 0;
  function<void(int)> dfs = [&](int v) {
    in_times[v] = time++;
    sizes[v] = 1;
    for (auto u : adj[v]) {
      dfs(u);
      sizes[v] += sizes[u];
    }
  };
  dfs(0);

  // Subtree as segment
  SegmentTree tree(n);
  FOR(v, 0, n) {
    int i = in_times[v];
    if (ls[v]) {
      tree.flip(i, i + 1);
    }
  }

  for (auto [t, v] : qs) {
    v--;
    int i = in_times[v];
    int s = sizes[v];
    if (t == "pow") {
      tree.flip(i, i + s);
    }
    if (t == "get") {
      auto res = tree.reduce(i, i + s);
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
python misc/run.py codeforces/problemset/877E/main.cpp

%%%% begin
4
1 1 1
1 0 0 1
9
get 1
get 2
get 3
get 4
pow 1
get 1
get 2
get 3
get 4
%%%%
2
0
0
1
2
1
1
0
%%%% end
*/
