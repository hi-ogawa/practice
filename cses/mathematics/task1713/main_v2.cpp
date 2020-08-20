// AC

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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// (0th) divisor function
//   σ(p^e) = e + 1 with multiplicativity
vector<ll> makeDivisors(ll n) {
  vector<ll> res(n + 1, 1);
  vector<bool> sieve(n + 1, 1);
  res[0] = 0;
  sieve[0] = sieve[1] = 0;
  for (ll p = 2; p <= n; p++) {
    // Usual sieve
    if (sieve[p] == 0) { continue; }
    for (ll x = p * p; x <= n; x += p) {
      sieve[x] = 0;
    }

    // ν_p(x) = e
    for (ll e = 1, pe = p; pe <= n; e++, pe *= p) {
      for (ll i = 1, x = pe; x <= n; i++, x += pe) {
        if (i % p == 0) { continue; }
        res[x] *= (e + 1);
      }
    }
  }
  // DD(sieve);
  // DD(res);
  return res;
}

// Main
vector<ll> res;
void precompute() {
  ll x_lim = 1000'000;
  // ll x_lim = 50;
  res = makeDivisors(x_lim);
}

void mainCase() {
  ll x; // <= 10^6
  cin >> x;
  cout << res[x] << endl;
}

int main() {
  precompute();

  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py cses/mathematics/task1713/main_v2.cpp --check

%%%% begin
3
16
17
18
%%%%
5
2
6
%%%% end
*/
