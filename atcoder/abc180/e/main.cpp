// CONTEST, AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
  int n; // [2, 17]
  cin >> n;
  vector<array<int, 3>> ls(n); // [-10^6, 10^6]
  cin >> ls;

  //
  // PROP.
  //   This non-symmetric distance satisfies triangle inequality.
  //   Thus, there exists optimal path which is simple.
  //

  vector<vector<int>> dists(n, vector<int>(n));
  FOR(i, 0, n) {
    auto [a, b, c] = ls[i];
    FOR(j, 0, n) {
      auto [p, q, r] = ls[j];
      dists[i][j] = abs(p - a) + abs(q - b) + max(0, r - c);
    }
  }

  // Solve TSP
  const int kInf = 1e8;
  vector<vector<int>> dp(1 << n, vector<int>(n, kInf));
  dp[0][0] = 0;
  FOR(s, 0, 1 << n) {
    FOR(v1, 0, n) {
      int sv1 = s | (1 << v1);
      if (s == sv1) { continue; }
      FOR(v2, 0, n) {
        if (sv1 & (1 << v2)) { continue; }
        int t = dp[s][v1] + dists[v1][v2];
        dp[sv1][v2] = min(dp[sv1][v2], t);
      }
    }
  }

  int res = kInf;
  FOR(v, 0, n) {
    int s = ((1 << n) - 1) ^ (1 << v);
    int t = dp[s][v] + dists[v][0];
    res = min(res, t);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc180/e/main.cpp

%%%% begin
17
14142 13562 373095
-17320 508075 68877
223606 -79774 9979
-24494 -89742 783178
26457 513110 -64591
-282842 7124 -74619
31622 -77660 -168379
-33166 -24790 -3554
346410 16151 37755
-36055 51275 463989
37416 -573867 73941
-3872 -983346 207417
412310 56256 -17661
-42426 40687 -119285
43588 -989435 -40674
-447213 -59549 -99579
45825 7569 45584
%%%%
6519344
%%%% end
*/
