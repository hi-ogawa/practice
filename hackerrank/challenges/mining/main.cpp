// WIP

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
  int n, m; // [1, 5000]
  cin >> n >> m;
  vector<array<int, 2>> ls(n);
  cin >> ls;

  // Segment costs
  vector<vector<ll>> costs(n, vector<ll>(n + 1));
  // TODO

  // DP divide conquer
  vector<vector<ll>> dp(m + 1, vector<ll>(n));

  function<void(int, int, int, int)> runDP = [](
      int i, int j0, int j1, int k0, int k1) {
    // int j = (j0 + j1) / 2;
    // j0, j
    // j, j1
    // runDP(i);
  };

  FOR(i, 2, m + 1) {
    runDP(i, 0, n, 0, n);
  }

  ll res = dp[m][n - 1];
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py hackerrank/challenges/mining/main.cpp --check

%%%% begin
3 1
20 1
30 1
40 1
%%%%
20
%%%% end

%%%% begin
3 1
11 3
12 2
13 1
%%%%
4
%%%% end

%%%% begin
6 2
10 15
12 17
16 18
18 13
30 10
32 1
%%%%
182
%%%% end
*/
