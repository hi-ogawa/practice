// AC

// NOTE: actually we don't need segment tree since charater doesn't change...

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

// Segment tree for XOR sum
struct SegmentTree {
  int n = 1;
  using Node = int;
  static inline Node kZero = 0;
  vector<Node> data;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, kZero);
  }

  Node join(const Node& lhs, const Node& rhs) {
    return lhs ^ rhs;
  }

  void set(int qi, const Node& qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  Node reduce(int ql, int qr) {
    Node res = kZero;
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
  int n, nq; // [1, 5 x 10^5]
  cin >> n >> nq;
  vector<int> parents(n - 1);
  cin >> parents;
  string s; // lowercase
  cin >> s;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  vector<vector<int>> adj(n);
  FOR(i, 0, n - 1) {
    int x = i + 1, y = parents[i] - 1;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS for in-time, depth, etc...
  vector<int> in_times(n);
  vector<int> out_times(n);
  vector<int> depths(n);
  int time = 0;
  function<void(int, int)> dfs = [&](int v, int vp) {
    in_times[v] = time++;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      depths[u] = depths[v] + 1;
      dfs(u, v);
    }
    out_times[v] = time++;
  };
  dfs(0, 0);

  // Ordering for representing depth/subtree vertices as segment
  vector<array<int, 2>> order_data(n);
  FOR(v, 0, n) { order_data[v] = {depths[v], in_times[v]}; }

  vector<int> order(n);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return order_data[x] < order_data[y]; });
  sort(ALL(order_data));

  SegmentTree tree(n);
  FOR(i, 0, n) {
    int v = order[i];
    int t = s[v] - 'a';
    tree.set(i, (1 << t)); // Parity of character count for each type
  }

  auto solve = [&](int v, int h) -> bool {
    // Find corresponding segment
    int t0 = in_times[v];
    int t1 = out_times[v];
    array<int, 2> ql = {h, t0}, qr = {h, t1};
    auto itl = lower_bound(ALL(order_data), ql);
    auto itr = lower_bound(ALL(order_data), qr);
    int l = distance(order_data.begin(), itl);
    int r = distance(order_data.begin(), itr);

    // Count each characters by parity
    int p = tree.reduce(l, r);

    // Can make palindrome \iff at most single type uses odd number
    bool ok = __builtin_popcount(p) <= 1;

    return ok;
  };

  for (auto [v, h] : qs) {
    v--; h--;
    auto res = solve(v, h);
    cout << (res ? "Yes" : "No") << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/570D/main.cpp

%%%% begin
6 5
1 1 1 3 3
zacccd
1 1
3 3
4 1
6 1
1 2
%%%%
Yes
No
Yes
Yes
Yes
%%%% end
*/
