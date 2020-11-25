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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Modulo integer
template<ll Modulo>
struct ModInt {
  using mint = ModInt;
  static constexpr ll modulo = Modulo;
  uint32_t v;
  ModInt() : v{0} {}
  template<class T, class = enable_if_t<is_integral_v<T>>>
  ModInt(T x) { ll y = (ll)x % modulo; if (y < 0) { y += modulo; } v = y; }
  friend istream& operator>>(istream& istr,       mint& self) { return istr >> self.v; }
  friend ostream& operator<<(ostream& ostr, const mint& self) { return ostr << self.v; }
  mint& operator+=(const mint& y) { v += y.v; while (v >= modulo) { v -= modulo; }; return *this; }
  mint& operator-=(const mint& y) { return *this += (modulo - y.v); }
  mint& operator*=(const mint& y) { v = (ll)v * y.v % modulo; return *this; }
  mint& operator/=(const mint& y) { return *this *= y.inv(); }
  friend mint operator+(const mint& x, const mint& y) { return mint(x) += y; }
  friend mint operator-(const mint& x, const mint& y) { return mint(x) -= y; }
  friend mint operator*(const mint& x, const mint& y) { return mint(x) *= y; }
  friend mint operator/(const mint& x, const mint& y) { return mint(x) /= y; }
  friend bool operator==(const mint& x, const mint& y) { return x.v == y.v; }
  friend bool operator!=(const mint& x, const mint& y) { return x.v != y.v; }
  mint operator-() const { return mint() - *this; }
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

const ll modulo = 1e9 + 9; // NOTE: it's not 10^9 + 7 !!!
using mint = ModInt<modulo>;

// GL math
template<class T, size_t N>
struct vec : array<T, N> {
  vec& operator+=(const vec& y) { for (size_t i = 0; i < N; i++) { (*this)[i] += y[i]; } return *this; }
  vec& operator-=(const vec& y) { for (size_t i = 0; i < N; i++) { (*this)[i] -= y[i]; } return *this; }
  vec& operator*=(const vec& y) { for (size_t i = 0; i < N; i++) { (*this)[i] *= y[i]; } return *this; }
  vec& operator/=(const vec& y) { for (size_t i = 0; i < N; i++) { (*this)[i] /= y[i]; } return *this; }
  vec& operator+=(T y) { for (size_t i = 0; i < N; i++) { (*this)[i] += y; } return *this; }
  vec& operator-=(T y) { for (size_t i = 0; i < N; i++) { (*this)[i] -= y; } return *this; }
  vec& operator*=(T y) { for (size_t i = 0; i < N; i++) { (*this)[i] *= y; } return *this; }
  vec& operator/=(T y) { for (size_t i = 0; i < N; i++) { (*this)[i] /= y; } return *this; }
  friend vec operator+(const vec& x, const vec& y) { return vec(x) += y; }
  friend vec operator-(const vec& x, const vec& y) { return vec(x) -= y; }
  friend vec operator*(const vec& x, const vec& y) { return vec(x) *= y; }
  friend vec operator/(const vec& x, const vec& y) { return vec(x) /= y; }
  friend vec operator+(const vec& x, T y) { return vec(x) += y; }
  friend vec operator-(const vec& x, T y) { return vec(x) -= y; }
  friend vec operator*(const vec& x, T y) { return vec(x) *= y; }
  friend vec operator/(const vec& x, T y) { return vec(x) /= y; }
};

template<class T, size_t N>
struct mat : array<array<T, N>, N> {
  mat() : mat(vec<T, N * N>()) { }
  mat(const vec<T, N * N>& x) {
    for (size_t i = 0; i < N; i++)
      for (size_t j = 0; j < N; j++)
        (*this)[i][j] = x[i * N + j];
  }
  static mat identity() {
    mat x;
    for (size_t i = 0; i < N; i++)
      for (size_t j = 0; j < N; j++)
        x[i][j] = (i == j);
    return x;
  }
  friend vec<T, N> operator*(const mat& x, const vec<T, N>& y) {
    vec<T, N> z = {};
    for (size_t i = 0; i < N; i++)
      for (size_t j = 0; j < N; j++)
        z[i] += x[i][j] * y[j];
    return z;
  }
  friend mat operator*(const mat& x, const mat& y) {
    mat z;
    for (size_t i = 0; i < N; i++)
      for (size_t j = 0; j < N; j++)
        for (size_t k = 0; k < N; k++)
          z[i][j] += x[i][k] * y[k][j];
    return z;
  }
};

using vec2 = vec<mint, 2>;
using vec3 = vec<mint, 3>;
using mat2 = mat<mint, 2>;
using mat3 = mat<mint, 3>;

// Segment tree
struct SegmentTree {
  int n_orig, n = 1;
  vector<mint> data;
  vector<vec2> lazy; // first two elements of Fibonacci recursion
  vector<mat2> precomp1;
  vector<mat3> precomp2;

  SegmentTree(int n_orig) : n_orig{n_orig} {
    while (n < n_orig) { n *= 2; }
    data.assign(2 * n, 0);
    lazy.assign(2 * n, vec2());

    // Precompute fibonacci operators
    mat2 fib = mat2({
      0, 1,
      1, 1
    });
    mat3 fibsum = mat3({
       0, 1, 0,
       0, 0, 1,
      -1, 0, 2
    });
    precomp1.resize(n);
    precomp2.resize(n);
    precomp1[0] = mat2::identity();
    precomp2[0] = mat3::identity();
    FOR(i, 1, n) {
      precomp1[i] = precomp1[i - 1] * fib;
      precomp2[i] = precomp2[i - 1] * fibsum;
    }
  }

  // Only for initialization
  void set(int qi, int qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = data[2 * j] + data[2 * j + 1];
    }
  }

  array<int, 2> toRange(int j) {
    assert(j > 0);
    int b = 31 - __builtin_clz(j);
    int s = n >> b;
    int i = j ^ (1 << b);
    return {s * i, s * (i + 1)};
  }

  mint value(int j) {
    if (lazy[j] == vec2()) { return data[j]; }

    auto [l, r] = toRange(j);
    int len = r - l;
    mint f0 = lazy[j][0];
    mint f1 = lazy[j][1];
    vec3 v = precomp2[len - 1] * vec3({f0, f0 + f1, 2 * (f0 + f1)});
    return data[j] + v[0];
  }

  void push(int j) {
    if (lazy[j] == vec2()) { return; }
    data[j] = value(j);

    auto [l, r] = toRange(j);
    int len = r - l;
    vec2 v = precomp1[len / 2] * lazy[j];
    lazy[2 * j] += lazy[j];
    lazy[2 * j + 1] += v;
    lazy[j] = vec2();
  }

  void incr(int ql, int qr) {
    function<mint(int, int, int)> rec = [&](int l, int r, int j) -> mint {
      if (qr <= l || r <= ql) { return value(j); }
      if (ql <= l && r <= qr) {
        lazy[j] += precomp1[l - ql] * vec2({1, 1});
        return value(j);
      }
      push(j);
      int m = (l + r) / 2;
      return data[j] = rec(l, m, 2 * j) + rec(m, r, 2 * j + 1);
    };
    rec(0, n, 1);
  }

  mint reduce(int ql, int qr) {
    function<mint(int, int, int)> rec = [&](int l, int r, int j) -> mint {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return value(j); }
      push(j);
      int m = (l + r) / 2;
      return rec(l, m, 2 * j) + rec(m, r, 2 * j + 1);
    };
    return rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 3 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, ls[i]); }

  for (auto [t, l, r] : qs) {
    l--;
    if (t == 1) {
      tree.incr(l, r);
    }
    if (t == 2) {
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
python misc/run.py codeforces/problemset/447E/main.cpp

%%%% begin
4 4
1 2 3 4
1 1 4
2 1 4
1 2 4
2 1 3
%%%%
17
12
%%%% end
*/
