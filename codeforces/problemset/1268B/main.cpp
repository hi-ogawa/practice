// WA

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
  vector<int> ls(n); // decreasing
  cin >> ls;

  if (n == 1) { cout << (ls[0] / 2) << endl; return; }

  // dp[i][0] = max gain when [0, ls[i]] is used
  // dp[i][1] = max gain when [ls[i + 1], ls[i]] is used

  // TODO: probably, we need to check if "one more cell" is avilable.

  vector<array<ll, 2>> dp(n);
  dp[0][0] = (ls[1] - ls[0]) / 2;
  dp[0][1] = ls[0] / 2;
  FOR(i, 1, n - 1) {
    int y = ls[i], z = ls[i + 1];
    dp[i][0] = max(
      dp[i - 1][0] + (y - z) + z / 2,
      dp[i - 1][1] + (y - z) / 2);
    dp[i][1] = max(
      dp[i - 1][0] + y,
      dp[i - 1][1] + y / 2); // TODO: feels maybe we can squeeze one more if odd...
  }
  dbg(dp);

  ll res1 = dp[n - 2][0] + ls[n - 1];
  ll res2 = dp[n - 2][1] + ls[n - 1] / 2;
  ll res = max(res1, res2);
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1268B/main.cpp --check

%%%% begin
5
3 2 2 2 1
%%%%
4
%%%% end
*/
