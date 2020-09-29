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
  int v;
  ModInt() : v{0} {}
  template<class T> ModInt(T t) : v{static_cast<int>(t)} {}
  friend istream& operator>>(istream& istr, mint& self)       { return istr >> self.v; }
  friend ostream& operator<<(ostream& ostr, const mint& self) { return ostr << self.v; }

  mint& operator+=(mint o) { v = v + o.v; while (v >= modulo) { v -= modulo; }; return *this; }
  mint& operator-=(mint o) { return *this += (modulo - o.v); }
  mint& operator*=(mint o) { v = ((ll)v * o.v) % modulo; return *this; }
  mint& operator/=(mint o) { return *this *= o.inv(); }
  friend mint operator+(const mint& x, const mint& y) { return mint(x) += y; }
  friend mint operator-(const mint& x, const mint& y) { return mint(x) -= y; }
  friend mint operator*(const mint& x, const mint& y) { return mint(x) *= y; }
  friend mint operator/(const mint& x, const mint& y) { return mint(x) /= y; }
  friend bool operator==(const mint& x, const mint& y) { return x.v == y.v; }
  friend bool operator!=(const mint& x, const mint& y) { return x.v != y.v; }
  mint inv() const { return pow(modulo - 2); }
  mint pow(ll e) const {
    mint x = *this, res = 1;
    while (e > 0) {
      if (e & 1) { res *= x; }
      e >>= 1; x *= x;
    }
    return res;
  }

  // Generator
  static inline mint generator[2];
  static void findGenerator() {
    // Factorize "modulo - 1"
    ll x = modulo - 1;
    vector<int> ps;
    for (int p = 2; p * p <= x; p++) {
      if (x % p == 0) {
        ps.push_back(p);
        while (x % p == 0) { x /= p; }
      }
    }
    if (x > 1) { ps.push_back(x); }
    // Brute force generator
    for (int y = 2; y < modulo; y++) {
      bool ok = 1;
      for (auto p : ps) {
        if (mint(y).pow((modulo - 1) / p) == 1) { ok = 0; break; }
      }
      if (ok) {
        generator[0] = mint(y);
        generator[1] = mint(y).inv();
        return;
      }
    }
    assert(0);
  }
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
  // Precompute roots and their powers
  static bool first_run = true;
  static array<vector<vector<mint>>, 2> roots; // roots[inv][b][k] = (2^b root)^k
  static vector<mint> pow2_invs;
  constexpr int nb_max = 20;
  if (first_run) {
    first_run = false;
    mint::findGenerator();
    pow2_invs.resize(nb_max + 1);
    roots[0].resize(nb_max + 1);
    roots[1].resize(nb_max + 1);
    for (int b = 1; b <= nb_max; b++) {
      int l = 1 << b;
      pow2_invs[b] = mint(1 << b).inv();
      roots[0][b].resize(l / 2);
      roots[1][b].resize(l / 2);
      mint u0 = mint::generator[0].pow((mint::modulo - 1) / l);
      mint u1 = mint::generator[1].pow((mint::modulo - 1) / l);
      mint z0 = 1, z1 = 1;
      for (int k = 0; k < l / 2; k++) {
        roots[0][b][k] = z0;
        roots[1][b][k] = z1;
        z0 *= u0;
        z1 *= u1;
      }
    }
  }

  int n = f.size();
  assert(n <= (1 << nb_max));
  if (n == 1) { return; }

  int nb = 0;
  while ((1 << nb) < n) { nb++; }
  FOR(i, 0, n) {
    int j = reverse32(i) >> (32 - nb);
    if (i < j) { swap(f[i], f[j]); }
  }
  for (int lb = 1; lb <= nb; lb++) {
    int l = 1 << lb;
    auto& u = roots[inv][lb];
    for (int i = 0; i < n; i += l) {
      for (int k = 0; k < l / 2; k++) {
        auto x = f[i + k];
        auto y = f[i + k + l / 2] * u[k];
        f[i + k]         = x + y;
        f[i + k + l / 2] = x - y;
      }
    }
  }
  if (inv) {
    mint inv_n = pow2_invs[nb];
    for (auto& x : f) { x *= inv_n; }
  }
}

template<class T>
void polymul(vector<T>& p, vector<T>& q, vector<T>& r) {
  fft(p, 0); fft(q, 0);
  FOR(i, 0, (int)p.size()) { r[i] = p[i] * q[i]; }
  fft(r, 1);
}

int pow2Ceil(int n) {
  int m = 1;
  while (m < n) { m *= 2; }
  return m;
}

template<class T>
void polymul2(vector<T>& p, vector<T>& q, vector<T>& r) {
  int n = 2 * pow2Ceil(max(p.size(), q.size()));
  p.resize(n); q.resize(n); r.resize(n);
  polymul(p, q, r);
}

using mint = ModInt<998244353>; // = 1 + 2^23 x 7 x 17

void mainCase() {
  int n, m; // [1, 2^19]
  cin >> n >> m;
  vector<mint> p(n), q(m), r;
  cin >> p >> q;
  polymul2(p, q, r);

  int k = n + m - 1;
  FOR(i, 0, k) {
    cout << r[i] << " \n"[i == k - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/convolution_mod/main.cpp --check

%%%% begin
4 5
1 2 3 4
5 6 7 8 9
%%%%
5 16 34 60 70 70 59 36
%%%% end

%%%% begin
1 1
10000000
10000000
%%%%
871938225
%%%% end
*/
