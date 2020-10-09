// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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

// Number theoretic transform
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
  // Precomputation on first run
  static struct Precopute {
    int nb_lim = 0;
    array<mint, 2> generator;
    array<vector<vector<mint>>, 2> roots; // roots[inv][b][k] = (2^b root)^k
    vector<mint> inverses;
    Precopute() {
      findGenerator();
      findRoots();
      findInverses();
    }
    void findGenerator() {
      // Factorize "p - 1"
      int x = mint::modulo - 1;
      vector<int> ps;
      for (int p = 2; p * p <= x; p++) {
        if (x % p == 0) {
          while (x % p == 0) { x /= p; }
          ps.push_back(p);
        }
      }
      if (x > 1) { ps.push_back(x); }
      // Brute force generator
      bool ok = 0;
      for (int g = 2; g < mint::modulo; g++) {
        ok = 1;
        for (auto p : ps) {
          if (mint(g).pow((mint::modulo - 1) / p) == 1) { ok = 0; break; }
        }
        if (ok) {
          generator[0] = g;
          generator[1] = mint(g).inv();
          break;
        }
      }
      assert(ok);
    }
    void findRoots() {
      while ((mint::modulo - 1) % (1 << nb_lim) == 0) { nb_lim++; }
      roots[0].resize(nb_lim);
      roots[1].resize(nb_lim);
      FOR(b, 1, nb_lim) {
        int l = 1 << b;
        roots[0][b].resize(l / 2);
        roots[1][b].resize(l / 2);
        mint u0 = generator[0].pow((mint::modulo - 1) / l);
        mint u1 = generator[1].pow((mint::modulo - 1) / l);
        mint z0 = 1, z1 = 1;
        for (int k = 0; k < l / 2; k++) {
          roots[0][b][k] = z0;
          roots[1][b][k] = z1;
          z0 *= u0; z1 *= u1;
        }
      }
    }
    void findInverses() {
      inverses.resize(nb_lim);
      mint inv2 = mint(2).inv();
      inverses[1] = inv2;
      FOR(b, 2, nb_lim) { inverses[b] = inverses[b - 1] * inv2; }
    }
  } precompute;

  // Usual FFT
  int n = f.size();
  if (n == 1) { return; }

  int nb = 0;
  while ((1 << nb) < n) { nb++; }
  assert(nb < precompute.nb_lim);

  FOR(i, 0, n) {
    int j = reverse32(i) >> (32 - nb);
    if (i < j) { swap(f[i], f[j]); }
  }

  for (int lb = 1; lb <= nb; lb++) {
    int l = 1 << lb;
    auto& u = precompute.roots[inv][lb];
    for (int i = 0; i < n; i += l) {
      for (int k = 0; k < l / 2; k++) {
        mint x = f[i + k];
        mint y = f[i + k + l / 2] * u[k];
        f[i + k]         = x + y;
        f[i + k + l / 2] = x - y;
      }
    }
  }

  if (inv) {
    mint n_inv = precompute.inverses[nb];
    for (auto& x : f) { x *= n_inv; }
  }
}

template<class T>
void polymul(vector<T>& p, vector<T>& q, vector<T>& r) {
  fft(p, 0); fft(q, 0);
  FOR(i, 0, (int)p.size()) { r[i] = p[i] * q[i]; }
  fft(r, 1);
}

int ceilPowerOfTwo(int n) {
  int m = 1;
  while (m < n) { m *= 2; }
  return m;
}

template<class T>
void polymul2(vector<T>& p, vector<T>& q, vector<T>& r) {
  int n = 2 * ceilPowerOfTwo(max(p.size(), q.size()));
  p.resize(n); q.resize(n); r.resize(n);
  polymul(p, q, r);
  while (r.size() && r.back() == 0) { r.pop_back(); }
}

// Polynomial
template<class mint>
struct Poly {
  vector<mint> v;
  Poly() {}
  Poly(mint x) : v{{x}} {}
  Poly(const vector<mint>& _v) : v{_v} {}
  friend istream& operator>>(istream& istr,       Poly& self) { return istr >> self.v; }
  friend ostream& operator<<(ostream& ostr, const Poly& self) { return ostr << self.v; }

  mint get(int i) const { return i < (int)v.size() ? v[i] : 0; }
  Poly& operator+=(const Poly& o) {
    int n = max(v.size(), o.v.size());
    v.resize(n);
    for (int i = 0; i < n; i++) { v[i] += o.get(i); }
    return *this;
  }
  Poly& operator-=(const Poly& o) {
    int n = max(v.size(), o.v.size());
    v.resize(n);
    for (int i = 0; i < n; i++) { v[i] -= o.get(i); }
    return *this;
  }
  Poly& operator*=(const Poly& o) {
    auto ov = o.v;
    polymul2(ov, v, v);
    return *this;
  }
  friend Poly operator+(const Poly& f, const Poly& g) { return Poly(f) += g; }
  friend Poly operator-(const Poly& f, const Poly& g) { return Poly(f) -= g; }
  friend Poly operator*(const Poly& f, const Poly& g) { return Poly(f) *= g; }

  // f = a(k-1) x^(k-1) + ... a1 x^1 + a0 (mod x^k)
  Poly modx(int k) const {
    return {{vector(v.begin(), v.begin() + min(k, (int)v.size()))}};
  }

  // f.g = r.x^k + 1
  Poly inv(int k) const {
    assert(k > 0);
    auto& f = *this;
    Poly g = f.get(0).inv();
    for (int i = 2; i <= 2 * k; i *= 2) {
      // NOTE: Actually you need to take care some factors from "modx" but mostly it can be proved like this:
      // f.g = r.x^k + 1  ==>
      // f.g.(2 - f.g) = (r.x^k + 1)(-r.x^k + 1) = r'.x^2k + 1
      g = (g * (Poly(2) - (f.modx(i) * g).modx(i))).modx(i);
    }
    return g.modx(k);
  }
};

using mint = ModInt<998244353>; // = 1 + 2^23 x 7 x 17

// Main
void mainCase() {
  int n; // [1, 5 x 10^5]
  cin >> n;
  vector<mint> v(n);
  cin >> v;

  Poly<mint> f(v);
  dbg(f);

  auto g = f.inv(n);
  dbg(g, f * g);

  FOR(i, 0, n) {
    cout << g.get(i) << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/inv_of_formal_power_series/main.cpp

%%%% begin
5
5 4 3 2 1
%%%%
598946612 718735934 862483121 635682004 163871793
%%%% end
*/
