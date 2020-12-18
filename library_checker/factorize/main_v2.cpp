// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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

template<class Rng>
struct MillerRabin {
  using lll = __int128;
  Rng& rng;
  int num_trials = 32;
  MillerRabin(Rng& rng) : rng{rng} {}

  ll pow(ll x, ll e, ll m) {
    ll y = 1 % m;
    while (e > 0) {
      if (e & 1) { y = (lll)x * y % m; }
      e >>= 1;
      x = (lll)x * x % m;
    }
    return y;
  }

  bool test(ll x, ll k, ll q, ll n) {
    ll y = pow(x, q, n);
    if (y == 1) { return 0; }
    FOR(_, 0, k) {
      if (y == n - 1) { return 0; }
      y = (lll)y * y % n;
    }
    return 1;
  }

  bool isComposite(ll n) {
    assert(n >= 1);
    if (n == 1) { return 1; }
    if (n == 2) { return 0; }
    if (n % 2 == 0) { return 1; }

    // n = 2^k q + 1
    ll q = n - 1;
    ll k = 0;
    while (q % 2 == 0) { q /= 2; k++; }

    FOR(_, 0, num_trials) {
      ll x = (rng() % (n - 1)) + 1;
      if (gcd(x, n) > 1) { return 1; }
      if (test(x, k, q, n)) { return 1; }
    }
    return 0;
  }

  bool isPrime(ll n) { return !isComposite(n); }
};

template<class Rng>
struct TonelliShanks {
  using lll = __int128;
  Rng& rng;
  TonelliShanks(Rng& rng) : rng{rng} {}

  ll pow(ll x, ll e, ll m) {
    ll y = 1 % m;
    while (e > 0) {
      if (e & 1) { y = ((lll)x * y) % m; }
      e >>= 1; x = ((lll)x * x) % m;
    }
    return y;
  }

  ll findPowerOfTwoOrder(ll x, ll k, ll p) {
    ll res = -1;
    FOR(i, 0, k + 1) {
      if (x == 1) { res = i; break; }
      x = ((lll)x * x) % p;
    }
    assert(res != -1);
    return res;
  }

  // x^2 = y ∈ Z(p)
  ll solve(ll y, ll p) {
    if (p == 2) { return y; }

    // p = q 2^k + 1
    ll q = p - 1;
    ll k = 0;
    while (q % 2 == 0) { q /= 2; k++; }
    assert(k >= 1);

    // Euler criterion
    if (pow(y, (p - 1) / 2, p) != 1) { return -1; }

    // Find non quadratic residue
    ll z = -1;
    while (z == -1) {
      ll x = rng() % (p - 1) + 1;
      if (pow(x, (p - 1) / 2, p) == p - 1) { z = x; }
    }

    // Tonelli-Shanks algorithm

    // y^(q + 1) = b^2 = a y
    ll a = pow(y, q, p);
    ll b = pow(y, (q + 1) / 2, p);

    ll res = b; // Accumulate a^(-1/2)
    while (true) {
      ll t = findPowerOfTwoOrder(a, k, p);
      if (t == 0) { break; }
      ll w = pow(z, q * (1 << (k - t - 1)), p);
      a = ((lll)a * w % p) * w % p;
      res = (lll)res * w % p;
    }
    return res;
  }
};

// Cf. https://en.wikipedia.org/wiki/Quadratic_sieve
template<class Rng>
struct QuadraticSieve {
  using lll = __int128;
  vector<int> ps;
  ll lim_p = 1e6; // TODO: how does this choice affect discovoring factors??
  int wb_bias = 16; // TODO: such a heuristics...
  Rng& rng;
  TonelliShanks<Rng> tonelli_shanks;

  QuadraticSieve(Rng& rng) : rng{rng}, tonelli_shanks{rng} {
    ps = getPrimes(lim_p);
  }

  ll mod(ll x, ll y) { x %= y; return x >= 0 ? x : (x + y); }

  ll pow(ll x, ll e, ll m) {
    ll y = 1 % m;
    while (e > 0) {
      if (e & 1) { y = (lll)x * y % m; }
      e >>= 1; x = (lll)x * x % m;
    }
    return y;
  }

  vector<int> getPrimes(int n) {
    vector<bool> s(n + 1, 1);
    for (int p = 2; p <= sqrt(n) + 1; p++) {
      if (!s[p]) { continue; }
      for (int x = p * p; x <= n; x += p) { s[x] = 0; }
    }
    vector<int> res;
    for (int p = 2; p <= n; p++) {
      if (s[p]) { res.push_back(p); }
    }
    return res;
  }

  // Find non trivial kernel by Gaussian elimination
  bool getKernel(vector<vector<int>>& a, vector<int>& res) {
    int n = a.size(), m = a[0].size();
    int kernel_row = (n > m) ? m : -1;

    vector<vector<int>> b(n, vector<int>(n));
    FOR(i, 0, n) { b[i][i] = 1; }

    FOR(k, 0, min(n, m)) {
      if (a[k][k] == 0) {
        // Pivot row
        int ip = -1;
        FOR(i, k + 1, n) {
          if (a[i][k] == 1) { ip = i; break; }
        }
        if (ip != -1) {
          // Found pivot
          FOR(j, k, m) { swap(a[k][j], a[ip][j]); }
          FOR(j, 0, n) { swap(b[k][j], b[ip][j]); }
        } else {
          // Otherwise, pivot column
          int jp = -1;
          FOR(j, k + 1, m) {
            if (a[k][j] == 1) { jp = j; break; }
          }
          if (jp != -1) {
            // Found pivot
            FOR(i, k, n) { swap(a[i][k], a[i][jp]); }
          } else {
            // Otherwise we're done
            kernel_row = k;
            break;
          }
        }
      }
      assert(a[k][k] == 1);

      // Eliminate row
      FOR(i, k + 1, n) {
        if (a[i][k] == 0) { continue; }
        FOR(j, k, m) { a[i][j] ^= a[k][j]; }
        FOR(j, 0, n) { b[i][j] ^= b[k][j]; }
      }
    }
    // dbg2(a);
    // dbg2(b);
    // dbg(kernel_row);
    if (kernel_row == -1) { return 0; }
    res = b[kernel_row];
    return 1;
  }

  ll solve(ll n) {
    ll sqrt_n = sqrt(n) + 1;
    int num_x = min(lim_p, sqrt_n);
    dbg(n, sqrt_n, num_x);

    // y(x) = (x + sqrt_n)^2 - n
    vector<ll> ys(num_x), zs(num_x);
    FOR(x, 0, num_x) {
      ys[x] = zs[x] = (x + sqrt_n) * (x + sqrt_n) - n;
    }

    // Bases = { p | n ∈ QR(p) }
    vector<ll> ws, bs;
    for (auto p : ps) {
      if (p >= num_x) { break; }
      if (ws.size() >= wb_bias + bs.size()) { break; }
      ll q = tonelli_shanks.solve(n, p); // q^2 = n ∈ Z(p)
      if (q == -1) { continue; }
      bs.push_back(p);
      array<ll, 2> qs = {q, -q};
      FOR(i, 0, 2) {
        if (p == 2 && i == 1) { continue; } // unique sqrt for prime 2
        for (int x = mod(qs[i] - sqrt_n, p); x < num_x; x += p) {
          assert(zs[x] % p == 0);
          zs[x] /= p;
          if (zs[x] == 1) { ws.push_back(x); }
        }
      }
    }
    sort(ALL(ws));
    int num_w = ws.size(), num_b = bs.size();
    dbg(num_w, num_b);

    // Exponent table
    vector<vector<int>> table(num_w, vector<int>(num_b));
    vector<int> kernel(num_w);

    auto doTrial = [&]() -> ll {
      FOR(i, 0, num_w) {
        FOR(j, 0, num_b) {
          table[i][j] = (ys[ws[i]] % bs[j] == 0);
        }
      }
      // dbg(ws);
      // dbg(bs);
      // dbg2(table);

      auto tmp_table = table;
      bool ok_kernel = getKernel(tmp_table, kernel);
      assert(ok_kernel);
      ll a = 1, b = 1;
      FOR(i, 0, num_w) {
        if (kernel[i] == 0) { continue; }
        a = (lll)a * (ws[i] + sqrt_n) % n;
      }
      FOR(j, 0, num_b) {
        ll e = 0;
        FOR(i, 0, num_w) { e += (kernel[i] && table[i][j]); }
        assert(e % 2 == 0);
        b = (lll)b * pow(bs[j], e / 2, n) % n;
      }
      dbg(a, b, a + b, a - b, gcd(a + b, n), gcd(a - b, n));
      ll g1 = gcd(a + b, n);
      ll g2 = gcd(a - b, n);
      if (g1 != 1 && g1 != n) { return g1; }
      if (g2 != 1 && g2 != n) { return g2; }
      return -1;
    };

    // Try multiple times by shuffling
    const int num_trials = 16;
    FOR(_, 0, num_trials) {
      ll res = doTrial();
      if (res != -1) { return res; }
      shuffle(ALL(ws), rng);
      shuffle(ALL(bs), rng);
    }
    return -1;
  }
};

template<class T>
T getKthRoot(int k, T y) {
  assert(k >= 1 && y >= 0);
  if (k == 1 || y <= 1) { return y; }

  const T kInf = numeric_limits<T>::max();

  // x^k ≤ y
  auto evaluate = [&](T x) -> bool {
    int e = k;
    T res = 1;
    bool overflow_x = 0;
    while (e > 0) {
      if (e & 1) {
        if (overflow_x || res > kInf / x) { return 0; }
        res *= x;
      }
      e >>= 1;
      if (overflow_x || (overflow_x = x > kInf / x)) { continue; }
      x *= x;
    }
    return res <= y;
  };

  // max { x | x^k ≤ y }
  T x0 = 1, x1 = y; // [x0, x1)
  while (x0 + 1 < x1) {
    T x = x0 + (x1 - x0) / 2;
    if (evaluate(x)) {
      x0 = x;
    } else {
      x1 = x;
    }
  }
  return x0;
}

void trialDivision(ll& n, vector<ll>& res, ll lim_p) {
  for (ll p = 2; p <= lim_p && p * p <= n; p++) {
    while (n % p == 0) { n /= p; res.push_back(p); }
  }
  if (2 <= n && n <= lim_p * lim_p) { res.push_back(n); n = 1; }
}

auto rng = mt19937(0x12345678);
auto miller_rabin = MillerRabin(rng);
auto quadratic_sieve = QuadraticSieve(rng);
const ll lim_trial_division = 1e6;

// Main
void mainCase() {
  ll n; // [1, 10^18]
  cin >> n;
  // [ Debug ]
  // quadratic_sieve.solve(n);
  // return;

  vector<ll> res;
  function<void(ll)> factorize = [&](ll n) {
    dbg(n);
    trialDivision(n, res, lim_trial_division);
    if (n == 1) { return; }
    if (miller_rabin.isPrime(n)) {
      res.push_back(n);
      return;
    }
    ll sqrt_n = getKthRoot(2, n);
    if (sqrt_n * sqrt_n == n) {
      factorize(sqrt_n);
      factorize(sqrt_n);
      return;
    }
    ll m = quadratic_sieve.solve(n);
    assert(m != -1);
    assert(1 < m && m < n && n % m == 0);
    factorize(m);
    factorize(n / m);
  };

  factorize(n);
  sort(ALL(res));

  cout << res.size();
  for (auto r : res) { cout << " " << r; }
  cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 100]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py library_checker/factorize/main_v2.cpp

%%%% begin
1
357984617619107
%%%%
2 3819797 93718231
%%%% end

%%%% begin
1
15347
%%%%
2 103 149
%%%% end

%%%% begin
1
1005973
%%%%
2 997 1009
%%%% end

%%%% begin
1
998244359987710471
%%%%
2 998244353 1000000007
%%%% end

%%%% begin
10
1
2
3
4
5
6
7
8
9
10
%%%%
0
1 2
1 3
2 2 2
1 5
2 2 3
1 7
3 2 2 2
2 3 3
2 2 5
%%%% end
*/
