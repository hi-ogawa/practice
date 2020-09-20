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

  static inline mint generator = 0;
  static void findGenerator() {
    if (generator != 0) { return; }
    auto factorize = [](ll x) -> vector<array<ll, 2>> {
      vector<array<ll, 2>> res;
      for (ll p = 2; p <= sqrt(x); p++) {
        if (x % p == 0) {
          ll e = 0;
          while (x % p == 0) { e++; x /= p; }
          res.push_back({p, e});
        }
      }
      if (x > 1) { res.push_back({x, 1}); }
      return res;
    };
    vector<ll> ls;
    for (auto [p, _e] : factorize(M - 1)) { // Assume prime
      ls.push_back((M - 1) / p);
    }
    for (ll x = 1; x < M; x++) {
      bool ok = 1;
      for (auto y : ls) { if (mint(x).pow(y) == 1) { ok = 0; break; } }
      if (ok) { generator = x; break; }
    }
  }
};

using mint = ModInt<998244353>; // 998244352 = 2^23 x 7 x 17

// FFT
uint32_t reverse32(uint32_t x) {
  x = ((x & 0x55555555U) <<  1) | ((x & 0xaaaaaaaaU) >>  1); // 0101 = 0x5, 1010 = 0xa
  x = ((x & 0x33333333U) <<  2) | ((x & 0xccccccccU) >>  2); // 0011 = 0x3, 1100 = 0xc
  x = ((x & 0x0f0f0f0fU) <<  4) | ((x & 0xf0f0f0f0U) >>  4);
  x = ((x & 0x00ff00ffU) <<  8) | ((x & 0xff00ff00U) >>  8);
  x = ((x & 0x0000ffffU) << 16) | ((x & 0xffff0000U) >> 16);
  return x;
}

void fft(vector<mint>& f, bool inv) {
  int n = f.size();
  int m = 0;
  while ((1 << m) < n) { m++; }
  FOR(i, 0, n) {
    int j = reverse32(i) >> (32 - m);
    if (i < j) { swap(f[i], f[j]); }
  }
  for (int l = 2; l <= n; l *= 2) {
    mint u = mint::generator.pow((mint::modulo - 1) / l); // precompute?
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
    mint inv_n = mint(n).inv(); // precompute?
    for (auto& x : f) { x *= inv_n; }
  }
}

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

void polymulMod(vector<mint>& p, vector<mint>& q, vector<mint>& r, ll modulo) {
  // Align to power of two
  int np = p.size(), nq = q.size();
  int n = pow2Ceil(2 * max(np, nq));
  p.resize(n); q.resize(n); r.resize(n);
  polymul(p, q, r);

  // Take modulo and remove leading zero
  int m = 1;
  FOR(i, 0, n) {
    r[i].v %= modulo;
    if (r[i] != 0) { m = i + 1; }
  }
  r.resize(m);
}

vector<mint> polymulModAll(vector<vector<mint>>& ps, ll modulo) {
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

  // Precompute generator
  mint::findGenerator();

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
