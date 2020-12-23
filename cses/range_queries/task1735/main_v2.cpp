// AC

// NOTE: Experiment with "unnecessary" abstraction...

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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

// Segment tree for range update and range reduction
template<class T1, class T2, class F1, class F2, class F3>
struct SegmentTree {
  T1 zero; T2 zero_lazy; F1 join; F2 join_lazy; F3 value;

  int n = 1;
  vector<T1> data;
  vector<T2> lazy;

  SegmentTree(int n_orig, T1 a, T2 b, F1 c, F2 d, F3 e) : zero{a}, zero_lazy{b}, join{c}, join_lazy{d}, value{e} {
    while (n < n_orig) { n *= 2; }
    data.assign(2 * n, zero);
    lazy.assign(2 * n, zero_lazy);
  }

  template<class Iter>
  void init(Iter first, Iter last) {
    auto it = first;
    for (int j = n; it != last; it++, j++) {
      data[j] = *it;
    }
    for (int j = n - 1; j >= 1; j--) {
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  void push(int j, int l, int r) {
    if (lazy[j] == zero_lazy) { return; }
    data[j] = value(data[j], lazy[j], l, r);
    lazy[2 * j    ] = join_lazy(lazy[2 * j    ], lazy[j]);
    lazy[2 * j + 1] = join_lazy(lazy[2 * j + 1], lazy[j]);
    lazy[j] = zero_lazy;
  }

  void update(int ql, int qr, T2 qv) {
    function<T1(int, int, int)> rec = [&](int l, int r, int j) -> T1 {
      if (qr <= l || r <= ql) { return value(data[j], lazy[j], l, r); }
      if (ql <= l && r <= qr) { lazy[j] = join_lazy(lazy[j], qv); return value(data[j], lazy[j], l, r); }
      push(j, l, r);
      int m = (l + r) / 2;
      return data[j] = join(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    rec(0, n, 1);
  }

  T1 reduce(int ql, int qr) {
    function<T1(int, int, int)> rec = [&](int l, int r, int j) -> T1 {
      if (qr <= l || r <= ql) { return zero; }
      if (ql <= l && r <= qr) { return value(data[j], lazy[j], l, r); }
      push(j, l, r);
      int m = (l + r) / 2;
      return join(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    return rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;

  using T1 = ll; // sum
  using T2 = pair<int, ll>; // (noop/set/incr, value)
  T1 zero = 0;
  T2 zero_lazy = {0, 0};
  auto join = [](T1 lhs, T1 rhs) -> T1 { return lhs + rhs; };
  auto join_lazy = [](T2 lhs, T2 rhs) -> T2 {
    auto [t1, v1] = lhs;
    auto [t2, v2] = rhs;
    if (t2 == 0) { return lhs; }          // (?, noop)    -> ?
    if (t2 == 1) { return rhs; }          // (?, set)     -> set
    if (t1 == 0) { return rhs; }          // (noop, incr) -> incr
    if (t1 == 1) { return {1, v1 + v2}; } // (set,  incr) -> set
    return {2, v1 + v2};                  // (incr, incr) -> incr
  };
  auto value = [](T1 v, T2 v_lazy, int l, int r) -> T1 {
    auto [t, u] = v_lazy;
    if (t == 0) { return v; }
    if (t == 1) { return (r - l) * u; }
    return v + (r - l) * u;
  };
  SegmentTree tree(n, zero, zero_lazy, join, join_lazy, value);
  tree.init(ALL(ls));

  FOR(_, 0, nq) {
    int t, l, r, x;
    cin >> t >> l >> r;
    l--;
    if (t == 1) {
      cin >> x;
      tree.update(l, r, {2, x});
    }
    if (t == 2) {
      cin >> x;
      tree.update(l, r, {1, x});
    }
    if (t == 3) {
      auto res = tree.reduce(l, r);
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
python misc/run.py cses/range_queries/task1735/main_v2.cpp

%%%% begin
6 5
2 3 1 1 5 3
3 3 5
1 2 4 2
3 3 5
2 2 4 5
3 3 5
%%%%
7
11
15
%%%% end
*/
