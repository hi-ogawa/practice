// AC

//
// PROP.
//   ∑_{k <= n} σ(k)
//     = ∑_{k ≤ n} ∑_{d | k} d
//     = ∑_{d ≤ n} d |{k | k ≤ n ∧ d | k}|
//     = ∑_{d} d f(d)   (where f(d) = |{k | k ≤ n ∧ d | k}| )
//     = ∑_{d ≤ √n} d f(d)
//     + ∑_{m < √n} (∑_{d s.t. f(d) = m} d) m
//     = ∑_{d ≤ √n} d f(d)
//     + ∑_{m < √n} sum(n/(m+1), n/m] m
//

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

constexpr ll modulo = 1000'000'000 + 7;
ll madd(ll x, ll y) { return ((x % modulo) + (y % modulo)) % modulo; }
ll mmul(ll x, ll y) { return ((x % modulo) * (y % modulo)) % modulo; }
ll mexp(ll x, ll e) {
  ll res = 1;
  while (e > 0) {
    if (e & 1) { res = mmul(res, x); }
    x = mmul(x, x); e >>= 1;
  }
  return res;
}
ll minv(ll x) { return mexp(x, modulo - 2); }
ll mdiv(ll x, ll y) { return mmul(x, minv(y)); }

// Main
void mainCase() {
  ll n; // <= 10^12
  cin >> n;

  // sum (x0, x1]
  auto series = [](ll x0, ll x1) -> ll {
    return mdiv(mmul(x0 + x1 + 1, x1 - x0), 2);
  };

  ll res = 0;
  ll nsqrt = sqrt(n);

  // d s.t. n/d >= n^1/2
  for (ll d = 1; n / d >= nsqrt; d++) {
    ll t = mmul(d, (n / d));
    dbgv(d, n / d, t);
    res = madd(res, t);
  }

  // m < n^1/2
  for (ll m = 1; m < nsqrt; m++) {
    ll t = mmul(series(n / (m + 1), n / m), m);
    dbgv(m, t, n / (m + 1), n / m);
    res = madd(res, t);
  }

  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py cses/mathematics/task1082/main.cpp --check

%%%% begin
29
%%%%
%%%% end

%%%% begin
20
%%%%
%%%% end

%%%% begin
5
%%%%
21
%%%% end

%%%% begin
1000000000000
%%%%
%%%% end
*/
