// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, m; // [1, 5000]
  cin >> n >> m;
  string s1, s2;
  cin >> s1 >> s2;

  // dp(i, j) = max score for suffix of s1[:i] and s2[:j] (cf. Kadane's DP)
  vector<vector<int>> dp(n + 1, vector<int>(m + 1));

  FOR(i, 0, n) {
    FOR(j, 0, m) {
      int t1 = dp[i][j] + ((s1[i] == s2[j]) ? +2 : -2);
      int t2 = dp[i + 1][j] - 1;
      int t3 = dp[i][j + 1] - 1;
      dp[i + 1][j + 1] = max(0, max(t1, max(t2, t3)));
    }
  }

  int res = 0;
  FOR(i, 0, n + 1) {
    FOR(j, 0, m + 1) {
      res = max(res, dp[i][j]);
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1447/d/main.cpp

%%%% begin
4 5
abba
babab
%%%%
5
%%%% end

%%%% begin
8 10
bbbbabab
bbbabaaaaa
%%%%
12
%%%% end

%%%% begin
7 7
uiibwws
qhtkxcn
%%%%
0
%%%% end
*/
