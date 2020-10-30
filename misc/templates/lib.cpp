
// Disjoint set union
struct Dsu {
  vector<int> ps;
  Dsu(int n) { ps.resize(n); iota(ALL(ps)); }
  int find(int a) {
    if (a == ps[a]) { return a; }
    return ps[a] = find(ps[a]);
  }
  void merge(int dst, int src) {
    ps[find(src)] = find(dst);
  }
};

// Fenwick tree for sum
struct FenwickTree {
  int n_;
  vector<int> data_;
  FenwickTree(int n) { n_ = n; data_.resize(n); }
  void incr(int i, int v) {
    while (i < n_) {
      data_[i] += v;
      i = (i | (i + 1));
    }
  }
  int reduce(int r) { // [0, r)
    int i = r - 1;
    int res = 0;
    while (i >= 0) {
      res += data_[i];
      i = (i & (i + 1)) - 1;
    }
    return res;
  }
};

// Z function
vector<int> makeZ(const string& s) {
  int n = s.size();
  vector<int> z(n);
  int l = 1, r = 1; // [l, r)
  FOR(i, 1, n) {
    if (i < r) { z[i] = min(z[i - l], r - i); }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) { z[i]++; }
    if (i + z[i] > r) { l = i; r = i + z[i]; }
  }
  return z;
}

// 64bit hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
ull hash64(ull x) {
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9ULL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebULL;
  x ^= x >> 31;
  return x;
};

// 32Bit reversal
uint32_t reverse32(uint32_t x) {
  x = ((x & 0x55555555U) <<  1) | ((x & 0xaaaaaaaaU) >>  1); // 0101 = 0x5, 1010 = 0xa
  x = ((x & 0x33333333U) <<  2) | ((x & 0xccccccccU) >>  2); // 0011 = 0x3, 1100 = 0xc
  x = ((x & 0x0f0f0f0fU) <<  4) | ((x & 0xf0f0f0f0U) >>  4);
  x = ((x & 0x00ff00ffU) <<  8) | ((x & 0xff00ff00U) >>  8);
  x = ((x & 0x0000ffffU) << 16) | ((x & 0xffff0000U) >> 16);
  return x;
}

// DFT / IDFT
template<class T>
void fft(vector<T>& f, bool inv) {
  // Precompute roots and their powers
  static bool first_run = true;
  constexpr int nb_max = 20;
  static array<vector<vector<T>>, 2> roots; // roots[inv][b][k] = (2^b root)^k
  if (first_run) {
    first_run = false;
    using U = typename T::value_type;
    const U pi = acos(-1);
    roots[0].resize(nb_max + 1);
    roots[1].resize(nb_max + 1);
    for (int b = 1; b < nb_max; b++) {
      int l = 1 << b;
      roots[0][b].resize(l / 2);
      roots[1][b].resize(l / 2);
      for (int k = 0; k < l / 2; k++) {
        U t = 2.0 * pi * (U)k / (U)l;
        roots[0][b][k] = {cos(t), - sin(t)};
        roots[1][b][k] = {cos(t), + sin(t)};
      }
    }
  }

  int n = f.size();
  assert(n <= (1 << nb_max));

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
    for (auto& x : f) { x /= n; }
  }
}

// High dimentional vector
template<class T, size_t Rank>
struct Tensor {
  using idx_t = array<int, Rank>;
  idx_t shape_;
  vector<T> data_;
  Tensor(const idx_t& shape, T init_value) : shape_{shape} {
    data_.assign(flatIndex(shape_), init_value);
  }
  int flatIndex(const idx_t& idx) {
    int res = idx[0];
    for (int i = 1; i < (int)Rank; i++) { res += res * shape_[i] + idx[i]; }
    return res;
  }
  template<class ...Is>
  T& operator()(Is... i) {
    static_assert(Rank == sizeof...(i));
    return data_[flatIndex(idx_t{i...})];
  }
};

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

using mint = ModInt<(ll)1e9 + 7>;
using mint = ModInt<998244353>; // = 1 + 2^23 x 7 x 17

// Number theoretic transform
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

// Order statistics tree (cf. https://codeforces.com/blog/entry/11080 by adamant)
#include <ext/pb_ds/assoc_container.hpp>
template<class Key, class Compare = less<Key>>
using ordered_set = __gnu_pbds::tree<
  Key, __gnu_pbds::null_type, Compare,
  __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;


// Segment tree for sum
struct SegmentTree {
  int n = 1;
  using Node = int;
  static inline Node kZero = 0;
  vector<Node> data;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, kZero);
  }

  ostream& print(ostream& ostr) const {
    for (int k = 1; k <= n; k *= 2) {
      for (int i = 0; i < k; i++) {
        ostr << data[i + k] << " \n"[i == k - 1];
      }
    }
    return ostr;
  }

  Node join(const Node& lhs, const Node& rhs) {
    return lhs + rhs;
  }

  void set(int qi, const Node& qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  // Iterative (cf. Al.Cash https://codeforces.com/blog/entry/18051)
  Node reduce(int ql, int qr) {
    Node res = kZero;
    int jl = ql + n, jr = qr + n;
    for (; jl < jr; jl /= 2, jr /= 2) {
      if (jl % 2) { res = join(res, data[jl++]); }
      if (jr % 2) { res = join(res, data[--jr]); }
    }
    return res;
  }

  // Recursive
  Node reduce(int ql, int qr) {
    function<Node(int, int, int)> rec = [&](int l, int r, int j) -> Node {
      if (qr <= l || r <= ql) { return kZero; }
      if (ql <= l && r <= qr) { return data[j]; }
      return rec(l, (l + r) / 2, 2 * j) + rec((l + r) / 2, r, 2 * j + 1);
    };
    return rec(0, n, 1);
  }
};


// Printing 128 bit integer
namespace std {
  ostream& operator<<(ostream& ostr, __int128 x) {
    if (x == 0) { return ostr << 0; }
    bool neg = x < 0;
    if (neg) { x = -x; }
    string res;
    while (x > 0) {
      res += (x % 10) + '0';
      x /= 10;
    }
    reverse(ALL(res));
    return ostr << (neg ? "-" : "") << res;
  }
}
