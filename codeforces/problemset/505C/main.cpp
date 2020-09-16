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
  int n, d;
  cin >> n >> d;
  vector<int> ls(n); // [1, 30000]
  cin >> ls;

  int m = *max_element(ALL(ls));
  map<int, int> cnts;
  for (auto x : ls) { cnts[x]++; }

  // Relavant jump range
  int jd = 2 * (sqrt(m) + 1);
  int j0 = max(1, d - jd);
  int j1 = d + jd + 1;

  // dp[i][j] = max point ending at "i" after "j" jump
  vector<vector<int>> _dp(m + j1 + 1, vector<int>(j1 - j0, -1));
  auto dp = [&](int i, int j) -> int& {
    assert(j0 <= j && j < j1);
    return _dp[i][j - j0];
  };
  auto maxeq = [](int& x, int y) { x = max(x, y); };

  dp(d, d) = cnts[d];
  FOR(i, d, m) {
    FOR(j, j0, j1) {
      if (dp(i, j) == -1) { continue; }
      if (j - 1 >= j0) {
        maxeq(dp(i + j - 1, j - 1), dp(i, j) + cnts[i + j - 1]);
      }
      if (j + 1 <  j1) {
        maxeq(dp(i + j + 1, j + 1), dp(i, j) + cnts[i + j + 1]);
      }
      maxeq(dp(i + j, j), dp(i, j) + cnts[i + j]);
    }
  }

  int res = 0;
  for (auto x : ls) {
    FOR(j, j0, j1) {
      res = max(res, dp(x, j));
    }
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/505C/main.cpp --check

%%%% begin
4 10
10
21
27
27
%%%%
3
%%%% end

%%%% begin
8 8
9
19
28
36
45
55
66
78
%%%%
6
%%%% end

%%%% begin
13 7
8
8
9
16
17
17
18
21
23
24
24
26
30
%%%%
4
%%%% end

*/
