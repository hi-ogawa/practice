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

// Modulo
template<ll Modulo>
struct ModInt {
  using mint = ModInt;
  static constexpr ll modulo = Modulo;
  ll v;
  ModInt() : v{0} {}
  template<class T> ModInt(T x) : v{static_cast<ll>(x)} {}
  template<class T> operator T() { return static_cast<T>(v); }
  friend ostream& operator<<(ostream& ostr, const mint& self) { return ostr << self.v; }

  mint& operator+=(const mint& y) { v += y.v; while (v >= modulo) { v -= modulo; }; return *this; }
  mint& operator-=(const mint& y) { return *this += (modulo - y.v); }
  mint& operator*=(const mint& y) { v = ((v * y.v) % modulo); return *this; }
  mint& operator/=(const mint& y) { return *this *= y.inv(); }
  friend mint operator+(const mint& x, const mint& y) { return mint(x) += y; }
  friend mint operator-(const mint& x, const mint& y) { return mint(x) -= y; }
  friend mint operator*(const mint& x, const mint& y) { return mint(x) *= y; }
  friend mint operator/(const mint& x, const mint& y) { return mint(x) /= y; }
  mint inv() const { return pow(modulo - 2); }
  mint pow(ll e) const {
    mint x = *this, res = 1;
    while (e > 0) {
      if (e & 1) { res *= x; }
      e >>= 1; x *= x;
    }
    return res;
  }
};

using mint = ModInt<998244353>;

// Segment tree for range set and cumstom reduction
struct SegmentTree {
  int n = 1;
  vector<mint> data;
  vector<int> lazy;

  // Precomputation
  mint inv_b_sub_1;
  vector<mint> pows;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.resize(n * 2);
    lazy.assign(n * 2, -1);

    // Precomputatoin
    const mint b = 10;
    inv_b_sub_1 = (b - 1).inv();
    pows.resize(n + 1);
    pows[0] = 1;
    FOR(i, 0, n) {
      pows[i + 1] = pows[i] * b;
    }
  }

  mint value(int l, int r, int j) {
    if (lazy[j] == -1) { return data[j]; }
    // (b^l + ... + b^(r - 1)) x d
    return (pows[r] - pows[l]) * inv_b_sub_1 * mint(lazy[j]);
  }

  void push(int l, int r, int j) {
    if (lazy[j] == -1) { return; }
    data[j] = value(l, r, j);
    lazy[j * 2] = lazy[j * 2 + 1] = lazy[j];
    lazy[j] = -1;
  }

  mint _set(int ql, int qr, int qv, int l, int r, int j) {
    if (qr <= l || r <= ql) { return value(l, r, j); }
    if (ql <= l && r <= qr) { lazy[j] = qv; return value(l, r, j); }
    push(l, r, j);
    mint v1 = _set(ql, qr, qv, l, (l + r) / 2, j * 2);
    mint v2 = _set(ql, qr, qv, (l + r) / 2, r, j * 2 + 1);
    return data[j] = v1 + v2;
  }

  void set(int ql, int qr, int qv) {
    _set(ql ,qr, qv, 0, n, 1);
  }

  mint _reduce(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return 0; }
    if (ql <= l && r <= qr) { return value(l, r, j); }
    push(l, r, j);
    mint v1 = _reduce(ql, qr, l, (l + r) / 2, j * 2);
    mint v2 = _reduce(ql, qr, (l + r) / 2, r, j * 2 + 1);
    return v1 + v2;
  }

  mint reduce(int ql, int qr) {
    return _reduce(ql, qr, 0, n, 1);
  }
};

// Main
void mainCase() {
  int n, nq;
  cin >> n >> nq;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  SegmentTree tree(n);
  tree.set(0, n, 1);

  for (auto [l, r, d] : qs) {
    tree.set(n - r, n - l + 1, d);
    mint res = tree.reduce(0, n);
    cout << res << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abl0/e/main.cpp --check

%%%% begin
8 5
3 6 2
1 4 7
3 8 3
2 2 2
4 5 1
%%%%
11222211
77772211
77333333
72333333
72311333
%%%% end

%%%% begin
200000 1
123 456 7
%%%%
641437905
%%%% end
*/
