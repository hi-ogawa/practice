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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Segment tree for minimum position
struct SegmentTree {
  using T = pair<int, int>;
  static inline T zero = {1 << 30, -1};
  static T join(T lhs, T rhs) {
    return lhs.first < rhs.first ? lhs : rhs;
  }

  int n = 1;
  vector<T> data;

  SegmentTree(int n_orig) {
    while (n < n_orig) { n *= 2; }
    data.assign(2 * n, zero);
  }

  void set(int qi, T qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  T reduce(int ql, int qr) {
    T res = zero;
    int jl = ql + n, jr = qr + n;
    for (; jl < jr; jl /= 2, jr /= 2) {
      if (jl % 2) { res = join(res, data[jl++]); }
      if (jr % 2) { res = join(res, data[--jr]); }
    }
    return res;
  }
};

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ls1(n), ls2(n); // [1, n], pre-order, in-order
  cin >> ls1 >> ls2;

  for (auto& x : ls1) { x--; } // [0, n)
  for (auto& x : ls2) { x--; }

  // Re-label so that tree becomes binary heap
  auto perm = ls1;
  auto inv_perm = perm;
  FOR(i, 0, n) { inv_perm[perm[i]] = i; }
  FOR(i, 0, n) { ls2[i] = inv_perm[ls2[i]]; }
  dbg(ls2);

  // Make cartesian tree
  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, {ls2[i], i}); }

  vector<array<int, 2>> adj(n + 1, {-1, -1});
  function<void(int, int, int, int)> solve = [&](int l, int r, int p, int side) {
    auto [_x0, i0] = tree.reduce(l, r);
    adj[p][side] = i0;
    if (l < i0) { solve(l, i0, i0, 0); }
    if (i0 + 1 < r) { solve(i0 + 1, r, i0, 1); }
  };
  solve(0, n, n, 0);
  int root = adj[n][0];

  // DFS for post-order
  vector<int> out_times(n);
  int time = 0;
  function<void(int)> dfs = [&](int v) {
    for (auto u : adj[v]) {
      if (u == -1) { continue; }
      dfs(u);
    }
    out_times[v] = time++;
  };
  dfs(root);
  dbg(out_times);

  // Restore label
  vector<int> res(n);
  FOR(i, 0, n) {
    res[out_times[i]] = perm[ls2[i]];
  }
  dbg(res);

  FOR(i, 0, n) {
    cout << (res[i] + 1) << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1702/main.cpp

%%%% begin
5
5 3 2 1 4
3 5 1 2 4
%%%%
3 1 4 2 5
%%%% end
*/
