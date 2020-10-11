// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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

// Main
void mainCase() {
  int n; // [2, 2 x 10^5]
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // 1st pass from arbitrary root
  vector<ll> dp(n);
  vector<int> sizes(n);
  function<void(int, int)> dfs = [&](int v, int vp) {
    sizes[v] = 1;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v);
      sizes[v] += sizes[u];
      dp[v] += dp[u];
    }
    dp[v] += sizes[v];
  };
  dfs(0, 0);
  dbg(dp);

  // 2nd pass for re-rooting
  vector<ll> dp2(n);
  function<void(int, int)> dfs2 = [&](int v, int vp) {
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      // (1st pick) + (go-down) + (go-up)
      dp2[u] = n + (dp[u] - sizes[u]) + (dp2[v] - n - dp[u] + n - sizes[u]);
      dfs2(u, v);
    }
  };
  dp2[0] = dp[0];
  dfs2(0, 0);
  dbg(dp2);

  // Find optimum
  ll res = *max_element(ALL(dp2));
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1187E/main.cpp

%%%% begin
9
1 2
2 3
2 5
2 6
1 4
4 9
9 7
9 8
%%%%
36
%%%% end

%%%% begin
5
1 2
1 3
2 4
2 5
%%%%
14
%%%% end
*/
