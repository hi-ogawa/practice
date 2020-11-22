// CONTEST, AC

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

using Real = double;

template<class T>
using V = vector<T>;

// Main
void mainCase() {
  int a, b, c; // [0, 99] (a + b + c <= 1)
  cin >> a >> b >> c;

  const int n = 100;
  V<V<V<Real>>> dp(n + 1, V<V<Real>>(n + 1, V<Real>(n + 1)));
  dp[a][b][c] = 1;
  FOR(i, a, n) {
    FOR(j, b, n) {
      FOR(k, c, n) {
        dp[i + 1][j][k] += dp[i][j][k] * (Real(i) / Real(i + j + k));
        dp[i][j + 1][k] += dp[i][j][k] * (Real(j) / Real(i + j + k));
        dp[i][j][k + 1] += dp[i][j][k] * (Real(k) / Real(i + j + k));
      }
    }
  }

  Real res = 0;
  FOR(i, a, n) {
    FOR(j, b, n) {
      res += dp[i][j][n] * Real((i - a) + (j - b) + (n - c));
    }
  }
  FOR(j, b, n) {
    FOR(k, c, n) {
      res += dp[n][j][k] * Real((n - a) + (j - b) + (k - c));
    }
  }
  FOR(k, c, n) {
    FOR(i, a, n) {
      res += dp[i][n][k] * Real((i - a) + (n - b) + (k - c));
    }
  }

  cout << fixed << setprecision(15) << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc184/d/main.cpp

%%%% begin
99 99 99
%%%%
1.000000000
%%%% end

%%%% begin
98 99 99
%%%%
1.331081081
%%%% end

%%%% begin
0 0 1
%%%%
99.000000000
%%%% end

%%%% begin
31 41 59
%%%%
91.835008202
%%%% end
*/
