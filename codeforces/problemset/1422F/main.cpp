// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
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

const ll modulo = 1e9 + 7;
using mint = ModInt<modulo>;

// Segment tree for maximum
struct SegmentTree1 {
  using T = int;
  static inline T zero = 0;
  static T join(T lhs, T rhs) { return max(lhs, rhs); }

  int n = 1;
  vector<T> data;

  SegmentTree1(int n_orig) {
    while (n < n_orig) { n *= 2; }
    data.assign(2 * n, zero);
  }

  void incr(int qi, T qv) {
    int j = qi + n;
    data[j] = join(data[j], qv);
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  T reduce(int ql, int qr) {
    T res = zero;
    int jl = ql + n, jr = qr + n;
    for (; jl < jr; jl /= 2, jr /= 2) {
      if (jl % 2) { res = join(res, data[jl++]); }
      if (jr % 2) { res = join(res, data[--jr]); }
    }
    return res;
  }
};

// Persistent segment tree for increment by multiplication
struct SegmentTree2 {
  using T = mint;
  static inline T zero = 1;
  static T join(T lhs, T rhs) { return lhs * rhs; }

  struct Node {
    int l, r;
    T data = zero;
    array<shared_ptr<Node>, 2> cs;

    void ensureChildren(int qi) {
      int m = (l + r) / 2;
      int side = m <= qi;
      auto& c = cs[side];
      if (c.use_count() == 0) { // Create node
        c = make_shared<Node>();
        c->l = side ? m : l;
        c->r = side ? r : m;
        return;
      }
      if (c.use_count() >= 2) { // Copy node
        c = make_shared<Node>(*c);
        return;
      }
    }

    void incr(int qi, T qv) {
      if (qi < l || r <= qi) { return; }
      if (l + 1 == r) { data = join(data, qv); return; }
      ensureChildren(qi);
      T res = zero;
      FOR(i, 0, 2) {
        if (cs[i]) {
          cs[i]->incr(qi, qv);
          res = join(res, cs[i]->data);
        }
      }
      data = res;
    }

    T reduce(int ql, int qr) {
      if (qr <= l || r <= ql) { return zero; }
      if (ql <= l && r <= qr) { return data; }
      T res = zero;
      FOR(i, 0, 2) {
        if (cs[i]) {
          res = join(res, cs[i]->reduce(ql, qr));
        }
      }
      return res;
    }
  };

  Node root;
  int n = 1;
  SegmentTree2(int n_orig) {
    while (n < n_orig) { n *= 2; }
    root.l = 0;
    root.r = n;
  }
  void incr(int qi, T qv) {
    root.incr(qi, qv);
  }
  T reduce(int ql, int qr) {
    return root.reduce(ql, qr);
  }
};

// Euler product sieve
tuple<vector<int>, vector<int>> makeEulerSieve(int n) {
  vector<int> ps, lp(n + 1);
  lp.resize(n + 1);
  for (int x = 2; x <= n; x++) {
    if (lp[x] == 0) { lp[x] = x; ps.push_back(x); }
    for (auto p : ps) {
      if (x * p > n || p > lp[x]) { break; }
      lp[x * p] = p;
    }
  }
  return {move(ps), move(lp)};
}

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 2 x 10^5]
  cin >> ls;
  int nq; // [1, 10^5]
  cin >> nq;
  vector<array<int, 2>> qs(nq); // [1, n]
  cin >> qs;

  // Prime factorization
  int m = *max_element(ALL(ls));
  vector<int> ps, lp;
  tie(ps, lp) = makeEulerSieve(m);
  int k = ps.size();
  vector<int> inv_ps(m + 1, -1);
  FOR(i, 0, k) { inv_ps[ps[i]] = i; }

  // Separate smalls/larges
  auto ps_sep = upper_bound(ALL(ps), sqrt(m));
  vector<int> ps1(ps.begin(), ps_sep);
  vector<int> ps2(ps_sep, ps.end());
  int k1 = ps1.size();
  int k2 = ps2.size();

  auto factorize = [&](int x) -> vector<array<int, 2>> {
    vector<array<int, 2>> res;
    while (x > 1) {
      int p = lp[x], e = 0;
      while (x % p == 0) { e++; x /= p; }
      res.push_back({p, e});
    }
    return res;
  };

  // Segment tree to find max exponent for each small prime
  vector<SegmentTree1> trees1(k1, SegmentTree1(n));

  // Segment tree to directly find lcm of large primes
  vector<SegmentTree2> trees2(1, SegmentTree2(n));

  vector<vector<int>> st(k2); // position for large prime
  FOR(i, 0, k2) { st[i].push_back(-1); }

  FOR(i, 0, n) {
    auto& tree = trees2.emplace_back(trees2.back());
    auto fs = factorize(ls[i]);
    for (auto [p, e] : fs) {
      int j = inv_ps[p];
      if (j < k1) {
        // Small prime
        trees1[j].incr(i, e);

      } else {
        // Large prime
        int i0 = st[j - k1].back();
        tree.incr(i0 + 1, mint(p));      // Update as difference array
        tree.incr(i + 1, mint(p).inv());
        st[j - k1].push_back(i);
      }
    }
  }

  auto solve = [&](int l, int r) -> mint {
    mint res = 1;
    // Accumulate small primes
    FOR(i, 0, k1) {
      int p = ps[i];
      int e = trees1[i].reduce(l, r);
      res *= mint(p).pow(e);
    }

    // Accumulate large primes
    res *= trees2[r].reduce(0, l + 1);

    return res;
  };

  mint res = 0;
  for (auto [l, r] : qs) {
    l = (l + res.v) % n + 1;
    r = (r + res.v) % n + 1;
    if (l > r) { swap(l, r); }
    l--;
    res = solve(l, r);
    dbg(l, r, res);
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1422F/main.cpp

%%%% begin
3
2 3 5
4
1 3
3 3
2 3
2 3
%%%%
6
2
15
30
%%%% end
*/
