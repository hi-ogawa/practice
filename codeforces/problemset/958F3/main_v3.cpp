// TLE

// NOTE: TLE on n = 100000 (Test: #51)

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
template<ll M>
struct ModInt {
  using mint = ModInt;
  static constexpr ll modulo = M;
  ll v;
  ModInt() : v{0} {}
  template<class T> ModInt(T t) : v{static_cast<ll>(t)} {}
  friend ostream& operator<<(ostream& o, const mint& self) { return o << self.v; }

  mint& operator+=(mint o) { v = v + o.v; while (v >= M) { v -= M; }; return *this; }
  mint& operator-=(mint o) { return *this += (M - o.v); }
  mint& operator*=(mint o) { v = (v * o.v) % M; return *this; }
  mint& operator/=(mint o) { return *this *= o.inv(); }
  friend mint operator+(const mint& x, const mint& y) { return mint(x) += y; }
  friend mint operator-(const mint& x, const mint& y) { return mint(x) -= y; }
  friend mint operator*(const mint& x, const mint& y) { return mint(x) *= y; }
  friend mint operator/(const mint& x, const mint& y) { return mint(x) /= y; }
  friend bool operator==(const mint& x, const mint& y) { return x.v == y.v; }
  friend bool operator!=(const mint& x, const mint& y) { return x.v != y.v; }

  mint inv() const { return pow(M - 2); } // Assume prime
  mint pow(ll e) const {
    mint x = *this, res = 1;
    while (e > 0) {
      if (e & 1) { res *= x; }
      e >>= 1; x *= x;
    }
    return res;
  }

  static constexpr ll const_pow(ll x, ll e, ll m) {
    ll res = 1;
    while (e > 0) {
      if (e & 1) { res = (res * x) % m; }
      e >>= 1; x = (x * x) % m;
    }
    return res;
  }

  static constexpr ll const_findGenerator(ll m) {
    // Factorize "m - 1"
    ll x = m - 1;
    int ps[16] = {};
    int ps_size = 0;
    for (int p = 2; p * p <= x; p++) {
      if (x % p == 0) {
        ps[ps_size++] = p;
        while (x % p == 0) { x /= p; }
      }
    }
    if (x > 1) { ps[ps_size++] = x; }
    // Brute force generator
    for (ll y = 1; y <= m - 1; y++)  {
      bool ok = 1;
      for (int i = 0; i < ps_size; i++) {
        if (const_pow(y, (m - 1) / ps[i], m) == 1) { ok = 0; break; }
      }
      if (ok) { return y; }
    }
    return -1; // assert(0)
  }

  static inline constexpr ll generator_ll     = const_findGenerator(M);
  static inline constexpr ll generator_inv_ll = const_pow(generator_ll, M - 2, M);
  static inline const mint generator          = mint(generator_ll);
  static inline const mint generator_inv      = mint(generator_inv_ll);

  // Precomputation for FFT

  static inline mint roots[32][2] = {};
  static void findRoots() {
    if (roots[0][0] != 0) { return; }
    for (int b = 0; (M - 1) % (1 << b) == 0; b++) {
      roots[b][0] = generator.pow((M - 1) >> b);
      roots[b][1] = generator_inv.pow((M - 1) >> b);
    }
  }

  static inline mint pow2Invs[30] = {};
  static void findPow2Invs() {
    if (pow2Invs[0] != 0) { return; }
    for (int b = 0; b < 30; b++) {
      pow2Invs[b] = mint(1 << b).inv();
    }
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
  int n = f.size();
  int nb = 0;
  while ((1 << nb) < n) { nb++; }
  FOR(i, 0, n) {
    int j = reverse32(i) >> (32 - nb);
    if (i < j) { swap(f[i], f[j]); }
  }
  for (int lb = 1; lb <= nb; lb++) {
    int l = 1 << lb;
    mint::findRoots();
    mint u = mint::roots[lb][inv];
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
    mint::findPow2Invs();
    mint inv_n = mint::pow2Invs[nb];
    for (auto& x : f) { x *= inv_n; }
  }
}

template<class mint>
void polymul(vector<mint>& p, vector<mint>& q, vector<mint>& r) {
  fft(p, 0); fft(q, 0);
  FOR(i, 0, (int)p.size()) { r[i] = p[i] * q[i]; }
  fft(r, 1);
}

template<class mint>
void polymul(const vector<mint>& p, const vector<mint>& q, vector<mint>& r) {
  auto pp = p; auto qq = q; polymul(pp, qq, r);
}

using mint = ModInt<998244353>;

void polymulRebase(vector<ll>& p, vector<ll>& q, vector<ll>& r, int b) {
  int n = p.size();
  vector<mint> p0(n), p1(n), q0(n), q1(n), p0q0(n), p0q1(n), p1q0(n), p1q1(n);
  FOR(i, 0, n) {
    p1[i] = p[i] / b; p0[i] = p[i] % b;
    q1[i] = q[i] / b; q0[i] = q[i] % b;
  }
  polymul(vector<mint>(p0), vector<mint>(q0), p0q0);
  polymul(             p0,  vector<mint>(q1), p0q1);
  polymul(vector<mint>(p1),              q0 , p1q0);
  polymul(             p1 ,              q1 , p1q1);
  FOR(i, 0, n) {
    r[i] = p1q1[i].v * b * b + (p1q0[i].v + p0q1[i].v) * b + p0q0[i].v;
  }
}

int pow2Ceil(int n) {
  int b = 0;
  while ((1 << b) < n) { b++; }
  return 1 << b;
}

void polymulMod(vector<ll>& p, vector<ll>& q, vector<ll>& r, int n_lim, int modulo, int base) {
  // Align to power of two
  int n = pow2Ceil(min(n_lim, 2 * (int)max(p.size(), q.size())));
  p.resize(n); q.resize(n); r.resize(n);

  // Multiply
  polymulRebase(p, q, r, base);

  // Take modulo and remove leading zeros
  int m = 1;
  FOR(i, 0, n) {
    r[i] %= modulo;
    if (r[i] != 0) { m = i + 1; }
  }
  r.resize(m);
}

vector<ll> polymulModAll(vector<vector<ll>>& ps, int n_lim, int modulo, int base) {
  // Multiply together from small degrees
  auto compare = [](auto& x, auto& y) { return x.size() < y.size(); };
  multiset<vector<ll>, decltype(compare)> heap(compare);
  heap.insert(ALL(ps));
  while (heap.size() >= 2) {
    auto p = *heap.begin(); heap.erase(heap.begin());
    auto q = *heap.begin(); heap.erase(heap.begin());
    polymulMod(p, q, q, n_lim, modulo, base);
    heap.insert(q);
  }
  return *heap.begin();
}

// Main
void mainCase() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> ls(n);
  cin >> ls;

  vector<int> cnts(m);
  for (auto x : ls) { x--; cnts[x]++; }

  // Make 0/1 coefficient polynomials
  vector<vector<ll>> ps(m);
  FOR(i, 0, m) { ps[i].assign(cnts[i] + 1, 1); }
  dbg2(ps);

  const int modulo = 1009;
  const int base = 32; // base^2 > modulo
  auto q = polymulModAll(ps, n + 1, modulo, base);
  dbg(q);
  assert(k < (int)q.size());

  int res = q[k];
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/958F3/main_v3.cpp --check

%%%% begin
111 16 58
15 6 4 7 7 10 16 2 3 1 4 8 10 1 2 11 6 6 14 16 6 16 1 2 13 2 7 13 1 4 1 4 12 2 4 11 15 12 9 13 10 4 11 7 5 3 12 11 11 3 16 15 9 6 15 11 4 14 8 15 16 3 9 10 9 1 8 4 14 7 13 5 1 8 5 11 8 14 1 8 15 2 5 2 4 5 9 2 10 11 11 5 7 11 11 14 5 16 14 2 4 11 12 10 7 14 2 5 3 2 1
%%%%
552
%%%% end

%%%% begin
4 3 2
1 2 3 2
%%%%
4
%%%% end
*/
