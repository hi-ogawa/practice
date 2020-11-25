// CONTEST, AC

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
  int n; // [3, 2 x 10^5]
  cin >> n;
  vector<array<int, 2>> edges(n); // connected, no multiple edge
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS
  // - Look for unique back edge
  // - Subtree size, etc...
  vector<int> done(n), sizes(n), depths(n), parents(n);
  array<int, 2> back_edge = {-1, -1};
  function<void(int, int)> dfs = [&](int v, int vp) {
    done[v] = 1;
    sizes[v] = 1;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      if (done[u]) {
        if (back_edge[0] == -1) { back_edge = {v, u}; }
        continue;
      }
      depths[u] = depths[v] + 1;
      parents[u] = v;
      dfs(u, v);
      sizes[v] += sizes[u];
    }
  };
  dfs(0, 0);
  assert(back_edge[0] != -1);
  dbg(sizes, depths);

  //
  // Count path
  //
  auto binom2 = [&](ll x) -> ll { return (x * (x - 1)) / 2; };

  // Starting from two for all pairs
  ll res = 2 * binom2(n);

  // Then, subtract bad pairs
  auto [v0, v1] = back_edge;
  int v = v0;
  res -= binom2(sizes[v]);
  FOR(_, 0, depths[v0] - depths[v1] - 1) {
    int vp = parents[v];
    res -= binom2(sizes[vp] - sizes[v]);
    v = vp;
  }
  res -= binom2(n - sizes[v]);

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1454/e/main.cpp

%%%% begin
3
3
1 2
2 3
1 3
4
1 2
2 3
3 4
4 2
5
1 2
2 3
1 3
2 5
4 3
%%%%
6
11
18
%%%% end
*/
