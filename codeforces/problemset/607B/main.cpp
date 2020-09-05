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
  int n; // <= 500;
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  // dp[i][j] = min steps to remove ls[i:j] with last pick ls[i]
  vector<vector<int>> dp(n, vector<int>(n));
  int kInf = 1 << 30;
  FOR(i, 0, n) { dp[i][i] = 1; }
  FOR(l, 1, n) {
    FOR(i, 0, n - l) {
      // Make dp[i][j]
      int j = i + l;
      int t = kInf;
      // 1. Pick ls[i]
      t = min(t, 1 + dp[i + 1][j]);
      // 2. Pick ls[i] and ls[k] as a pair
      FOR(k, i + 1, j + 1) {
        if (ls[i] != ls[k]) { continue; }
        int s = 1;
        if (i + 1 <= k - 1) { s += dp[i + 1][k - 1] - 1; } // "-1" since we can merge (i, k) with inner palindrome.
        if (k + 1 <= j) { s += dp[k + 1][j]; }
        t = min(t, s);
      }
      dp[i][j] = t;
    }
  }
  dbg2(dp);

  int res = dp[0][n - 1];
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
python misc/run.py codeforces/problemset/607B/main.cpp --check

%%%% begin
4
1 4 4 1
%%%%
1
%%%% end

%%%% begin
7
1 4 4 2 3 2 1
%%%%
2
%%%% end
*/
