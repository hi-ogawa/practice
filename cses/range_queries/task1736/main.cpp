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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Segment tree (see task1735 for "request system")
struct SegmentTree {
  int depth_ = 0;
  vector<ll> data_;
  // req[j] = {a, b} means its segments has pending request [a, a + b, a + 2b, ...]
  vector<tuple<ll, ll>> req_;

  SegmentTree(int n) {
    while ((1 << depth_) < n) { depth_++; }
    int k = 1 << (depth_ + 1);
    data_.resize(k);
    req_.assign(k, {0, 0});
  }
  ostream& print(ostream& ostr) {
    FOR(d, 0, depth_ + 1) {
      int j0 = (1 << d) - 1;
      FOR(j, j0, j0 + (1 << d)) {
        if (j > j0) { ostr << "    "; }
        ostr << data_[j];
        auto [a, b] = req_[j];
        if (a > 0) { ostr << "#[" << a << "," << b << "]"; }
      }
      ostr << endl;
    }
    ostr << endl;
    return ostr;
  }
  int index(int qi) { return (1 << depth_) - 1 + qi; }
  int up(int j) { return (j - 1) / 2; }
  int left(int j) { return 2 * j + 1; }
  int right(int j) { return 2 * j + 2; }

  // Only for initialization
  void set(int qi, int qv) {
    int j = index(qi);
    data_[j] = qv;
    while (j > 0) {
      j = up(j);
      data_[j] = data_[left(j)] + data_[right(j)];
    }
  }

  // Merge with pending request
  void mergeRequest(ll qa, ll qb, int j) {
    auto [a, b] = req_[j];
    req_[j] = {a + qa, b + qb};
  }

  void propagateRequest(int l, int r, int j) {
    auto [a, b] = req_[j];
    req_[j] = {0, 0};
    int step = (r - l) / 2;
    mergeRequest(a, b, left(j));
    mergeRequest(a + step * b, b, right(j));
  }

  ll getValue(int l, int r, int j) {
    auto [a, b] = req_[j];
    ll res = data_[j];
    if (a >= 0) {
      ll c = r - l;
      res += ((a + a + (c - 1) * b) * c) / 2;
    }
    return res;
  }

  // @returns (l, r)-sum
  ll _incr(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return getValue(l, r, j); }
    if (ql <= l && r <= qr) { mergeRequest(1 + l - ql, 1, j); return getValue(l, r, j); }
    propagateRequest(l, r, j);
    int mid = (l + r) / 2;
    ll v1 = _incr(ql, qr, l, mid, left(j));
    ll v2 = _incr(ql, qr, mid, r, right(j));
    return data_[j] = v1 + v2;
  }
  void incr(int ql, int qr) {
    _incr(ql, qr, 0, 1 << depth_, 0);
  }

  // @returns ((ql, qr)-sum, (l, r)-sum)
  tuple<ll, ll> _reduce(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return {0, getValue(l, r, j)}; }
    if (ql <= l && r <= qr) { return {getValue(l, r, j), getValue(l, r, j)}; }
    propagateRequest(l, r, j);
    int mid = (l + r) / 2;
    auto [v1, u1] = _reduce(ql, qr, l, mid, left(j));
    auto [v2, u2] = _reduce(ql, qr, mid, r, right(j));
    return {v1 + v2, data_[j] = u1 + u2};
  }
  ll reduce(int ql, int qr) {
    return get<0>(_reduce(ql, qr, 0, 1 << depth_, 0));
  }
};

// Main
void mainCase() {
  int n, nq;
  cin >> n >> nq;
  vector<int> ls(n, 0);
  cin >> ls;
  vector<array<int, 3>> qs(nq, {0});
  cin >> qs;

  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, ls[i]); }
  // tree.print(cout);

  for (auto [t, a, b] : qs) {
    a--; b--;
    // DD(tie(t, a, b));
    if (t == 1) {
      tree.incr(a, b + 1);
    }
    if (t == 2) {
      ll res = tree.reduce(a, b + 1);
      // DD(res);
      cout << res << endl;
    }
    // tree.print(cout);
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
python misc/run.py cses/range_queries/task1736/main.cpp --check

%%%% begin
5 3
4 2 3 1 7
2 1 5
1 1 5
2 1 5
%%%%
17
32
%%%% end
*/
