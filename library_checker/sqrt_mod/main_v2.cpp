// AC

// Cf. https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm

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
  ll y; // [0, p)
  ll p; // [2, 10^9], prime
  cin >> y >> p;
  if (p == 2) { cout << y << "\n"; return; }

  ZpSqrt zp_sqrt(p);

  ll res = zp_sqrt.solve(y);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 10^5]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py library_checker/sqrt_mod/main_v2.cpp

%%%% begin
5
0 5
1 5
2 5
3 5
4 5
%%%%
0
1
-1
-1
2
%%%% end
*/
