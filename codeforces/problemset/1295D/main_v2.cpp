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

vector<array<ll, 2>> factorize(ll n) {
  vector<array<ll, 2>> res;
  for (ll p = 2; p <= sqrt(n); p++) {
    if (n % p == 0) {
      ll e = 0;
      while (n % p == 0) { n /= p; e++; }
      res.push_back({p, e});
    }
  }
  if (n > 1) { res.push_back({n, 1}); }
  return res;
}

ll totient(ll n) { // By multiplicative property
  auto factors = factorize(n);
  ll res = n;
  for (auto [p, _e] : factors) {
    res = (res / p) * (p - 1);
  }
  return res;
}

// Main
void mainCase() {
  ll a, m; // [1, 10^10]
  cin >> a >> m;

  //
  // PROP.
  //   For g | m,
  //     #{ x | gcd(x, m)   = g } (⊂ Z_m)
  //   = #{ x | gcd(x, m/g) = 1 } (⊂ Z_m/g)
  //

  ll g = gcd(a, m);
  ll res = totient(m / g);
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1295D/main_v2.cpp --check

%%%% begin
3
4 9
5 10
42 9999999967
%%%%
6
1
9999999966
%%%% end
*/
