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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, m; // [1, 3 x 10^5]
  cin >> n >> m;
  vector<array<int, 2>> edges(m); // connected
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  //
  // PROP.
  //   Valid \iff No bridge in the graph
  //

  //
  // PROP.
  //   If no bridge in the graph, then its DFS tree satisfies:
  //     Each tree edge has corresponding back edge from some descendent to some ancestor.
  //
  // N.B.
  //   Thus it suffices to
  //     1. check if there's a bridge
  //     2. assign directions based on tree/back edge,
  //

  // DFS tree
  vector<int> in_times(n, -1);
  vector<int> dp(n);
  int time = 0;
  set<array<int, 2>> bridges;
  set<array<int, 2>> tree_edges;
  set<array<int, 2>> back_edges;
  function<void(int, int)> dfs = [&](int v, int vp) {
    dp[v] = in_times[v] = time++;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      if (in_times[u] != -1 && in_times[u] < in_times[v]) {
        back_edges.insert({v, u});
      }
      if (in_times[u] == -1) {
        tree_edges.insert({v, u});
        dfs(u, v);
        if (in_times[v] < dp[u]) {
          bridges.insert({v, u});
        }
      }
      dp[v] = min(dp[v], dp[u]);
    }
  };
  dfs(0, 0);
  dbg(dp);
  dbg(in_times);
  dbg(bridges);
  dbg(tree_edges);
  dbg(back_edges);
  assert(tree_edges.size() + back_edges.size() == m);

  if (!bridges.empty()) { cout << 0 << "\n"; return; }

  for (auto [x, y] : tree_edges) {
    x++; y++;
    cout << x << " " << y << "\n";
  }
  for (auto [x, y] : back_edges) {
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
python misc/run.py codeforces/problemset/118E/main.cpp

%%%% begin
5 9
5 4
2 1
3 4
4 1
5 2
2 3
4 2
3 1
5 1
%%%%
%%%% end

%%%% begin
6 8
1 2
2 3
1 3
4 5
4 6
5 6
2 4
3 5
%%%%
1 2
2 3
3 1
4 5
5 6
6 4
4 2
3 5
%%%% end

%%%% begin
6 7
1 2
2 3
1 3
4 5
4 6
5 6
2 4
%%%%
0
%%%% end
*/
