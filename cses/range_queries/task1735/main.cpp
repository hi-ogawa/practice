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

// Segment tree
struct SegmentTree {
  int depth_ = 0;
  vector<ll> data_;
  vector<ll> req_incr_; // at most one request is pending
  vector<ll> req_set_;

  SegmentTree(int n) {
    while ((1 << depth_) < n) { depth_++; }
    int k = 1 << (depth_ + 1);
    data_.resize(k);
    req_set_.assign(k, -1);
    req_incr_.assign(k, -1);
  }
  ostream& print(ostream& ostr) {
    FOR(d, 0, depth_ + 1) {
      int j0 = (1 << d) - 1;
      FOR(j, j0, j0 + (1 << d)) {
        if (j > j0) { ostr << "  "; }
        ostr << data_[j];
        if (req_set_[j] >= 0) { ostr << "#" << req_set_[j]; }
        if (req_incr_[j] >= 0) { ostr << "%" << req_incr_[j]; }
      }
      ostr << endl;
    }
    ostr << endl;
    return ostr;
  }

  // Merge with pending request if any
  void mergeRequest(int qt, ll qv, int j) { // qt = 1 (incr), 2 (set)
    // incr, incr => incr
    // incr, set  => set
    // set,  incr => set
    // set,  set  => set
    ll ri = req_incr_[j], rs = req_set_[j];
    assert((ri == -1 || rs == -1));
    if (ri == -1 && rs == -1) {
      if (qt == 1) { req_incr_[j] = qv; }
      if (qt == 2) { req_set_[j] = qv; }
      return;
    }
    if (ri >= 0 && qt == 1) {
      req_incr_[j] = ri + qv;
      req_set_[j] = -1;
    }
    if (ri >= 0 && qt == 2) {
      req_incr_[j] = -1;
      req_set_[j] = qv;
    }
    if (rs >= 0 && qt == 1) {
      req_incr_[j] = -1;
      req_set_[j] = rs + qv;
    }
    if (rs >= 0 && qt == 2) {
      req_incr_[j] = -1;
      req_set_[j] = qv;
    }
  }

  void propagateRequest(int j) {
    int j1 = 2 * j + 1;
    int j2 = 2 * j + 2;
    ll ri = req_incr_[j], rs = req_set_[j];
    assert((ri == -1 || rs == -1));
    if (ri >= 0) {
      req_incr_[j] = -1;
      mergeRequest(1, ri, j1); mergeRequest(1, ri, j2);
    }
    if (rs >= 0) {
      req_set_[j] = -1;
      mergeRequest(2, rs, j1); mergeRequest(2, rs, j2);
    }
  }

  ll getValue(int l, int r, int j) {
    ll ri = req_incr_[j], rs = req_set_[j];
    assert((ri == -1 || rs == -1));
    if (ri >= 0) { return data_[j] + (r - l) * ri; }
    if (rs >= 0) { return (r - l) * rs; }
    return data_[j];
  }

  // @returns (l, r)-sum
  ll _set(int ql, int qr, ll qv, int l, int r, int j) {
    // No intersection
    if (qr <= l || r <= ql) {
      return getValue(l, r, j);
    }
    // Totally contained
    if (ql <= l && r <= qr) {
      mergeRequest(2, qv, j);
      return getValue(l, r, j);
    }
    // Split to children (resolve requests (current and pending) and apply to data_[j])
    propagateRequest(j); // propagate pending request first
    int mid = (l + r) / 2;
    ll v1 = _set(ql, qr, qv, l, mid, 2 * j + 1);
    ll v2 = _set(ql, qr, qv, mid, r, 2 * j + 2);
    return data_[j] = v1 + v2;
  }
  void set(int ql, int qr, ll qv) {
    _set(ql, qr, qv, 0, 1 << depth_, 0);
  }

  ll _incr(int ql, int qr, ll qv, int l, int r, int j) {
    if (qr <= l || r <= ql) { return getValue(l, r, j); }
    if (ql <= l && r <= qr) { mergeRequest(1, qv, j); return getValue(l, r, j); }
    propagateRequest(j);
    int mid = (l + r) / 2;
    ll v1 = _incr(ql, qr, qv, l, mid, 2 * j + 1);
    ll v2 = _incr(ql, qr, qv, mid, r, 2 * j + 2);
    return data_[j] = v1 + v2;
  }
  void incr(int ql, int qr, ll qv) {
    _incr(ql, qr, qv, 0, 1 << depth_, 0);
  }

  // @returns ((ql, qr)-sum, (l, r)-sum)
  tuple<ll, ll> _reduce(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return {0, getValue(l, r, j)}; }
    if (ql <= l && r <= qr) { return {getValue(l, r, j), getValue(l, r, j)}; }
    propagateRequest(j);
    int mid = (l + r) / 2;
    auto [v1, u1] = _reduce(ql, qr, l, mid, 2 * j + 1);
    auto [v2, u2] = _reduce(ql, qr, mid, r, 2 * j + 2);
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
  vector<array<int, 4>> qs(nq, {0});
  FOR(iq, 0, nq) {
    int t, a, b, c; t = a = b = c = -1;
    cin >> t;
    if (t == 1 || t == 2) { cin >> a >> b >> c; }
    if (t == 3) { cin >> a >> b; }
    qs[iq] = {t, a, b, c};
  }
  // DD(qs);

  SegmentTree tree(n);
  FOR(i, 0, n) {
    tree.set(i, i + 1, ls[i]);
  }
  // tree.print(cout);

  for (auto [t, a, b, c] : qs) {
    a--; b--;
    // DD(tie(t, a, b, c));
    if (t == 1) {
      tree.incr(a, b + 1, c);
    }
    if (t == 2) {
      tree.set(a, b + 1, c);
    }
    if (t == 3) {
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
python misc/run.py cses/range_queries/task1735/main.cpp --check

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
