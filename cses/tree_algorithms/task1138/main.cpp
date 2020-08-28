// AC

// Cf. task1136

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
  vector<int> ls(n, 0); // <= 10^9
  cin >> ls;
  vector<tuple<int, int>> edges(n - 1, {0, 0});
  cin >> edges;
  vector<tuple<int, int, int>> qs(nq, {0, 0, 0});
  FOR(i, 0, nq) {
    int a, b = -1, c = -1;
    cin >> a;
    if (a == 1) { cin >> b >> c; }
    if (a == 2) { cin >> b; }
    b--;
    qs[i] = {a, b, c};
  }
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS
  vector<int> in_time(n, -1);
  vector<int> size(n, -1);
  {
    int t = 0;
    function<void(int)> dfs = [&](int v) {
      in_time[v] = t++;
      size[v] = 1;
      for (auto u : adj[v]) {
        if (in_time[u] == -1) {
          dfs(u);
          size[v] += size[u];
        }
      }
    };
    dfs(0);
  }
  dbg(in_time); dbg(size);

  // Subtree sum as segment sum
  FenwickTree tree(n + 1); // range update & single get (difference array)
  FOR(v, 0, n) {
    // range update
    tree.incr(in_time[v], ls[v]);
    tree.incr(in_time[v] + size[v], -ls[v]);
  }

  // Answer query
  for (auto [t, x, y] : qs) {
    if (t == 1) {
      // range update
      ll z = y - ls[x];
      tree.incr(in_time[x], z);
      tree.incr(in_time[x] + size[x], -z);
      ls[x] = y;
    }
    if (t == 2) {
      // single get
      ll res = tree.reduce(in_time[x] + 1);
      cout << res << endl;
    }
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
python misc/run.py cses/tree_algorithms/task1138/main.cpp --check

%%%% begin
5 3
4 2 5 2 1
1 2
1 3
3 4
3 5
2 4
1 3 2
2 4
%%%%
11
8
%%%% end
*/
