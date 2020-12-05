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

const ll modulo = 998244353;
using mint = ModInt<modulo>;

// RNG for searching non quadratic residue
auto rng = mt19937(0x12345678);

// Zp sqrt (cf. library_checker/sqrt_mod/main.cpp)
struct ZpSqrt {
  ll p;
  ll z; // Non quadratic residue z^(p-1)/2 = -1
  ll q, k; // p = q 2^k + 1

  ZpSqrt(ll p) : p{p} {
    assert(p >= 3); // odd prime

    // p = q 2^k + 1
    q = p - 1;
    k = 0;
    while (q % 2 == 0) { q /= 2; k++; }
    assert(k >= 1);

    // Find non quadratic residue
    z = -1;
    FOR(_, 0, 64) {
      ll x = ll(rng()) % p;
      if (pow(x, (p - 1) / 2) == p - 1) {
        z = x;
        break;
      }
    }
    assert(z != -1);
  }

  ll pow(ll x, ll e) {
    ll y = 1;
    while (e > 0) {
      if (e & 1) { y = (y * x) % p; }
      e >>= 1;
      x = (x * x) % p;
    }
    return y;
  }

  // Find t s.t.
  //   x^(2^(t-1)) = -1
  //   x^(2^t)     = 1
  ll findPowerOfTwoOrder(ll x) {
    ll res = -1;
    FOR(t, 0, 64) {
      if (x == 1) { res = t; break; }
      x = (x * x) % p;
    }
    assert(res != -1);
    return res;
  };

  // x^2 = y
  ll solve(ll y) {
    if (y <= 1) { return y; }

    // Euler criterion
    if (pow(y, (p - 1) / 2) != 1) { return -1; }

    // y^(p - 1)/2 = y^(q 2^(k-1)) = 1
    // y^(q + 1) = b^2 = a y
    ll a = pow(y, q); // a^(2^(k-1)) = y^(p-1)/2 = 1
    ll b = pow(y, (q + 1) / 2);

    ll res = b; // Accumulate a^(-1/2) during loop
    while (true) {
      ll t = findPowerOfTwoOrder(a);
      if (t == 0) { break; }

      // z^(q 2^(k-t) 2^(t-1)) = z^(p-1)/2 = -1
      // (a z^(q 2^(k-t))^(2^(t-1)) = 1
      ll w = pow(z, q * (1 << (k - t - 1)));
      a = (a * w % p) * w % p;

      res = res * w % p;
    }
    return res;
  }
};

// Main
void mainCase() {
  int n; // [2, 5 x 10^5]
  cin >> n;
  ll p; // [3, 10^9 + 9], odd prime
  cin >> p;
  vector<int> parents(n - 1); // [1, n]
  cin >> parents;
  vector<ll> ls(n); // [0, p)
  cin >> ls;

  vector<vector<int>> adj(n);
  FOR(i, 0, n - 1) {
    int j = parents[i];
    adj[j - 1].push_back(i + 1);
  }

  ZpSqrt zp_sqrt(p);

  //
  // PROP.
  //   c = a^2 + 2 a (∑ bi) + 2 (∑_{i ≠ j} bi bj)
  //     = (a + (∑ bi))^2 - (∑ bi)^2 + 2 (∑_{i ≠ j} bi bj)
  //     = (a + (∑ bi))^2 - ∑ (bi)^2
  //
  // N.B.
  //   Thus, solvability of c = a^2 + ... doesn't depend on ±bi.
  //

  vector<mint> dp(n);
  vector<ll> dp1(n); // dp1(v) = sum({ ai   | i \in subtree(v) })
  vector<ll> res(n);

  function<void(int)> dfs = [&](int v) {
    ll c = ls[v];
    ll b = 0, b2 = 0;
    mint w = 1;
    for (auto u : adj[v]) {
      dfs(u);
      w *= dp[u];
      b = (b + dp1[u]) % p;
      b2 = (b2 + dp1[u] * dp1[u] % p) % p;
    }
    ll y = (c + b2) % p;
    ll x = 0;
    if (y == 0) {
      // Single solution x = 0
      w *= 1;
    } else {
      x = zp_sqrt.solve(y);
      if (x == -1) {
        // Zero solution
        w *= 0;
      } else {
        // Two solutions ±x
        w *= 2;
      }
    }
    res[v] = (x - b + p) % p;
    dp1[v] = (b + res[v]) % p;
    dp[v] = w;
  };
  dfs(0);
  dbg(dp);
  dbg(dp1);

  mint res2 = dp[0];
  cout << res2 << "\n";
  if (res2 == 0) { cout << -1 << "\n"; return; }
  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/DEC20/LCASQRT/main.cpp

%%%% begin
3
6 3
1 1 2 3 2
1 2 0 1 1 1
5 3
1 1 1 3
2 1 0 2 1
9 101
1 1 2 3 2 4 3 5
18 77 44 82 4 20 19 43 97
%%%%
32
2 2 0 1 2 2
0
-1
64
3 70 5 76 20 11 25 12 81
%%%% end
*/
