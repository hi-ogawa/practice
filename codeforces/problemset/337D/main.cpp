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
  int n, m, d;
  cin >> n >> m >> d;
  vector<int> ls(m);
  vector<array<int, 2>> edges(n - 1);
  cin >> ls >> edges;
  for (auto& x : ls) { x--; }
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  vector<int> is_bad(n);
  for (auto x : ls) { is_bad[x] = 1; }

  // bad distance for subtrees (NOTE: priority queue with bounded size = 2 would suffices)
  vector<multiset<pair<int, int>>> dp(n); // dp[v] = {(u, d), ...}
  const int kInf = 1e6;

  // 1st pass for global root(0) subtree
  function<void(int, int)> dfs = [&](int v, int vp) {
    dp[v].insert({is_bad[v] ? 0 : -kInf, v});
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v);
      dp[v].insert({dp[u].rbegin()->first + 1, u});
    }
  };
  dfs(0, 0);
  dbg2(dp);

  // 2nd pass for re-rooting
  function<void(int, int)> dfs2 = [&](int v, int vp) {
    if (v != vp) {
      auto [x, vpu] = *dp[vp].rbegin();
      if (v == vpu) {
        tie(x, vpu) = *next(dp[vp].rbegin());
      }
      dp[v].insert({x + 1, vpu});
    }
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs2(u, v);
    }
  };
  dfs2(0, 0);
  dbg2(dp);

  // Count #{ v | max_{u : bad} d(v, u) <= d }
  int res = 0;
  FOR(v, 0, n) {
    res += (dp[v].rbegin()->first <= d);
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/337D/main.cpp --check

%%%% begin
6 2 3
1 2
1 5
2 3
3 4
4 5
5 6
%%%%
3
%%%% end
*/
