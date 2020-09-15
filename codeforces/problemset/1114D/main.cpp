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
  int n0;
  cin >> n0;
  vector<int> ls0(n0);
  cin >> ls0;

  // WLOG, all neighbors are distinct
  vector<int> ls;
  ls.push_back(ls0[0]);
  FOR(i, 1, n0) {
    if (ls.back() == ls0[i]) { continue; }
    ls.push_back(ls0[i]);
  }
  int n = ls.size();
  dbgv(n, ls);
  if (n == 1) { cout << 0 << endl; return; }

  // dp[i][j][0] = min cost to change ls[i:j] to ls[i]
  // dp[i][j][1] = min cost to change ls[i:j] to ls[j]
  vector<vector<array<int, 2>>> dp(n, vector<array<int, 2>>(n));
  FOR(i, 0, n - 1) {
    dp[i][i + 1] = {1, 1};
  }

  const int kInf = 1 << 30;
  for (int l = 2; l <= n; l++) {
    for (int i = 0; i < n - l; i++) {
      int j = i + l;
      int t0 = kInf, t1 = kInf;
      t0 = min(t0, dp[i + 1][j][0] + (ls[i] != ls[i + 1]));
      t0 = min(t0, dp[i + 1][j][1] + (ls[i] != ls[j]));
      t1 = min(t1, dp[i][j - 1][0] + (ls[i] != ls[j]));
      t1 = min(t1, dp[i][j - 1][1] + (ls[j] != ls[j - 1]));
      dp[i][j] = {t0, t1};
    }
  }

  int res = min(dp[0][n - 1][0], dp[0][n - 1][1]);
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1114D/main.cpp --check

%%%% begin
4
5 2 2 1
%%%%
2
%%%% end

%%%% begin
8
4 5 2 2 1 3 5 5
%%%%
4
%%%% end

%%%% begin
1
4
%%%%
0
%%%% end
*/
