// MLE

// NOTE: Trivial O(n^3) solution

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
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<ll> ls(n); // [-10^9, 10^9]
  cin >> ls;

  const ll kInf = 1e18;

  using vec2 = array<ll, 2>;
  vector<vector<vec2>> dp(n, vector<vec2>(n + 1)); // (max, min)

  FOR(i, 0, n) {
    dp[i][i + 1] = {ls[i], ls[i]};
  }

  FOR(len, 2, n + 1) {
    FOR(i, 0, n - len + 1) {
      int j = i + len;
      vec2 t = {-kInf, kInf};
      FOR(k, i + 1, j) {
        auto [u1, v1] = dp[i][k];
        auto [u2, v2] = dp[k][j];
        t[0] = max(t[0], - v1 - v2);
        t[1] = min(t[1], - u1 - u2);
      }
      dp[i][j] = t;
    }
  }

  ll res = dp[0][n][0];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1421/e/main.cpp

%%%% begin
4
5 6 7 8
%%%%
26
%%%% end

%%%% begin
5
4 -5 9 -2 1
%%%%
15
%%%% end
*/
