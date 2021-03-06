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
#define DD(X) do { if (DEBUG) { std::cout << #X ": " << (X) << std::endl << std::flush; } } while (0)
#define DD2(X) do { if (DEBUG) { std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; } } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main

// Simple DP (TLE)
void mainCase_v1() {
  ll n, x; // n <= 40, x <= 10^9
  cin >> n >> x;
  vector<ll> ls(n, 0); // >= 1
  cin >> ls;
  sort(ALL(ls));
  DD(ls);

  map<ll, ll, greater<ll>> dp;
  dp[0] = 1;
  FOR(i, 0, n) {
    ll t = ls[i];
    for (auto [k, _v] : dp) {
      if (k + t <= x) { // culling
        dp[k + t] += dp[k];
      }
    }
    DD(dp);
  }
  ll res = dp[x];
  cout << res << endl;
}

// Simple DP with "meet in the middle" (AC)
void mainCase_v2() {
  ll n, x; // n <= 40, x <= 10^9
  cin >> n >> x;
  vector<ll> ls(n, 0); // >= 1
  cin >> ls;
  sort(ALL(ls)); // TODO: analyze consequence of sort
  DD(ls);

  auto doDp = [&](int i0, int i1) -> map<ll, ll, greater<ll>> {
    map<ll, ll, greater<ll>> dp;
    dp[0] = 1;
    FOR(i, i0, i1) {
      ll t = ls[i];
      for (auto [k, _v] : dp) {
        if (k + t <= x) {
          dp[k + t] += dp[k];
        }
      }
    }
    return dp;
  };
  auto dp1 = doDp(0, n / 2);
  auto dp2 = doDp(n / 2, n);
  DD(dp1.size());
  DD(dp2.size());
  // DD(dp1);
  // DD(dp2);

  ll res = 0;
  for (auto [y, yc] : dp1) {
    res += yc * dp2[x - y];
  }
  cout << res << endl;
}

void mainCase() { mainCase_v2(); }

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
python misc/run.py cses/additional_problems/task1628/main.cpp --check

%%%% begin
4 5
1 2 3 2
%%%%
3
%%%% end
*/
