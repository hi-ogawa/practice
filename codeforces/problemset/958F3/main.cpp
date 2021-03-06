// WA, WIP

// NOTE: WA on n = 20000 (Test: #46)
// NOTE: similar to cses/additional_problems/task1706/main_v5.cpp

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
    assert(0);
  }

  static inline const mint generator = mint(const_findGenerator(M));
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
  int m = 0;
  while ((1 << m) < n) { m++; }
  FOR(i, 0, n) {
    int j = reverse32(i) >> (32 - m);
    if (i < j) { swap(f[i], f[j]); }
  }
  for (int l = 2; l <= n; l *= 2) {
    mint u = mint::generator.pow((mint::modulo - 1) / l);
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

constexpr tuple<ll, ll, ll> solveBezout(ll p, ll q) { // xp + yq = gcd(p, q)
  bool _swap = 0;
  if (p < q) { swap(p, q); _swap = 0; }
  ll x1 = 1, x2 = 0;
  ll y1 = 0, y2 = 1;
  ll z1 = p, z2 = q;
  while (z2 != 0) {
    ll s = z1 / z2, r = z1 % z2;
    tie(x1, x2) = make_tuple(x2, x1 - s * x2);
    tie(y1, y2) = make_tuple(y2, y1 - s * y2);
    tie(z1, z2) = make_tuple(z2, r);
  }
  if (_swap) { swap(x1, y1); }
  return {x1, y1, z1};
}

void polymulCRT(vector<ll>& p, vector<ll>& q, vector<ll>& r, int modulo) {
  const ll m1 = 998244353; // = 1 + 2^23 x 7 x 17
  const ll m2 = 754974721; // = 1 + 2^24 x 3^2 x 5
  ll n1, n2, _g;
  tie(n1, n2, _g) = solveBezout(m1, m2);

  auto add = [&](ll x, ll y) -> ll { return (x + y) % modulo; };
  auto mul = [&](ll x, ll y) -> ll { return (x * y) % modulo; };
  auto solveCRT = [&](ll x1, ll x2) -> ll {
    // n1 m1 + n2 m2 = 1
    // =>
    // x = x1 = x1 n2 m2 (mod m1)
    // x = x2 = x2 n1 m1 (mod m2)
    // x = x1 n2 m2 + x2 n1 m1 (mod m1 m2)
    return add(mul(x1, mul(n2, m2)), mul(x2, mul(n1, m1)));
  };

  int n = p.size();
  vector<ModInt<m1>> p1(n), q1(n), r1(n);
  vector<ModInt<m2>> p2(n), q2(n), r2(n);
  FOR(i, 0, n) {
    p1[i] = p[i]; q1[i] = q[i];
    p2[i] = p[i]; q2[i] = q[i];
  }
  polymul(p1, q1, r1);
  polymul(p2, q2, r2);
  FOR(i, 0, n) {
    r[i] = solveCRT(r1[i].v, r2[i].v);
  }
}

using mint = ModInt<998244353>; // = 1 + 2^23 x 7 x 17

int pow2Ceil(int n) {
  int b = 0;
  while ((1 << b) < n) { b++; }
  return 1 << b;
}

// NOTE: this overflows since we expect "n * modulo * modulo ~ 10^5.10^3.10^3 > 998244353"
void polymulMod(vector<mint>& p, vector<mint>& q, vector<mint>& r, int modulo) {
  // Align to power of two
  int n = 2 * pow2Ceil(max(p.size(), q.size()));
  p.resize(n); q.resize(n); r.resize(n);

  // Multiply
  polymul(p, q, r);

  // Take modulo and remove leading zero
  int m = 1;
  FOR(i, 0, n) {
    r[i].v %= modulo;
    if (r[i] != 0) { m = i + 1; }
  }
  r.resize(m);
}

vector<mint> polymulModAll(vector<vector<mint>>& ps, int modulo) {
  // Multiply together from small degrees
  auto compare = [](auto& x, auto& y) { return x.size() < y.size(); };
  multiset<vector<mint>, decltype(compare)> heap(compare);
  heap.insert(ALL(ps));
  while (heap.size() >= 2) {
    auto p = *heap.begin(); heap.erase(heap.begin());
    auto q = *heap.begin(); heap.erase(heap.begin());
    polymulMod(p, q, q, modulo);
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
  vector<vector<mint>> ps(m);
  FOR(i, 0, m) { ps[i].assign(cnts[i] + 1, 1); }
  dbg2(ps);

  const int modulo = 1009;
  auto q = polymulModAll(ps, modulo);
  dbg(q);
  assert(k < (int)q.size());

  int res = q[k].v;
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/958F3/main.cpp --check

%%%% begin
4 3 2
1 2 3 2
%%%%
4
%%%% end
*/
