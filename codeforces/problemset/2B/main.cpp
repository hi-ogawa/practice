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
  int n; // n <= 10^3
  cin >> n;
  vector<vector<int>> board(n, vector<int>(n));
  cin >> board;
  dbg2(board);

  auto getExponent = [](int x, int b) -> int {
    int res = 0;
    while (x % b == 0) { x /= b; res++; }
    return res;
  };

  using ivec3 = array<int, 3>;

  // A bit weird encoding for handling "zero path"
  vector<vector<array<int, 3>>> board2(n, vector<array<int, 3>>(n));
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      int x = board[i][j];
      int e2 = x == 0 ? 1 : getExponent(x, 2);
      int e5 = x == 0 ? 1 : getExponent(x, 5);
      board2[i][j] = {e2, e5, -(x == 0)}; // Negate so that minimum gives "zero path"
    }
  }

  vector<vector<ivec3>> dp(n, vector<ivec3>(n));
  auto add3 = [](const ivec3& x, const ivec3& y) -> ivec3 {
    return {x[0] + y[0], x[1] + y[1], x[2] + y[2]};
  };
  auto min3 = [](const ivec3& x, const ivec3& y) -> ivec3 {
    return {min(x[0], y[0]), min(x[1], y[1]), min(x[2], y[2])};
  };

  dp[0][0] = board2[0][0];
  FOR(i, 1, n) { dp[i][0] = add3(dp[i - 1][0], board2[i][0]); }
  FOR(j, 1, n) { dp[0][j] = add3(dp[0][j - 1], board2[0][j]); }
  FOR(i, 1, n) {
    FOR(j, 1, n) {
      dp[i][j] = add3(min3(dp[i - 1][j], dp[i][j - 1]), board2[i][j]);
    }
  }
  dbg2(dp);

  auto [min2, min5, zero_cnt] = dp[n - 1][n - 1];
  dbgv(min2, min5, zero_cnt);

  bool take_zero = zero_cnt < 0 && min2 > 0 && min5 > 0;
  int res1 = take_zero ? 1 : min(min2, min5);
  string res2;

  // Which index to track
  int id = take_zero ? 2 : (min2 < min5) ? 0 : 1;
  dbg(id);

  int i = n - 1, j = n - 1;
  while (i != 0 || j != 0) {
    if (j == 0) {
      i--; res2 += "D";
      continue;
    }
    if (i == 0) {
      j--; res2 += "R";
      continue;
    }
    if (dp[i][j][id] == dp[i - 1][j][id] + board2[i][j][id]) {
      i--; res2 += "D";
      continue;
    }
    if (dp[i][j][id] == dp[i][j - 1][id] + board2[i][j][id]) {
      j--; res2 += "R";
      continue;
    }
    assert(0);
  }
  reverse(ALL(res2));
  dbgv(res1, res2);

  cout << res1 << endl << res2 << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py codeforces/problemset/2B/main.cpp --check

%%%% begin
3
1 2 3
4 5 6
7 8 9
%%%%
0
DDRR
%%%% end
*/
