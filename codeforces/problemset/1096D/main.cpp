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

// Main
void mainCase() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  vector<ll> ls(n);
  cin >> ls;

  // dp[i][0] = min cost edit s[:i] to have only ""
  // dp[i][1] = min cost edit s[:i] to have only "h"
  // dp[i][2] = min cost edit s[:i] to have only "ha"
  // dp[i][3] = min cost edit s[:i] to have only "har"
  vector<array<ll, 4>> dp(n + 1);
  FOR(i, 1, n + 1) {
    char c = s[i - 1];
    ll x = ls[i - 1];
    if (c == 'h') {
      dp[i][0] = dp[i - 1][0] + x;
      dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]);
      dp[i][2] = dp[i - 1][2];
      dp[i][3] = dp[i - 1][3];
      continue;
    }
    if (c == 'a') {
      dp[i][0] = dp[i - 1][0];
      dp[i][1] = dp[i - 1][1] + x;
      dp[i][2] = min(dp[i - 1][1], dp[i - 1][2]);
      dp[i][3] = dp[i - 1][3];
      continue;
    }
    if (c == 'r') {
      dp[i][0] = dp[i - 1][0];
      dp[i][1] = dp[i - 1][1];
      dp[i][2] = dp[i - 1][2] + x;
      dp[i][3] = min(dp[i - 1][2], dp[i - 1][3]);
      continue;
    }
    if (c == 'd') {
      dp[i][0] = dp[i - 1][0];
      dp[i][1] = dp[i - 1][1];
      dp[i][2] = dp[i - 1][2];
      dp[i][3] = dp[i - 1][3] + x;
      continue;
    }
    dp[i] = dp[i - 1];
  }
  dbg(dp);

  ll res = *min_element(ALL(dp[n]));
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1096D/main.cpp --check

%%%% begin
6
hhardh
3 2 9 11 7 1
%%%%
5
%%%% end

%%%% begin
8
hhzarwde
3 2 6 9 4 8 7 1
%%%%
4
%%%% end

%%%% begin
6
hhaarr
1 2 3 4 5 6
%%%%
0
%%%% end
*/
