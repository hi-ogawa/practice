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

  // Factorial, binomial
  static inline vector<mint> facts[2];
  static void makeFactorials(int n) {
    facts[0].assign(n + 1, 1);
    facts[1].assign(n + 1, 1);
    for (int i = 2; i <= n; i++) {
      facts[0][i] = facts[0][i - 1] * i;
    }
    facts[1][n] = facts[0][n].inv();
    for (int i = n - 1; i >= 2; i--) {
      facts[1][i] = facts[1][i + 1] * (i + 1);
    }
  }
  static mint binom(int n, int k) {
    if (n < k) { return 0; }
    return facts[0][n] * facts[1][n - k] * facts[1][k];
  }
};

const ll modulo = 1e9 + 7;
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
  mat pow(ll e) const {
    mat x = *this, res = mat::identity();
    while (e > 0) {
      if (e & 1) { res = res * x; }
      e >>= 1; x = x * x;
    }
    return res;
  }
};

using Mat = mat<mint, 100>;

// Main
void mainCase() {
  ll n, m; // [1, 10^18], [2, 100]
  cin >> n >> m;
  m--; // [1, 99]

  //
  // PROP.
  //   Define
  //     f(n, m) = ∑_{k} binom(n - km, k)
  //   Then
  //     f(n + 2, m)
  //        = ∑ binom(n + 2 - km, k)
  //        = ∑ binom(n + 1 - km, k) + binom(n + 1 - km, k - 1)
  //        = ∑ binom(n + 1 - km, k) + binom(n + 1 - m - (k - 1)m, k - 1)
  //        = f(n + 1, m) + ∑ binom(n + 1 - m, m)
  //   i.e.
  //     f(n + m + 1, m) = f(n + m) + f(n)
  //
  //   Thus, f(n, m) is m-degree linear recurrence.
  //

  //
  // a = | 0 1 0 .. 0 |
  //     | 0 0 1 .. 0 |
  //     |  ...       |
  //     | 1 0 0 .. 1 |
  //
  // b = | f(0) 0 .. 0 |
  //     | f(1) 0 .. 0 |
  //     | ...         |
  //     | f(m) 0 .. 0 |
  //
  Mat a, b;
  a[m][0] = a[m][m] = 1;
  FOR(i, 0, m) {
    a[i][i + 1] = 1;
  }

  mint::makeFactorials(m);
  FOR(i, 0, m + 1) {
    FOR(j, 0, i + 1) {
      b[i][0] += mint::binom(i - j * m, j);
    }
  }
  Mat c = a.pow(n) * b;
  dbg(a, a.pow(n), b, c);

  mint res = c[0][0];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1117D/main.cpp

%%%% begin
4 2
%%%%
5
%%%% end

%%%% begin
3 2
%%%%
3
%%%% end
*/
