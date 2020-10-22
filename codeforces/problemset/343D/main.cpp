// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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

// Segment tree for range set and sum
struct SegmentTree1 {
  int n = 1;
  vector<int> data;
  vector<array<int, 2>> lazy; // (on/off, value)

  SegmentTree1(int _n) {
    while (n < _n) { n *= 2; }
    data.resize(2 * n);
    lazy.resize(2 * n);
  }

  int value(int l, int r, int j) {
    if (!lazy[j][0]) { return data[j]; }
    return (r - l) * lazy[j][1];
  }

  void push(int l, int r, int j) {
    if (!lazy[j][0]) { return; }
    data[j] = value(l, r, j);
    lazy[2 * j] = lazy[j];
    lazy[2 * j + 1] = lazy[j];
    lazy[j][0] = 0;
  }

  void set(int ql, int qr, int qv) {
    function<int(int, int, int)> rec = [&](int l, int r, int j) -> int {
      if (qr <= l || r <= ql) { return value(l, r, j); }
      if (ql <= l && r <= qr) { lazy[j] = {1, qv}; return value(l, r, j); }
      push(l, r, j);
      int m = (l + r) / 2;
      return data[j] = rec(l, m, 2 * j) + rec(m, r, 2 * j + 1);
    };
    rec(0, n, 1);
  }

  int reduce(int ql, int qr) {
    function<int(int, int, int)> rec = [&](int l, int r, int j) -> int {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return value(l, r, j); }
      push(l, r, j);
      int m = (l + r) / 2;
      return rec(l, m, 2 * j) + rec(m, r, 2 * j + 1);
    };
    return rec(0, n, 1);
  }
};

// Segment tree for range max
struct SegmentTree2 {
  int n = 1;
  vector<int> data;

  SegmentTree2(int _n) {
    while (n < _n) { n *= 2; }
    data.resize(2 * n);
  }

  void set(int qi, int qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = max(data[2 * j], data[2 * j + 1]);
    }
  }

  int reduce(int ql, int qr) {
    function<int(int, int, int)> rec = [&](int l, int r, int j) -> int {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return data[j]; }
      int m = (l + r) / 2;
      return max(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    return rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int n; // [1, 5 x 10^5]
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  int nq; // [1, 5 x 10^5]
  cin >> nq;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS for subtree size and in-time
  vector<int> in_time(n);
  vector<int> sizes(n);
  int time = 0;
  function<void(int, int)> dfs = [&](int v, int vp) {
    in_time[v] = time++;
    sizes[v]++;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v);
      sizes[v] += sizes[u];
    }
  };
  dfs(0, 0);

  // Subtree as segment
  SegmentTree1 filled(n);  // last filled time
  SegmentTree2 emptied(n); // last emptied time

  // Answer queries
  FOR(iq, 0, nq) {
    auto [t, x] = qs[iq];
    x--;
    int i = in_time[x];
    int s = sizes[x];
    if (t == 1) {
      filled.set(i, i + s, iq + 1);
    }
    if (t == 2) {
      emptied.set(i, iq + 1);
    }
    if (t == 3) {
      int f = filled.reduce(i, i + 1);
      int e = emptied.reduce(i, i + s);
      int res = f > e;
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
python misc/run.py codeforces/problemset/343D/main.cpp

%%%% begin
5
1 2
5 1
2 3
4 2
12
1 1
2 3
3 1
3 2
3 3
3 4
1 2
2 4
3 1
3 3
3 4
3 5
%%%%
0
0
0
1
0
1
0
1
%%%% end
*/
