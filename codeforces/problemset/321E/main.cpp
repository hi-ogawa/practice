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
  int n, m; // n \in [1, 4000], m \in [1, 800]
  cin >> n >> m;
  vector<vector<int>> ls(n, vector<int>(n)); // \in [0, 9]
  cin >> ls;

  // Cum sum each row
  vector<vector<int>> ps(n, vector<int>(n + 1));
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      ps[i][j + 1] = ps[i][j] + ls[i][j];
    }
  }

  // Segment costs
  vector<vector<int>> costs(n, vector<int>(n + 1));
  FOR(i, 0, n) {
    FOR(j, i + 1, n + 1) {
      int c = ps[j - 1][j - 1] - ps[j - 1][i];
      costs[i][j] = costs[i][j - 1] + c;
    }
  }
  dbg2(costs);

  // Divide/Conquer DP
  // TODO: prove monotonicity of "k"

  const int kInf = 1e9;
  vector<vector<int>> dp(m + 1, vector<int>(n + 1));
  dp[1] = costs[0];

  function<void(int, int, int, int, int)> runDP = [&](
      int i, int j0, int j1, int k0, int k1) {
    if (j0 == j1) { return; }
    int j = (j0 + j1) / 2;
    int tt = kInf;
    int kk = 0;
    dbgv(i, j, j0, j1, k0, k1);
    FOR(k, k0, min(k1 + 1, j)) {
      int t = dp[i - 1][k] + costs[k][j];
      dbgv(i, k);
      if (t < tt) {
        tt = t; kk = k;
      }
    }
    dp[i][j] = tt;
    runDP(i, j0,     j, k0, kk);
    runDP(i, j + 1, j1, kk, k1);
  };

  FOR(i, 2, m + 1) {
    runDP(i, 1, n + 1, 1, n);
  }
  dbg2(dp);

  int res = dp[m][n];
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/321E/main.cpp --check

%%%% begin
5 2
0 0 1 1 1
0 0 1 1 1
1 1 0 0 0
1 1 0 0 0
1 1 0 0 0
%%%%
0
%%%% end

%%%% begin
8 3
0 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1
1 1 0 1 1 1 1 1
1 1 1 0 1 1 1 1
1 1 1 1 0 1 1 1
1 1 1 1 1 0 1 1
1 1 1 1 1 1 0 1
1 1 1 1 1 1 1 0
%%%%
7
%%%% end

%%%% begin
3 2
0 2 0
2 0 3
0 3 0
%%%%
2
%%%% end
*/
