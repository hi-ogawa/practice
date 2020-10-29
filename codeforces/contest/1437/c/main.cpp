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
  int n; // [1, 200]
  cin >> n;
  vector<int> xs(n); // [1, n]
  cin >> xs;
  sort(ALL(xs));

  //
  // Minimize ∑ |xi - yi|
  /// where
  //    1 ≤ x1 ≤ x2 ≤ ...
  //    1 ≤ y1 < y2 < ... (i.e. distinct)
  //

  const int kInf = 1e9;
  int k = 2 * n;

  // dp(i, y) = min cost for the case (x1, .., xi) and (y1, .., yi ≤ y)
  vector<int> dp(k + 1), dp_prev;
  FOR(i, 0, n) {
    dp_prev = dp;
    int x = xs[i];
    FOR(y1, 0, k + 1) {
      int t = kInf;
      FOR(y2, 0, y1) {
        t = min(t, dp_prev[y2] + abs(x - y1));
      }
      dp[y1] = t;
    }
  }

  int res = *min_element(ALL(dp));
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
python misc/run.py codeforces/contest/1437/c/main.cpp

%%%% begin
6
6
4 2 4 4 5 2
7
7 7 7 7 7 7 7
1
1
5
5 1 2 4 3
4
1 4 4 4
21
21 8 1 4 1 5 21 1 8 21 11 21 11 3 12 8 19 15 9 11 13
%%%%
4
12
0
0
2
21
%%%% end
*/
