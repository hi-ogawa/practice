// AFTER EDITORIAL, AC

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

const ll kInf = 1e18;

// Segment tree for range increase and minimum index
struct SegmentTree {
  int n = 1;

  using Node = tuple<ll, int>;
  static inline Node kZero = {kInf, -1};

  vector<Node> data;
  vector<ll> lazy;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, kZero);
    lazy.assign(2 * n, 0);
  }

  Node join(const Node& lhs, const Node& rhs) {
    auto [vl, _il] = lhs;
    auto [vr, _ir] = rhs;
    if (vl < vr) { return lhs; }
    return rhs;
  }

  // Only for initialization
  void set(int qi, ll qv) {
    int j = qi + n;
    data[j] = {qv, qi};
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  Node value(int, int, int j) {
    auto [v, i] = data[j];
    return {v + lazy[j], i};
  }

  void push(int l, int r, int j) {
    data[j] = value(l, r, j);
    lazy[2 * j] += lazy[j];
    lazy[2 * j + 1] += lazy[j];
    lazy[j] = 0;
  }

  void incr(int ql, int qr, ll qv) {
    function<Node(int, int, int)> rec = [&](int l, int r, int j) -> Node {
      if (qr <= l || r <= ql) { return value(l, r, j); }
      if (ql <= l && r <= qr) { lazy[j] += qv; return value(l, r, j); }
      push(l, r, j);
      int m = (l + r) / 2;
      return data[j] = join(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    rec(0, n, 1);
  }

  Node reduce(int ql, int qr) {
    function<Node(int, int, int)> rec = [&](int l, int r, int j) -> Node {
      if (qr <= l || r <= ql) { return kZero; }
      if (ql <= l && r <= qr) { return value(l, r, j); }
      push(l, r, j);
      int m = (l + r) / 2;
      return join(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    return rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<ll> ls(n);
  cin >> ls;

  SegmentTree tree(n);
  FOR(i, 0, n) {
    tree.set(i, ls[i]);
  }

  vector<int> res(n);
  FOR(x, 1, n + 1) {
    auto [v, i] = tree.reduce(0, n);
    dbg(x, v, i);
    assert(v == 0);
    res[i] = x;
    tree.incr(i + 1, n, -x);
    tree.incr(i, i + 1, kInf);
  }

  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1208D/main.cpp

%%%% begin
3
0 0 0
%%%%
3 2 1
%%%% end

%%%% begin
2
0 1
%%%%
1 2
%%%% end

%%%% begin
5
0 1 1 1 10
%%%%
1 4 3 2 5
%%%% end
*/
