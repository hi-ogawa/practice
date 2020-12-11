// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n; // [3, 10^5]
  cin >> n;
  vector<array<int, 2>> edges(n - 1); // tree
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // Temporary use non-leaf root
  int tmp_root = find_if(ALL(adj), [&](auto& x) { return (int)x.size() >= 2; }) - adj.begin();
  assert(tmp_root != n);

  // dp(v) = #{ leaves under subtree(v) }
  vector<int> dp(n);
  function<void(int, int)> dfs = [&](int v, int vp) {
    dp[v] = (int)adj[v].size() == 1;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v);
      dp[v] += dp[u];
    }
  };
  dfs(tmp_root, -1);
  dbg(dp);

  int m = dp[tmp_root]; // number of leaves

  // Find vertex with each branch has at most (m / 2) leaves
  function<int(int, int)> dfs2 = [&](int v, int vp) -> int {
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      if (dp[u] > m / 2) { return dfs2(u, v); }
    }
    return v;
  };
  int root = dfs2(tmp_root, -1);

  // Collect leaves for each branches
  int k = adj[root].size();
  vector<vector<int>> branches(k);

  function<void(int, int, int)> dfs3 = [&](int v, int vp, int i) {
    if ((int)adj[v].size() == 1) {
      branches[i].push_back(v);
    }
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs3(u, v, i);
    }
  };
  FOR(i, 0, k) {
    dfs3(adj[root][i], root, i);
  }
  dbg(branches);

  // Pair two leaves from different branches
  sort(ALL(branches), [](auto& x, auto& y) { return x.size() < y.size(); });
  assert((int)branches.back().size() <= m / 2);
  vector<int> leaves;
  for (auto& xs : branches) {
    for (auto x : xs) {
      leaves.push_back(x);
    }
  }
  vector<array<int, 2>> res;
  FOR(i, 0, m / 2) {
    res.push_back({leaves[i], leaves[i + m / 2]});
  }
  if (m % 2) {
    res.push_back({leaves[0], leaves.back()});
  }
  dbg(res);

  cout << res.size() << "\n";
  for (auto [x, y] : res) {
    x++; y++;
    cout << x << " " << y << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1704/main_v2.cpp

%%%% begin
4
2 1
3 2
4 3
%%%%
%%%% end

%%%% begin
5
1 2
1 3
3 4
3 5
%%%%
2
2 4
4 5
%%%% end
*/
