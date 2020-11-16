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
  int n, k; // [1, 200]
  cin >> n >> k;
  vector<ll> ls(n); // [1, 10^18]
  cin >> ls;

  vector<int> xs(n), ys(n); // log(10^18, 5) <= 26
  FOR(i, 0, n) {
    ll z = ls[i];
    while (z % 2 == 0) {
      z /= 2;
      xs[i]++;
    }
    while (z % 5 == 0) {
      z /= 5;
      ys[i]++;
    }
  }
  dbg(xs, ys);

  // DP for solving max_{|S| = k} min(∑_{i ∈ S} x(i), ∑_{i ∈ S} y(i))

  // dp(L, Y) = max { ∑_{i ∈ S} x(i) | |S| = L and ∑_{i ∈ S} y(i) = Y }

  int m = accumulate(ALL(ys), 0); // <= 200 * 26 ~ 5000
  vector<vector<int>> dp(k + 1, vector<int>(m + 1, -1));
  dp[0][0] = 0;

  // O(n * k * m) ~ 2e8
  FOR(i, 0, n) {
    int x = xs[i], y = ys[i];
    for (int l = k; l >= 1; l--) { // Reverse to avoid double counting
      for (int j = m; j >= y; j--) {
        if (dp[l - 1][j - y] == -1) { continue; }
        dp[l][j] = max(dp[l][j], dp[l - 1][j - y] + x);
      }
    }
  }
  dbg2(dp);

  int res = 0;
  FOR(y, 0, m + 1) {
    if (dp[k][y] == -1) { continue; }
    int t = min(y, dp[k][y]);
    res = max(res, t);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/837D/main.cpp

%%%% begin
3 2
50 4 20
%%%%
3
%%%% end

%%%% begin
5 3
15 16 3 25 9
%%%%
3
%%%% end

%%%% begin
3 3
9 77 13
%%%%
0
%%%% end
*/
