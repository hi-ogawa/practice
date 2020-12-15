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

// Main
void mainCase() {
  ll a, b; // [0, m)
  ll m; // [1, 10^9]
  cin >> a >> b >> m;

  auto mod = [&](ll x, ll y) -> ll { x %= y; return x >= 0 ? x : (x + y); };

  auto pow = [&](ll x, ll e, ll m) -> ll {
    ll y = 1 % m;
    while (e > 0) {
      if (e & 1) { y = (y * x) % m; }
      e >>= 1;
      x = (x * x) % m;
    }
    return y;
  };

  auto solveCoprime = [&](ll x, ll a, ll b, ll m) -> ll {
    // x a^(q * n - r) = b
    //  <=> x (a^n)^q = b (a^r)
    dbg(x, a, b, m);
    ll n = sqrt(m);
    ll an = pow(a, n, m);
    unordered_map<ll, ll> lhs_ids;
    ll anq = 1;
    FOR(q, 1, m / n + 1) {
      anq = (anq * an) % m;
      ll lhs = (x * anq) % m;
      if (!lhs_ids.count(lhs)) { lhs_ids[lhs] = q; }
    }
    ll ar = 1;
    ll res = m;
    FOR(r, 1, n + 1) {
      ar = (ar * a) % m;
      ll rhs = (b * ar) % m;
      if (lhs_ids.count(rhs)) {
        res = min(res, lhs_ids[rhs] * n - r);
      }
    }
    return res == m ? -1 : res;
  };

  auto solve = [&](ll a, ll b, ll m) -> ll {
    assert(m >= 1);
    a = mod(a, m);
    b = mod(b, m);

    // x a^k = b ∈ Z(m)
    ll x = 1 % m;
    ll e1 = 0;
    while (true) {
      ll g = gcd(a, m);
      if (g == 1) { break; }

      // k = 0
      if (x == b) { return e1; }

      // No solution
      if (b % g != 0) { return -1; }

      // k > 0
      // x a^k = b ∈ Z(m) <=> x (a/g) a^(k - 1) = b/g ∈ Z(m/g)
      m /= g;
      b /= g;
      x = (x * (a / g)) % m;
      a %= m;
      e1++;
    }

    ll e2 = solveCoprime(x, a, b, m);
    if (e2 == -1) { return -1; }
    return e1 + e2;
  };

  auto res = solve(a, b, m);
  assert(res == -1 || pow(a, res, m) == b);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 100]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py library_checker/discrete_logarithm_mod/main_v2.cpp

%%%% begin
7
2 1 5
4 7 10
8 6 10
5 2 11
5 9 11
0 0 1
0 2 4
%%%%
0
-1
4
-1
4
0
-1
%%%% end
*/
