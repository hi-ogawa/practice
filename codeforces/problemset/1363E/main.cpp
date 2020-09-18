// WA

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
  int n; // < 10^6
  cin >> n;
  vector<array<ll, 3>> ls(n);
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // dp[v][0] = #cost to fix subtree(v) without paying a[v]
  // dp[v][1] = #cost to fix subtree(v) with paying a[v]
  using data_t = pair<ll, array<array<int, 2>, 2>>; // (cost, 0/0, 0/1, 1/0, 1/1)
  vector<array<data_t, 2>> dp(n);
  function<void(int, int)> dfs = [&](int v, int parent) {
    dp[v][0].second[ls[v][1]][ls[v][2]]++;
    for (auto u : adj[v]) {
      if (u == parent) { continue; }
      dfs(u, v);
      // Let child pay when it's cheaper (TODO: ancestor should decide it, not parent (cf. main_v2.cpp))
      bool cheap = ls[u][0] < ls[v][0];
      dp[v][0].first += dp[u][cheap].first;
      for (auto b : {0, 1}) {
        for (auto c : {0, 1}) {
          dp[v][0].second[b][c] += dp[u][cheap].second[b][c];
        }
      }
    }
    // Fix as much as possible
    dp[v][1] = dp[v][0];
    int cnt01 = dp[v][1].second[0][1];
    int cnt10 = dp[v][1].second[1][0];
    int k = min(cnt01, cnt10);
    dp[v][1].second[0][0] += k;
    dp[v][1].second[0][1] -= k;
    dp[v][1].second[1][0] -= k;
    dp[v][1].second[1][1] += k;
    dp[v][1].first += 2 * k * ls[v][0];
  };
  dfs(0, 0);
  dbg2(dp);

  // Check 0/1 balance is correct
  bool ok = dp[0][1].second[0][1] == 0 && dp[0][1].second[1][0] == 0;
  if (!ok) { cout << -1 << endl; return; }

  ll res = dp[0][1].first;
  if (dp[0][0].second[0][1] == 0 && dp[0][0].second[1][0] == 0) {
    res = min(res, dp[0][0].first);
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1363E/main.cpp --check

%%%% begin
5
1 0 1
20 1 0
300 0 1
4000 0 0
50000 1 0
1 2
2 3
2 4
1 5
%%%%
4
%%%% end

%%%% begin
5
10000 0 1
2000 1 0
300 0 1
40 0 0
1 1 0
1 2
2 3
2 4
1 5
%%%%
24000
%%%% end

%%%% begin
2
109 0 1
205 0 1
1 2
%%%%
-1
%%%% end
*/
