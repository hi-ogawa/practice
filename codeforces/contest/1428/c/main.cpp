// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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
  string s; // A/B
  cin >> s;
  int n = s.size(); // [1, 2 x 10^5]

  const int kInf = 1e9;

  // TODO: prove/disprove optimality

  // dp(i, 0) = min result for ls[:i] becoming 0...0
  // dp(i, 1) = min result for ls[:i] becoming 10..0
  vector<array<int, 2>> dp(n + 1, {kInf, kInf});
  dp[0][0] = 0;
  FOR(i, 0, n) {
    int x = s[i] - 'A'; // 0/1
    if (x == 0) {
      dp[i + 1][0] = dp[i][0] + 1;
      dp[i + 1][1] = dp[i][1] + 1;
    }
    if (x == 1) {
      if (dp[i][0] == 0) {
        dp[i + 1][0] = 1;
      }
      if (dp[i][0] > 0) {
        dp[i + 1][0] = dp[i][0] - 1;
      }
      if (dp[i][1] == 1) {
        dp[i + 1][0] = 0;
      }
      if (dp[i][1] > 1) {
        dp[i + 1][1] = dp[i][1] - 1;
      }
    }
  }
  dbg(dp);

  int res = *min_element(ALL(dp[n]));
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1428/c/main.cpp

%%%% begin
3
AAA
BABA
AABBBABBBB
%%%%
3
2
0
%%%% end
*/
