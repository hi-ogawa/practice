// AFTER EDITORIAL, TLE

// NOTE: n^4 solution

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

// Modulo
template<ll M>
struct ModOp {
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
  string s;
  cin >> s;
  int n = s.size(); // <= 500

  static ModOp<1000'000'000 + 7> _;
  _.makeFact(n);

  // Time ~ n^4
  vector<vector<ll>> dp(n, vector<ll>(n));
  for (int l = 2; l <= n; l += 2) {
    for (int i = 0; i <= n - l; i++) {
      // Solve s[i:i+l]
      ll tmp = 0;
      FOR(j1, i, i + l) {
        FOR(j2, j1 + 1, i + l) {
          // Pick s[j1] and s[j2] as last pair
          if (s[j1] != s[j2]) { continue; }
          int k1 = j1 - i;
          int k2 = j2 - j1 - 1;
          int k3 = l - k1 - k2 - 2;
          ll x = k1 == 0 ? 1 : dp[i][j1 - 1];
          ll y = k2 == 0 ? 1 : dp[j1 + 1][j2 - 1];
          ll z = k3 == 0 ? 1 : dp[j2 + 1][i + l - 1];
          ll w = _.binom((k1 + k2 + k3) / 2, k1 / 2);
          ll v = _.binom((k2 + k3) / 2, k2 / 2);
          tmp = _.add(tmp, _.mul(x, _.mul(y, _.mul(z, _.mul(w, v)))));
        }
      }
      dbgv(i, l, tmp);
      dp[i][i + l - 1] = tmp;
    }
  }
  dbg2(dp);

  ll res = dp[0][n - 1];
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
python misc/run.py cses/additional_problems/task1080/main.cpp --check

%%%% begin
aaaaaaaaaaaaaaaaaaaa
%%%%
654729075
%%%% end

%%%% begin
aaaa
%%%%
3
%%%% end

%%%% begin
01102332
%%%%
6
%%%% end

%%%% begin
aaaaaa
%%%%
15
%%%% end

%%%% begin
aabccb
%%%%
3
%%%% end
*/
