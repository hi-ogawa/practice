
// NOTE: Tree matching like DP (cf. cses/tree_algorithms/task1130/main_v2.cpp)

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

// Modulo op
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
};

// Main
void mainCase() {
  ll n;
  cin >> n;

  static ModOp<1000'000'000 + 7> _;

  vector<array<ll, 2>> dp(n + 1);
  FOR(i, 3, n + 1) {
    // dp[i][0] = dp[i - 1][1] + 2 * dp[i - 2][1];
    // dp[i][1] = dp[i - 1][0] + 2 * dp[i - 2][0] + 1;
    dp[i][0] = _.add(dp[i - 1][1], _.mul(2, dp[i - 2][1]));
    dp[i][1] = _.add(dp[i - 1][0], _.add(_.mul(2, dp[i - 2][0]), 1));

    // we want to take max but it's not really valid in Zp...
    // (probably, we are supposed to analyze which gets larger by parity or something)
    // (probably, it becomes possible to compute such linear recurrence by binary expo)
    dp[i][1] = max(dp[i][0], dp[i][1]);
  }
  dbg(dp);
  dbg(_.mul(4, dp[n][0]));
  dbg(_.mul(4, dp[n][1]));

  ll res = _.mul(4, max(dp[n][0], dp[n][1]));
  cout << res << endl;
}

int main() {
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
python misc/run.py codeforces/problemset/1369D/main.cpp --check

%%%% begin
1
3
%%%%
4
%%%% end

%%%% begin
7
1
2
3
4
5
100
2000000
%%%%
0
0
4
4
12
990998587
804665184
%%%% end
*/
