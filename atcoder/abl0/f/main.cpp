// AFTER EDITORIAL, AC

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
  friend ostream& operator<<(ostream& ostr, const mint& self) { return ostr << self.v; }

  mint& operator+=(const mint& y) { v += y.v; while (v >= modulo) { v -= modulo; }; return *this; }
  mint& operator-=(const mint& y) { return *this += (modulo - y.v); }
  mint& operator*=(const mint& y) { v = ((v * y.v) % modulo); return *this; }
  mint& operator/=(const mint& y) { return *this *= y.inv(); }
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

  // Factorial, binomial, inverse
  static inline vector<mint> _facts, _inv_facts;
  static void makeFactorials(int n) {
    _facts.resize(n + 1);
    _inv_facts.resize(n + 1);
    _facts[0] = 1;
    _inv_facts[0] = 1;
    for (int i = 1; i <= n; i++) {
      _facts[i] = _facts[i - 1] * mint(i);
    }
    _inv_facts[n] = _facts[n].inv();
    for (int i = n; i >= 1; i--) {
      _inv_facts[i - 1] = _inv_facts[i] * i;
    }
  }
  static mint fact(int n, bool inv = 0) {
    assert(!_facts.empty());
    return inv ? _inv_facts[n] : _facts[n];
  }
  static mint binom(int n, int k) {
    return fact(n) * fact(n - k, 1) * fact(k, 1);
  }
  static mint inverse(int n) {
    return fact(n - 1) * fact(n, 1);
  }

  // Generator and primitive roots
  static inline mint _generator, _inv_generator;
  static mint generator(bool inv = 0) {
    assert(_generator != 0);
    return inv ? _inv_generator : _generator;
  }
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
        _generator = mint(y);
        _inv_generator = mint(y).inv();
        return;
      }
    }
    assert(0);
  }

  static inline vector<mint> _roots, _inv_roots;
  static mint root(int b, bool inv) {
    assert(!_roots.empty());
    return (inv ? _inv_roots : _roots)[b];
  }
  static void findRoots() {
    _roots.resize(32);
    _inv_roots.resize(32);
    for (int b = 0; (modulo - 1) % (1 << b) == 0; b++) {
      _roots[b]     = generator(0).pow((modulo - 1) >> b);
      _inv_roots[b] = generator(1).pow((modulo - 1) >> b);
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
    mint u = mint::root(lb, inv);
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
    mint inv_n = mint::inverse(n);
    for (auto& x : f) { x *= inv_n; }
  }
}

constexpr ll modulo = 998244353;
using mint = ModInt<modulo>;

void polymulPow2(vector<mint>& p, vector<mint>& q, vector<mint>& r) {
  fft(p, 0); fft(q, 0);
  FOR(i, 0, (int)p.size()) { r[i] = p[i] * q[i]; }
  fft(r, 1);
}

int pow2Ceil(int n) {
  int b = 0;
  while ((1 << b) < n) { b++; }
  return 1 << b;
}

void polymul(vector<mint>& p, vector<mint>& q, vector<mint>& r) {
  int n = 2 * pow2Ceil(max(p.size(), q.size()));
  p.resize(n); q.resize(n), r.resize(n);
  polymulPow2(p, q, r);
  while (r.size() >= 2 && r.back() == 0) { r.pop_back(); }
}

vector<mint> polymulAll(const vector<vector<mint>>& ps) {
  // Multiply together from small degrees
  auto compare = [](auto& x, auto& y) { return x.size() < y.size(); };
  multiset<vector<mint>, decltype(compare)> heap(compare);
  heap.insert(ALL(ps));
  while (heap.size() >= 2) {
    auto p = *heap.begin(); heap.erase(heap.begin());
    auto q = *heap.begin(); heap.erase(heap.begin());
    polymul(p, q, q);
    heap.insert(q);
  }
  return *heap.begin();
}

// Main
void mainCase() {
  int n; // [1, 5 x 10^4]
  cin >> n;
  vector<int> ls(2 * n); // [1, 10^5]
  cin >> ls;

  map<int, int> cnts;
  for (auto x : ls) { cnts[x]++; }

  //
  // PROP.
  //   Define
  //     f(k) = #{ways making "k" pairs out of "2k"} = (2k)! / k! 2^k
  //     g(k) = #{ways making "k" bad pairs out of "2n"}
  //   Then,
  //     h(k) = #{ways making "n" pairs out of "2n" and at least "k" pairs are bad}
  //          = f(n-k) g(k)
  //   Thus, by inclusion-exclusion principle,
  //     Answer = ∑_k (-1)^k f(n-k) g(k)
  //

  //
  // PROP.
  //   Define
  //     p(x | c) = 1 + x f(2) binom(c, 2) + x^2 f(4) binom(c, 4) + ...
  //   Then,
  //     ∏_j p(x | cnts[j]) = g(0) + x g(1) + x^2 g(2) + ....
  //

  // Zp precompuation
  mint::makeFactorials(2 * n);
  mint::findGenerator();
  mint::findRoots();

  // Define f
  const mint inv_2 = mint(2).inv();
  auto f = [&](int k) { return mint::fact(2 * k) * mint::fact(k, 1) * inv_2.pow(k); };

  // Define p(x | cnts[j])
  vector<vector<mint>> ps;
  for (auto [_k, c] : cnts) {
    auto& p = ps.emplace_back();
    p.resize(c / 2 + 1);
    for (int i = 0; i <= c; i += 2) {
      p[i / 2] = f(i / 2) * mint::binom(c, i);
    }
  }
  dbg(cnts);
  dbg2(ps);

  // Compute ∏_j p(x | cnts[j])
  auto g = polymulAll(ps);
  g.resize(n + 1);
  dbgv(g);

  // Compute answer
  mint res = 0;
  FOR(i, 0, n + 1) {
    dbgv(n, i, f(n - i), g[i]);
    if (i % 2 == 0) { res += f(n - i) * g[i]; }
    if (i % 2 == 1) { res -= f(n - i) * g[i]; }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abl0/f/main.cpp --check

%%%% begin
2
1
1
2
3
%%%%
2
%%%% end

%%%% begin
5
30
10
20
40
20
10
10
30
50
60
%%%%
516
%%%% end
*/
