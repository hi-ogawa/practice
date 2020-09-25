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

  mint& operator+=(const mint& y) { v += y.v; while (v >= modulo) { v -= modulo; }; return *this; }
  mint& operator-=(const mint& y) { return *this += (modulo - y.v); }
  mint& operator*=(const mint& y) { v = ((v * y.v) % modulo); return *this; }
  mint& operator/=(const mint& y) { return *this *= y.inv(); }
  friend mint operator+(const mint& x, const mint& y) { return mint(x) += y; }
  friend mint operator-(const mint& x, const mint& y) { return mint(x) -= y; }
  friend mint operator*(const mint& x, const mint& y) { return mint(x) *= y; }
  friend mint operator/(const mint& x, const mint& y) { return mint(x) /= y; }
  mint inv() { return pow(modulo - 2); }
  mint pow(ll e) {
    mint x = *this, res = 1;
    while (e > 0) {
      if (e & 1) { res *= x; }
      e >>= 1; x *= x;
    }
    return res;
  }

  static constexpr ll const_pow(ll x, ll e) {
    ll res = 1;
    while (e > 0) {
      if (e & 1) { res = (res * x) % modulo; }
      e >>= 1; x = (x * x) % modulo;
    }
    return res;
  }

  static constexpr ll const_findGenerator() {
    // Factorize "modulo - 1"
    ll x = modulo - 1;
    ll ps[20] = {};
    int n = 0;
    for (int p = 2; p * p <= x; p++) {
      if (x % p == 0) {
        while (x % p == 0) { x /= p; }
        ps[n++] = p;
      }
    }
    if (x > 1) { ps[n++] = x; }
    // Check generator
    for (ll y = 2; y < modulo; y++) {
      bool ok = 1;
      for (int i = 0; i < n; i++) {
        if (const_pow(y, (modulo - 1) / ps[i]) == 1) {
          ok = 0; break;
        }
      }
      if (ok) { return y; }
    }
    return -1; // assert(0); not supported by gcc?
  }

  static inline constexpr ll _generator = const_findGenerator();
  static mint generator() { return mint(_generator); }
};

// FFT
uint32_t reverse32(uint32_t x) {
  x = ((x & 0x55555555U) <<  1) | ((x & 0xaaaaaaaaU) >>  1); // 0101 = 0x5, 1010 = 0xa
  x = ((x & 0x33333333U) <<  2) | ((x & 0xccccccccU) >>  2); // 0011 = 0x3, 1100 = 0xc
  x = ((x & 0x0f0f0f0fU) <<  4) | ((x & 0xf0f0f0f0U) >>  4);
  x = ((x & 0x00ff00ffU) <<  8) | ((x & 0xff00ff00U) >>  8);
  x = ((x & 0x0000ffffU) << 16) | ((x & 0xffff0000U) >> 16);
  return x;
}

template<class mint>
void fft(vector<mint>& f, bool inv) {
  int n = f.size();
  int nb = 0;
  while ((1 << nb) < n) { nb++; }
  FOR(i, 0, n) {
    int j = reverse32(i) >> (32 - nb);
    if (i < j) { swap(f[i], f[j]); }
  }
  for (int lb = 1; lb <= nb; lb++) {
    int l = 1 << lb;
    mint u = mint::generator().pow((mint::modulo - 1) >> lb);
    if (inv) { u = u.inv(); }
    for (int i = 0; i < n; i += l) {
      mint z = 1;
      for (int k = 0; k < l / 2; k++) {
        auto& x = f[i + k];
        auto& y = f[i + k + l / 2];
        tie(x, y) = make_tuple(x + z * y, x - z * y);
        z *= u;
      }
    }
  }
  if (inv) {
    mint inv_n = mint(n).inv();
    for (auto& x : f) { x *= inv_n; }
  }
}

template<class mint>
void polymul(vector<mint>& p, vector<mint>& q, vector<mint>& r) {
  fft(p, 0); fft(q, 0);
  FOR(i, 0, (int)p.size()) { r[i] = p[i] * q[i]; }
  fft(r, 1);
}

int pow2Ceil(int n) {
  int b = 0;
  while ((1 << b) < n) { b++; }
  return 1 << b;
}

void normalize(vector<ll>& x) {
  const int base = 10;
  int i = 0;
  while (true) {
    ll q = x[i] / base, r = x[i] % base;
    x[i++] = r;
    if (i == (int)x.size() && q == 0) { break; }
    if (q == 0) { continue; }
    if (i == (int)x.size()) { x.resize(i); }
    x[i] += q;
  }
  int n = x.size();
  int m = 1;
  for (int j = n - 1; j >= 1; j--) {
    if (x[j] > 0) { m = j + 1; break; }
  }
  x.resize(m);
}

using mint = ModInt<998244353>; // 1 + 2^23 x 7 x 17 > (size) * (digit max)^2 = 1000 * 10 * 10

void bigmul(vector<ll>& x, vector<ll>& y, vector<ll>& z) {
  int n = 2 * pow2Ceil(max(x.size(), y.size()));
  vector<mint> p(ALL(x)), q(ALL(y));
  p.resize(n); q.resize(n);
  polymul(p, q, q);
  z = vector<ll>(ALL(q));
  normalize(z);
}

// Main
void mainCase() {
  string s1, s2; // [0, 10^1000]
  cin >> s1 >> s2;

  int n1 = s1.size(), n2 = s2.size();
  vector<ll> x1(n1), x2(n2);
  reverse(ALL(s1));
  reverse(ALL(s2));
  FOR(i, 0, n1) { x1[i] = s1[i] - '0'; }
  FOR(i, 0, n2) { x2[i] = s2[i] - '0'; }

  vector<ll> res;
  bigmul(x1, x2, res);

  int n = res.size();
  reverse(ALL(res));
  FOR(i, 0, n) {
    cout << res[i];
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 1000]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py spoj/MUL/main.cpp --check

%%%% begin
5
4 2
123 43
324 342
0 12
9999 12345
%%%%
8
5289
110808
0
123437655
%%%% end
*/
