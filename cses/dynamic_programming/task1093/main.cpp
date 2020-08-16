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

// Modulo
constexpr ll kModulo = 1000000000 + 7;
ll madd(ll x, ll y) { return (x + y) % kModulo; }
ll mmul(ll x, ll y) { return (x * y) % kModulo; }
ll mexp(ll b, ll e) {
  ll res = 1;
  ll be = b;
  while (e > 0) {
    if (e & 1) { res = mmul(res, be); }
    be = mmul(be, be);
    e >>= 1;
  }
  return res;
}
ll minv(ll x) { return mexp(x, kModulo - 2); } // Zp* inverse

// Main
void mainCase() {
  ll n; // <= 500
  cin >> n;

  ll total = (n * (n + 1)) / 2;
  if (total % 2) {
    cout << 0 << endl;
    return;
  }

  ll x = total / 2;
  // DD(tie(total, x));

  vector<ll> dp(x + 1, 0);
  dp[0] = 1;
  FOR(i, 1, n + 1) {
    for (ll j = x; j >= i; j--) {
      dp[j] = madd(dp[j], dp[j - i]);
    }
    // DD(dp);
  }
  ll res = mmul(dp[x], minv(2));
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
python misc/run.py cses/dynamic_programming/task1093/main.cpp --check

%%%% begin
107
%%%%
589938798
%%%% end

%%%% begin
7
%%%%
4
%%%% end
*/
