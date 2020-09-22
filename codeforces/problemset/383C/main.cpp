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

// Segment tree for sum and range increment
struct SegmentTree {
  int n = 1;
  vector<ll> data, lazy;
  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.resize(2 * n);
    lazy.resize(2 * n);
  }
  ostream& print(ostream& o) {
    FOR(j, 1, 2 * n) {
      if (j > 1 && (j & (j - 1)) == 0) { o << endl; }
      o << data[j] << "#" << lazy[j] << "  ";
    }
    return o << endl;
  }

  ll value(int l, int r, int j) {
    return data[j] + lazy[j] * (r - l);
  }

  void push(int l, int r, int j) {
    data[j] = value(l, r, j);
    lazy[2 * j] += lazy[j];
    lazy[2 * j + 1] += lazy[j];
    lazy[j] = 0;
  }

  ll _incr(int ql, int qr, int qv, int l, int r, int j) {
    if (qr <= l || r <= ql) { return value(l, r, j); }
    if (ql <= l && r <= qr) { lazy[j] += qv; return value(l, r, j); }
    push(l, r, j);
    ll v0 = _incr(ql, qr, qv, l, (l + r) / 2, 2 * j);
    ll v1 = _incr(ql, qr, qv, (l + r) / 2, r, 2 * j + 1);
    return data[j] = v0 + v1;
  }

  void incr(int ql, int qr, int qv) {
    _incr(ql, qr, qv, 0, n, 1);
  }

  ll _reduce(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return 0; }
    if (ql <= l && r <= qr) { return value(l, r, j); }
    push(l, r, j);
    ll v0 = _reduce(ql, qr, l, (l + r) / 2, 2 * j);
    ll v1 = _reduce(ql, qr, (l + r) / 2, r, 2 * j + 1);
    return v0 + v1;
  }

  ll reduce(int ql, int qr) {
    return _reduce(ql, qr, 0, n, 1);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n);
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  vector<array<int, 3>> qs(nq, {-1, -1, -1});
  FOR(i, 0, nq) {
    cin >> qs[i][0];
    if (qs[i][0] == 1) { cin >> qs[i][1] >> qs[i][2]; }
    if (qs[i][0] == 2) { cin >> qs[i][1]; }
  }
  for (auto& [x, y] : edges) { x--; y--; }
  for (auto& [x, y, z] : qs) { y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS for subtree array and depth
  vector<int> depths(n);
  vector<int> sizes(n);
  vector<int> in_time(n);
  {
    int t = 0;
    function<void(int, int)> dfs = [&](int v, int vp) {
      in_time[v] = t++;
      sizes[v] = 1;
      for (auto u : adj[v]) {
        if (u == vp) { continue; }
        depths[u] = depths[v] + 1;
        dfs(u, v);
        sizes[v] += sizes[u];
      }
    };
    dfs(0, 0);
  }

  // Subtree as "in-time order" segment
  vector<SegmentTree> trees(2, n); // two for depth parity
  for (auto [t, v, x] : qs) {
    if (DEBUG) {
      trees[0].print(cout);
    }
    dbgv(t, v, x);
    int iv = in_time[v];
    bool d = depths[v] % 2;
    if (t == 1) {
      trees[ d].incr(iv, iv + sizes[v],  x);
      trees[!d].incr(iv, iv + sizes[v], -x);
    }
    if (t == 2) {
      ll res = trees[d].reduce(iv, iv + 1) + ls[v];
      cout << res << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/383C/main.cpp --check

%%%% begin
5 5
1 2 1 1 2
1 2
1 3
2 4
2 5
1 2 3
1 1 2
2 1
2 2
2 4
%%%%
3
3
0
%%%% end
*/
