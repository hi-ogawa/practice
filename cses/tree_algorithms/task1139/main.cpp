// AC

// Cf. task1137 and task1734

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
  int n; // <= 10^6
  cin >> n;
  vector<int> ls(n, 0);
  cin >> ls;
  vector<tuple<int, int>> edges(n - 1, {0, 0});
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS
  vector<int> in_time(n, -1);
  vector<int> size(n);
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

  vector<int> in_time_inv(n, 0);
  FOR(i, 0, n) { in_time_inv[in_time[i]] = i; }

  // Track sliding left-most uniqueness (cf. task1734)
  FenwickTree tree(n);
  map<int, int> mapping;
  vector<int> res(n);
  for (int i = n - 1; i >= 0; i--) {
    int v = in_time_inv[i];
    int x = ls[v];
    if (mapping.count(x)) {
      tree.incr(mapping[x], -1);
    }
    mapping[x] = i;
    tree.incr(i, 1);
    res[v] = tree.reduce(i, i + size[v]);
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
python misc/run.py cses/tree_algorithms/task1139/main.cpp --check

%%%% begin
5
2 3 2 2 1
1 2
1 3
3 4
3 5
%%%%
3 1 2 1 1
%%%% end
*/
