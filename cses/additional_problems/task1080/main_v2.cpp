// AFTER EDITORIAL, TLE

// NOTE: Improved to n^3 but not fact enough

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

  vector<vector<ll>> dp1(n, vector<ll>(n)); // Finish by picking "i"
  vector<vector<ll>> dp2(n, vector<ll>(n)); // Finish by any
  for (int l = 2; l <= n; l += 2) {
    for (int i = 0; i <= n - l; i++) {
      int j = i + l - 1;

      // Make dp1[i][j]
      ll tmp1 = 0;
      for (int k = 2; k <= l; k += 2) {
        // Last pair s[i] and s[jj]
        int jj = i + k - 1;
        if (s[i] != s[jj]) { continue; }
        ll x = k == 2 ? 1 : dp2[i + 1][jj - 1];
        ll y = k == l ? 1 : dp2[jj + 1][j];
        ll z = _.binom((l - 2) / 2, (k - 2) / 2);
        tmp1 = _.add(tmp1, _.mul(x, _.mul(y, z)));
      }
      dp1[i][j] = tmp1;

      // Make dp2[i][j]
      ll tmp2 = 0;
      for (int jj = i; jj < j; jj += 2) {
        // Last pair s[jj] and s[j]
        ll x = jj == i ? 1 : dp2[i][jj - 1];
        ll y = dp1[jj][j];
        ll z = _.binom((l - 2) / 2, (jj - i) / 2);
        tmp2 = _.add(tmp2, _.mul(x, _.mul(y, z)));
      }
      dp2[i][j] = tmp2;
    }
  }
  dbg2(dp1);
  dbg2(dp2);

  ll res = dp2[0][n - 1];
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
python misc/run.py cses/additional_problems/task1080/main_v2.cpp --check

%%%% begin
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
%%%%
%%%% end

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
