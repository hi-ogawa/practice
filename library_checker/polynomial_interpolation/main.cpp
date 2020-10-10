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
}

template<class D>
struct Polynomial {
  using poly = Polynomial;
  vector<D> v;
  Polynomial() {}
  Polynomial(D v) : v{vector<D>({v})} {}
  Polynomial(const vector<D> v) : v{v} { normalize(); }
  friend ostream& operator<<(ostream& ostr, const poly& self) { return ostr << self.v; }

  D get(int i) const { return i < (int)v.size() ? v[i] : 0; }
  poly& normalize() { while (v.size() && v.back() == 0) { v.pop_back(); }; return *this; }

  poly& operator+=(const poly& g) {
    v.resize(max(v.size(), g.v.size()));
    FOR(i, 0, (int)v.size()) { v[i] += g.get(i); }
    return normalize();
  }
  poly& operator-=(const poly& g) {
    v.resize(max(v.size(), g.v.size()));
    FOR(i, 0, (int)v.size()) { v[i] -= g.get(i); }
    return normalize();
  }
  poly& operator*=(const poly& g) {
    auto gv = g.v;
    polymul2(gv, v, v);
    return normalize();
  }
  poly& operator/=(const poly& g) {
    assert(g.v.size());
    int n = v.size(), m = g.v.size();
    if (n < m) { return *this = poly(0); }
    int k = n - m + 1;
    return *this = (this->rev().modx(k) * g.rev().inv(k)).modx(k).rev();
  }
  poly& operator%=(const poly& g) {
    return *this -= (*this / g) * g;
  }

  friend poly operator+(const poly& f, const poly& g) { return poly(f) += g; }
  friend poly operator-(const poly& f, const poly& g) { return poly(f) -= g; }
  friend poly operator*(const poly& f, const poly& g) { return poly(f) *= g; }
  friend poly operator/(const poly& f, const poly& g) { return poly(f) /= g; }
  friend poly operator%(const poly& f, const poly& g) { return poly(f) %= g; }

  poly rev() const {
    auto g = *this;
    reverse(ALL(g.v));
    return g.normalize();
  }

  poly modx(int k) const {
    return poly({v.begin(), v.begin() + min(k, (int)v.size())});
  }

  poly inv(int k) const {
    assert(k > 0 && get(0) != 0);
    auto& f = *this;
    poly g = poly(1 / f.get(0));
    for (int i = 2; i < 2 * k; i *= 2) {
      g = (g * (poly(2) - (f.modx(i) * g).modx(i))).modx(i);
    }
    return g.modx(k);
  }

  D eval(D x) const {
    D res = 0, xi = 1;
    FOR(i, 0, (int)v.size()) {
      res += v[i] * xi;
      xi *= x;
    }
    return res;
  }

  poly derivative() const {
    auto g = *this;
    FOR(i, 0, (int)v.size() - 1) {
      g.v[i] = g.v[i + 1] * (i + 1);
    }
    if (v.size()) { g.v.pop_back(); }
    return g.normalize();
  }
};

template<class D>
struct MultipointEvaluation {
  using poly = Polynomial<D>;
  vector<D> res;

  MultipointEvaluation(const poly& f, const vector<D>& xs) {
    vector<poly> ps;

    int n_orig = xs.size();
    int n = 1;
    while (n < n_orig) { n *= 2; }

    res.resize(n);
    ps.resize(2 * n);

    function<void(int, int, int)> rec1 = [&](int l, int r, int j) {
      if (l + 1 == r) {
        ps[j] = l < n_orig ? poly({-xs[l], 1}) : poly(1);
        return;
      }
      rec1(l, (l + r) / 2, 2 * j);
      rec1((l + r) / 2, r, 2 * j + 1);
      ps[j] = ps[2 * j] * ps[2 * j + 1];
    };
    rec1(0, n, 1);

    function<void(int, int, int, const poly&)> rec2 = [&](int l, int r, int j, const poly& g) {
      if (l + 1 == r) {
        res[l] = l < n_orig ? g.eval(xs[l]) : 0;
        return;
      }
      rec2(l, (l + r) / 2, 2 * j    , g % ps[2 * j]);
      rec2((l + r) / 2, r, 2 * j + 1, g % ps[2 * j + 1]);
    };
    rec2(0, n, 1, f);
  }
};

template<class D>
struct Interpolation {
  using poly = Polynomial<D>;
  vector<poly> res;

  Interpolation(const vector<D>& xs, const vector<D>& ys) {
    vector<poly> ps;
    poly dp;

    int n_orig = xs.size();
    int n = 1;
    while (n < n_orig) { n *= 2; }

    ps.resize(2 * n);
    res.resize(2 * n);

    // p = (x - xl)...(x - xr-1)
    function<void(int, int, int)> rec1 = [&](int l, int r, int j) {
      if (l + 1 == r) {
        ps[j] = l < n_orig ? poly({-xs[l], 1}) : poly(1);
        return;
      }
      rec1(l, (l + r) / 2, 2 * j);
      rec1((l + r) / 2, r, 2 * j + 1);
      ps[j] = ps[2 * j] * ps[2 * j + 1];
    };
    rec1(0, n, 1);

    // dp_eval[i] = ∏{j ≠ i} (xi - xj)
    dp = ps[1].derivative();
    MultipointEvaluation dp_eval(dp, xs);

    // ∑i yi ∏j (x - xj) / (xi - xj)
    function<void(int, int, int)> rec2 = [&](int l, int r, int j) {
      if (l + 1 == r) {
        res[j] = l < n_orig ? ys[l] / dp_eval.res[l] : 0;
        return;
      }
      rec2(l, (l + r) / 2, 2 * j);
      rec2((l + r) / 2, r, 2 * j + 1);
      res[j] += res[2 * j] * ps[2 * j + 1];
      res[j] += res[2 * j + 1] * ps[2 * j];
    };
    rec2(0, n, 1);
  }
};

using mint = ModInt<998244353>;
using poly = Polynomial<mint>;

// Main
void mainCase() {
  int n; // [1, 2^17]
  cin >> n;
  vector<mint> xs(n), ys(n);
  cin >> xs >> ys;

  Interpolation<mint> interp(xs, ys);
  auto res = interp.res[1];

  FOR(i, 0, n) {
    cout << res.get(i) << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/polynomial_interpolation/main.cpp

%%%% begin
5
5 6 7 8 9
586 985 1534 2257 3178
%%%%
1 2 3 4 0
%%%% end

%%%% begin
1
10000000
10000000
%%%%
10000000
%%%% end
*/
