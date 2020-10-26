// CONTEST, WA

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
  int k = 6;
  vector<int> xs(k); // [1, 10^9]
  cin >> xs;
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ys(n); // [1, 10^9]
  cin >> ys;
  sort(ALL(xs));
  sort(ALL(ys));

  vector<vector<int>> ls(k, vector<int>(n));
  FOR(i, 0, k) {
    FOR(j, 0, n) {
      ls[i][j] = ys[j] - xs[i];
    }
  }
  dbg2(ls);

  // TODO: prove/disprove optimality

  const int kInf = 1e9;
  vector<vector<array<int, 2>>> dp(k, vector<array<int, 2>>(n)); // (min, max)
  FOR(i, 0, k) {
    dp[i][0] = {ls[i][0], ls[i][0]};
  }
  FOR(j, 1, n) {
    FOR(i1, 0, k) {
      int x = ls[i1][j];
      int t0 = 0, t1 = kInf;
      FOR(i2, 0, i1 + 1) {
        auto [s0, s1] = dp[i2][j - 1];
        s0 = min(s0, x);
        s1 = max(s1, x);
        if (s1 - s0 < t1 - t0) {
          t0 = s0;
          t1 = s1;
        }
      }
      dp[i1][j] = {t0, t1};
    }
  }
  dbg2(dp);

  int res = kInf;
  FOR(i, 0, k) {
    auto [t0, t1] = dp[i][n - 1];
    res = min(res, t1 - t0);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1435/c/main.cpp

%%%% begin
1 4 100 10 30 5
6
101 104 105 110 130 200
%%%%
0
%%%% end

%%%% begin
1 1 2 2 3 3
7
13 4 11 12 11 13 12
%%%%
7
%%%% end
*/
