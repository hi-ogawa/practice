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
  int n, m; // n \in [1, 5000]
  cin >> n >> m;
  array<int, 3> ns;
  cin >> ns;
  vector<array<int, 2>> edges(m);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // Find bipartite connected components
  vector<int> bips(n); // "+c" or "-c" where "c" indicates component
  bool ok_bip = 1;
  function<void(int)> dfs = [&](int v) {
    for (auto u : adj[v]) {
      if (bips[u] == 0) {
        bips[u] = -1 * bips[v];
        dfs(u);
        continue;
      }
      assert(bips[u] == bips[v] || bips[u] == -bips[v]);
      if (bips[u] == bips[v]) { ok_bip = 0; break; }
    }
  };
  int bip_id = 1;
  FOR(v, 0, n) {
    if (bips[v] == 0) {
      bips[v] = bip_id++;
      dfs(v);
    }
  }
  dbgv(ok_bip, bips);
  if (!ok_bip) { cout << "NO" << endl; return; }

  // Bipartite component sizes
  vector<array<int, 2>> cnts(bip_id);
  FOR(v, 0, n) {
    int b = bips[v];
    cnts[abs(b)][b < 0]++;
  }
  dbg(cnts);

  // DP for possible sums
  vector<vector<bool>> dp(bip_id, vector<bool>(n + 1));
  dp[0][0] = 1;
  FOR(i, 1, bip_id) {
    auto [c0, c1] = cnts[i];
    FOR(j, 0, n + 1) {
      bool t = 0;
      if (j - c0 >= 0) { t = t || dp[i - 1][j - c0]; }
      if (j - c1 >= 0) { t = t || dp[i - 1][j - c1]; }
      dp[i][j] = t;
    }
  }
  dbg2(dp);
  if (!dp[bip_id - 1][ns[1]]) { cout << "NO" << endl; return; }

  // Backtrack DP to realize dp[ns[1]]
  set<int> choices; // "+c" or "-c"
  int j = ns[1];
  for (int i = bip_id - 1; i >= 1; i--) {
    auto [c0, c1] = cnts[i];
    if (j - c0 >= 0 && dp[i - 1][j - c0]) {
      choices.insert(i);
      j = j - c0; continue;
    }
    if (j - c1 >= 0 && dp[i - 1][j - c1]) {
      choices.insert(- i);
      j = j - c1; continue;
    }
    assert(0);
  }
  dbg(choices);

  // Assign colors
  vector<int> res(n, -1);
  int cnt0 = 0;
  FOR(v, 0, n) {
    if (choices.count(bips[v])) {
      // 1
      res[v] = 1;
    } else {
      // 0/2 (split so that ns[0] and ns[2])
      res[v] = (cnt0++ < ns[0]) ? 0 : 2;
    }
  }
  dbg(res);

  cout << "YES" << endl;
  for (auto x : res) { cout << (x + 1); }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu87/e/main.cpp --check

%%%% begin
6 3
2 2 2
3 1
5 4
2 5
%%%%
YES
112323
%%%% end

%%%% begin
5 9
0 2 3
1 2
1 3
1 5
2 3
2 4
2 5
3 4
3 5
4 5
%%%%
NO
%%%% end
*/
