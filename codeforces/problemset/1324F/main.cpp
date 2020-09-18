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
  int n;
  cin >> n;
  vector<int> ls(n);
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // dp[v] = max point of "0-rooted" subtree(v)
  vector<int> dp(n);
  function<void(int, int)> dfs = [&](int v, int parent) {
    dp[v] = ls[v] ? 1 : -1;
    for (auto u : adj[v]) {
      if (u == parent) { continue; }
      dfs(u, v);
      if (dp[u] > 0) {
        dp[v] += dp[u];
      }
    }
  };
  dfs(0, 0);
  dbg(dp);

  // dp2[v] = max point of subtree(v)
  vector<int> dp2(n);
  function<void(int, int)> dfs2 = [&](int v, int parent) {
    for (auto u : adj[v]) {
      if (u == parent) { continue; }
      if (dp[u] == -1) {
        dp2[u] = max(-1, dp2[v] - 1);
      } else {
        dp2[u] = max(dp[u], dp2[v]);
      }
      dfs2(u, v);
    }
  };
  dp2[0] = dp[0];
  dfs2(0, 0);
  dbg(dp2);

  FOR(i, 0, n) {
    cout << dp2[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
  return 0;
}

/*
python misc/run.py codeforces/problemset/1324F/main.cpp --check

%%%% begin
9
0 1 1 1 0 0 0 0 1
1 2
1 3
3 4
3 5
2 6
4 7
6 8
5 9
%%%%
2 2 2 2 2 1 1 0 2
%%%% end

%%%% begin
4
0 0 1 0
1 2
1 3
1 4
%%%%
0 -1 1 -1
%%%% end
*/
