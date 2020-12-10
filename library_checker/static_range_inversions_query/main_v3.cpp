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

// Fenwick tree for range sum
struct FenwickTree {
  using T = int;
  int n;
  vector<int> data;
  FenwickTree(int n) : n{n} {
    data.resize(n);
  }
  void incr(int qi, T qv) {
    int i = qi;
    while (i < n) {
      data[i] += qv;
      i = (i | (i + 1));
    }
  }
  T reduce(int qi) { // [0, qi)
    int i = qi - 1;
    T res = 0;
    while (i >= 0) {
      res += data[i];
      i = (i & (i + 1)) - 1;
    }
    return res;
  }
  T reduce(int ql, int qr) { // [ql, qr)
    return reduce(qr) - reduce(ql);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [0, 10^9]
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  // Compress value into [0, n)
  vector<int> dec = ls;
  sort(ALL(dec));
  for (auto& x : ls) { x = distance(dec.begin(), lower_bound(ALL(dec), x)); }
  dbg(ls);

  // Mo's algorithm
  int n_blk = sqrt(n);
  auto compare = [&](auto x, auto y) {
    x[0] /= n_blk; y[0] /= n_blk;
    return x < y;
  };
  vector<int> order(nq);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return compare(qs[x], qs[y]); });

  // State
  ll cnt = 0;
  int l = n_blk, r = l;
  FenwickTree tree(n);

  vector<ll> res(nq);
  FOR(o, 0, nq) {
    int qi = order[o];
    auto [ql, qr] = qs[qi];

    // Reset state when left block changes
    if (l <= ql) {
      l = ((ql / n_blk) + 1) * n_blk;
      r = l;
      cnt = 0;
      tree = FenwickTree(n);
    }

    // Extend [r, qr)
    for (; r < qr; r++) {
      cnt += tree.reduce(ls[r] + 1, n);
      tree.incr(ls[r], 1);
    }

    // Temporary update [ql, sep)
    int sep = min(l, qr);
    for (int i = sep - 1; i >= ql; i--) {
      cnt += tree.reduce(0, ls[i]);
      tree.incr(ls[i], 1);
    }
    res[qi] = cnt;
    for (int i = ql; i < sep; i++) {
      tree.incr(ls[i], -1);
      cnt -= tree.reduce(0, ls[i]);
    }
  }

  for (auto x : res) {
    cout << x << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/static_range_inversions_query/main_v3.cpp

%%%% begin
4 2
4 1 4 0
1 3
0 4
%%%%
0
4
%%%% end
*/
