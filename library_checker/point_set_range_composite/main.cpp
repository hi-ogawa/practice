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

const ll modulo = 998244353;
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
using mat2 = mat<mint, 2>;

// Segment tree
struct SegmentTree {
  using T = mat2;
  static inline T zero = mat2::identity();
  static inline T join(T lhs, T rhs) { return rhs * lhs; }

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
    int jl = ql + n, jr = qr + n;
    T res_l = zero, res_r = zero;
    for (; jl < jr; jl /= 2, jr /= 2) {
      if (jl % 2) { res_l = join(res_l, data[jl++]); }
      if (jr % 2) { res_r = join(data[--jr], res_r); }
    }
    return join(res_l, res_r);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 5 x 10^5]
  cin >> n >> nq;
  vector<array<mint, 2>> ls(n);
  cin >> ls;
  vector<array<int, 4>> qs(nq);
  cin >> qs;

  SegmentTree tree(n);
  FOR(i, 0, n) {
    auto [a, b] = ls[i];
    tree.set(i, mat2({a, b, 0, 1}));
  }

  for (auto [t, x, y, z] : qs) {
    if (t == 0) {
      tree.set(x, mat2({y, z, 0, 1}));
    }
    if (t == 1) {
      auto res = tree.reduce(x, y) * vec2({z, 1});
      cout << res[0] << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/point_set_range_composite/main.cpp

%%%% begin
5 5
1 2
3 4
5 6
7 8
9 10
1 0 5 11
1 2 4 12
0 1 13 14
1 0 4 15
1 2 5 16
%%%%
14005
470
8275
5500
%%%% end
*/
