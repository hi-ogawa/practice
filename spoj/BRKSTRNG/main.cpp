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
  int v, m; // l \in [1, 10^7], n \in [1, 10^3]
  cin >> v >> m;
  vector<int> ls(m);
  cin >> ls;

  // Cumsums
  int n = m + 1;
  vector<int> ps;
  ps.push_back(0);
  ps.insert(ps.end(), ALL(ls));
  ps.push_back(v);

  // Knuth DP
  // TODO: prove monotonicity of optimal indices
  ll kInf = 1e18;
  vector<vector<ll>> dp(n, vector<ll>(n + 1, kInf));
  vector<vector<int>> dp2(n, vector<int>(n + 1));
  FOR(i, 0, n) {
    dp[i][i + 1] = 0;
    if (i + 2 <= n) {
      dp[i][i + 2] = ps[i + 2] - ps[i];
      dp2[i][i + 2] = i + 1;
    }
  }
  FOR(l, 3, n + 1) {
    FOR(i, 0, n - l + 1) {
      int j = i + l;
      int k0 = dp2[i][j - 1], k1 = dp2[i + 1][j];
      FOR(k, k0, k1 + 1) {
        ll f = dp[i][k] + dp[k][j];
        if (f < dp[i][j]) {
          dp[i][j] = f;
          dp2[i][j] = k;
        }
      }
      dp[i][j] += ps[j] - ps[i];
    }
  }
  // dbg2(dp);
  // dbg2(dp2);

  ll res = dp[0][n];
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  char c;
  while (cin >> c) {
    cin.putback(c);
    mainCase();
  }
  return 0;
}

/*
python misc/run.py spoj/BRKSTRNG/main.cpp --check

%%%% begin
20 3
3 8 10
20 4
2 3 8 10
%%%%
37
40
%%%% end
*/
