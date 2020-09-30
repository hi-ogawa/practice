// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = begin(x); it != end(x); it++) { if (it != begin(x)) { o << ", "; } o << *it; } o << "}"; return o; }
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
  int n, k; // [1, 500]
  cin >> n >> k;
  vector<int> ls(n); // [1, 500]
  cin >> ls;

  // dp[n, s1, s2] = 1 \iff we can make two disjoint sum s1 and s2 out of (c1, c2, .., cn)
  vector<vector<bool>> dp(k + 1, vector<bool>(k + 1));
  dp[0][0] = 1;
  auto dp_prev = dp;
  FOR(i, 0, n) {
    int x = ls[i];
    FOR(s1, 0, k + 1) {
      FOR(s2, 0, k + 1) {
        if (s1 >= x) { dp[s1][s2] = dp[s1][s2] | dp_prev[s1 - x][s2]; }
        if (s2 >= x) { dp[s1][s2] = dp[s1][s2] | dp_prev[s1][s2 - x]; }
      }
    }
    dp_prev = dp;
  }
  dbg2(dp);

  vector<int> res;
  FOR(x, 0, k + 1) {
    if (dp[x][k - x]) { res.push_back(x); }
  }

  int m = res.size();
  cout << m << "\n";
  FOR(i, 0, m) {
    cout << res[i] << " \n"[i == m - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/687C/main.cpp --check

%%%% begin
6 18
5 6 1 10 12 2
%%%%
16
0 1 2 3 5 6 7 8 10 11 12 13 15 16 17 18
%%%% end

%%%% begin
3 50
25 25 50
%%%%
3
0 25 50
%%%% end
*/
