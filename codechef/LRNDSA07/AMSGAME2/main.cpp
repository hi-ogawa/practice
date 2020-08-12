// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// gcd (for c++14)
ll _gcd(ll x, ll y) {
  if (x == 0) { return y; } if (y == 0) { return x; }
  bool xo = x & 1; bool yo = y & 1;
  if (!xo && !yo) { return _gcd(x >> 1, y >> 1) << 1; }     // even, even
  if (!xo &&  yo) { return _gcd(x >> 1, y); }               // even, odd
  if ( xo && !yo) { return _gcd(x, y >> 1); }               // odd, even
  if (x < y) { swap(x, y); } return _gcd((x - y) >> 1, y);  // odd, odd
}

// Main

// TLE
void mainCase_v1() {
  ll n; // <= 60
  cin >> n;
  vector<ll> ls(n, 0); // <= 10^4
  cin >> ls;

  ll m = *max_element(ALL(ls));
  vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));
  RANGE(i, 1, n + 1) {
    ll a = ls[i - 1];
    dp[i][a]++;
    RANGE(j, 1, m + 1) {
      dp[i][j] += dp[i - 1][j];
      dp[i][_gcd(a, j)] += dp[i - 1][j];
    }
  }
  // DD(ls);
  // cout << "dp:" << endl;
  // for (auto x : dp) { cout << x << endl; }

  cout << dp[n][1] << endl;
}

// Use "map" to update only non-zero entry
// (TODO: this avoids TLE but probably there can be a test case making this TLE?)
void mainCase_v2() {
  ll n; // <= 60
  cin >> n;
  vector<ll> ls(n, 0); // <= 10^4
  cin >> ls;

  vector<map<ll, ll>> dp(n + 1, map<ll, ll>());
  RANGE(i, 1, n + 1) {
    ll a = ls[i - 1];
    dp[i][a]++;
    for (auto jv : dp[i - 1]) {
      ll j, v;  tie(j, v) = jv;
      dp[i][j] += v;
      dp[i][_gcd(a, j)] += v;
    }
  }
  // cout << "dp:" << endl;
  // for (auto x : dp) { cout << x << endl; }

  cout << dp[n][1] << endl;
}

void mainCase() { mainCase_v2(); }

int main() {
  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA07/AMSGAME2/main.cpp --check

%%%% begin
3
4
2 3 5 7
4
3 4 8 16
3
6 10 15
%%%%
11
7
1
%%%% end
*/
