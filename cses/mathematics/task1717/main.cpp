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

template<ll M>
struct ModOp {
  ll m = M;
  ll add(ll x, ll y) { return (x + y) % M; }
  ll mul(ll x, ll y) { return (x * y) % M; }
  ll div(ll x, ll y) { return mul(x, inv(y)); }
  ll inv(ll x)       { return pow(x, M - 2); }
  ll pow(ll x, ll e) {
    ll y = 1;
    while (e > 0) {
      if (e & 1) { y = mul(y, x); }
      x = mul(x, x); e >>= 1;
    }
    return y;
  }

  vector<ll> fact_;
  void makeFact(ll n) {
    if (fact_.size()) { return; }
    fact_.resize(n + 1);
    fact_[0] = 1;
    FOR(x, 1, n + 1) { fact_[x] = mul(x, fact_[x - 1]); }
  }
  ll fact(ll n) { return fact_[n]; }
  ll binom(ll n, ll k) { return div(fact(n), mul(fact(n - k), fact(k))); }
};


// Main
void mainCase() {
  ll n; // <= 10^6
  cin >> n;

  static ModOp<1000'000'000 + 7> mo;
  mo.makeFact(1000'000);

  // Count "no-fix" permutation (f(x) != x) by inc-exc trick
  //  Ai = {f | f(i) = i}
  //  |¬⋃i Ai| = ∑_{I ⊂ {1..n}} (-1)^|I| |⋂i∈I Ai|
  //           = ∑_k (-1)^k binom(n, k) fact(n - k)
  ll res = 0;
  FOR(k, 0, n + 1) {
    ll s = k % 2 ? -1 : 1;
    res = mo.add(res, s * mo.mul(mo.binom(n, k), mo.fact(n - k)));
  }
  res = mo.add(res, mo.m); // force to positive
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
python misc/run.py cses/mathematics/task1717/main.cpp --check

%%%% begin
4
%%%%
9
%%%% end
*/
