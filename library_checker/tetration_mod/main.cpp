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

const ll kInf = 1LL << 62;

// Main
void mainCase() {
  ll a, b, m; // [0, 10^9]
  cin >> a >> b >> m;

  auto totient = [](ll x) -> ll {
    ll y = x;
    for (ll p = 2; p * p <= x; p++) {
      if (x % p) { continue; }
      while (x % p == 0) { x /= p; }
      y = (y / p) * (p - 1);
    }
    if (x > 1) { y = (y / x) * (x - 1); }
    return y;
  };

  auto pow = [](ll x, ll e, ll m) -> ll {
    ll y = 1 % m;
    while (e > 0) {
      if (e & 1) { y = (y * x) % m; }
      e >>= 1;
      x = (x * x) % m;
    }
    return y;
  };

  auto mod = [](ll x, ll y) -> ll { x %= y; return x >= 0 ? x : (x + y); };

  auto pow_check_overflow = [](ll x, ll e) -> ll {
    ll y = 1;
    int overflow = 0;
    while (e > 0) {
      if (e & 1) {
        if (overflow) { return -1; }
        if (y > kInf / x) { return -1; }
        y *= x;
      }
      e >>= 1;
      if ((overflow |= (x > kInf / x))) { continue; }
      x *= x;
    }
    return y;
  };

  // Returns -1 if a↑↑b ≥ bound
  auto tetration_check_bound = [&](ll a, ll b, ll bound) -> ll {
    if (a == 0) {
      ll y = (b % 2) ^ 1;
      return (y < bound) ? y : -1;
    }
    ll y = 1;
    FOR(_, 0, b) {
      y = pow_check_overflow(a, y);
      if (y == -1 || y >= bound) { return -1; }
    }
    return y;
  };

  //
  // DEF.
  //   f(x, a, b, c, m) = x^(a↑↑b - c) % m (where a↑↑b - c ≥ 0)
  //
  function<ll(ll, ll, ll, ll, ll)> f = [&](ll x, ll a, ll b, ll c, ll m) -> ll {
    dbg(x, a, b, c, m);
    x %= m;
    if (m == 1) { return 0; }
    if (b == 0) { assert(c <= 1); return pow(x, 1 - c, m); }
    if (x == 0) {
      ll ab = tetration_check_bound(a, b, c + 1);
      assert(ab == -1 || ab == c);
      return (ab == -1) ? 0 : 1;
    }
    // x >= 1, b >= 1, m >= 2

    ll g = gcd(x, m);
    if (g == 1) {
      ll tm = totient(m);
      ll ab = f(a, a, b - 1, 0, tm);
      return pow(x, mod(ab - c, tm), m);
    }

    // m = k g^e
    ll k = m;
    ll e = 0;
    while (k % g == 0) { k /= g; e++; }

    ll ab = tetration_check_bound(a, b, c + e);
    if (ab != -1) {
      return pow(x, ab - c, m);
    }

    ll f1 = f(x / g, a, b, c,     m);
    ll f2 = f(g,     a, b, c + e, k) * m / k;
    return f1 * f2 % m;
  };

  auto solve = [&](ll a, ll b, ll m) -> ll {
    if (m == 1) { return 0; }
    if (b == 0) { return 1; }
    return f(a, a, b - 1, 0, m);
  };

  auto res = solve(a, b, m);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 10^3]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py library_checker/tetration_mod/main.cpp

%%%% begin
10
0 0 10
0 1 10
1 0 10
1 1 10
7 3 10
1 3 33
998 244 353
998244353 1333 1000000000
998244353 998244353 1333
1000000000 1000000000 133333
%%%%
1
0
1
1
3
1
140
998121473
170
94527
%%%% end

%%%% begin
10
2 2 1
2 2 2
2 2 3
2 2 4
2 2 5
3 3 1
3 3 2
3 3 3
3 3 4
3 3 5
%%%%
0
0
1
0
4
0
1
0
3
2
%%%% end
*/
