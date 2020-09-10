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
  int n, m, k; // n <= 18
  cin >> n >> m >> k;
  vector<ll> ls(n);
  cin >> ls;
  vector<array<ll, 3>> edges(k);
  cin >> edges;

  vector<vector<ll>> bonus(n, vector<ll>(n));
  for (auto [x, y, c] : edges) {
    x--; y--;
    bonus[x][y] += c;
  }

  // [ Without "exactly before "]
  // vector<ll> dp(1 << n);
  // FOR(s, 0, 1 << n) {
  //   FOR(v, 0, n) {
  //     if (s & (1 << v)) { continue; }
  //     ll p = ls[v];
  //     FOR(u, 0, n) {
  //       if (s & (1 << u)) { p += bonus[u][v]; }
  //     }
  //     int sv = s | (1 << v);
  //     dp[sv] = max(dp[sv], dp[s] + p);
  //   }
  // }

  // ll res = 0;
  // FOR(s, 0, 1 << n) {
  //   int c = 0;
  //   FOR(v, 0, n) { c += bool(s & (1 << v)); }
  //   if (c == m) {
  //     res = max(res, dp[s]);
  //   }
  // }
  // cout << res << endl;

  // [ With "exactly before" ]
  vector<vector<ll>> dp(1 << n, vector<ll>(n));
  FOR(v, 0, n) {
    dp[(1 << v)][v] = ls[v];
  }
  FOR(s, 0, 1 << n) {
    FOR(v, 0, n) {
      if (!(s & (1 << v))) { continue; }
      FOR(u, 0, n) {
        if (s & (1 << u)) { continue; }
        int su = s | (1 << u);
        dp[su][u] = max(dp[su][u], dp[s][v] + ls[u] + bonus[v][u]);
      }
    }
  }
  dbg2(dp);

  ll res = 0;
  FOR(s, 0, 1 << n) {
    int c = 0;
    FOR(v, 0, n) { c += bool(s & (1 << v)); }
    if (c == m) {
      FOR(v, 0, n) { res = max(res, dp[s][v]); }
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
python misc/run.py codeforces/problemset/580D/main.cpp --check

%%%% begin
7 4 3
2 6 13 5 7 1 9
6 1 15
2 5 3
6 4 8
%%%%
40
%%%% end

%%%% begin
2 2 1
1 1
2 1 1
%%%%
3
%%%% end

%%%% begin
4 3 2
1 2 3 4
2 1 5
3 4 2
%%%%
12
%%%% end
*/
