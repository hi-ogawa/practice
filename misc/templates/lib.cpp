// TODO:
// - DSU
// - Segment tree
// - Suffix array
// - ...

// Disjoint set union
struct Dsu {
  vector<int> data_;
  Dsu(int n) { data_.resize(n); iota(ALL(data_)); }
  void merge(int dst, int src) { data_[find(src)] = find(dst); }
  int find(int a) {
    if (a == data_[a]) { return a; }
    return data_[a] = find(data_[a]);
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
using cd = complex<double>;

void fft(vector<cd>& f, bool inv) {
  int n = f.size();
  int m = 0;
  while ((1 << m) < n) { m++; }
  FOR(i, 0, n) {
    int j = reverse32(i) >> (32 - m);
    if (i < j) { swap(f[i], f[j]); }
  }
  for (int l = 2; l <= n; l *= 2) {
    cd u = exp((inv ? 2i : -2i) * M_PI / (cd)l);
    for (int i = 0; i < n; i += l) {
      cd z = 1.0;
      for (int k = 0; k < l / 2; k++) {
        cd& x = f[i + k];
        cd& y = f[i + k + l / 2];
        tie(x, y) = make_tuple(x + z * y, x - z * y);
        z *= u;
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
};

using mint = ModInt<(ll)1e9 + 7>;
using mint = ModInt<998244353>; // = 1 + 2^23 x 7 x 17
