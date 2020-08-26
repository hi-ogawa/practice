// AC

// NOTE: Articulation point of undirected connected graph

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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n, m; // 10^5
  cin >> n >> m;
  if (n == 0 && m == 0) { return; }
  if (n == 1) {
    cout << 0 << endl;
    return mainCase();
  }

  vector<array<int, 2>> edges(m, {0});
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y); swap(x, y);
    adj[x].push_back(y);
  }

  vector<int> in_time(n, -1);
  vector<bool> oks(n, 0);
  int t = 0;

  // @returns minimum in_time of DFS subtree
  function<int(int)> dfs = [&](int v) {
    int res = in_time[v] = t++;
    for (auto u : adj[v]) {
      if (in_time[u] >= 0) { // Back edge
        res = min(res, in_time[u]);
        continue;
      }
      int res_u = dfs(u);
      if (in_time[v] <= res_u) { // Found "no-back subgraph"
        // DD(tie(v, u, res_u));
        oks[v] = 1;
      }
      res = min(res, res_u);
    }
    return res;
  };
  // Root gets false-positive in above dfs, so run twice from different roots.
  dfs(0);
  bool ok1 = oks[1];
  fill(ALL(in_time), -1); fill(ALL(oks), 0);
  dfs(1);
  oks[1] = ok1;
  // DD(oks);

  int res = accumulate(ALL(oks), 0);
  cout << res << endl;
  mainCase(); // Next case
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py spoj/SUBMERGE/main.cpp --check

%%%% begin
6 8
1 3
6 1
6 3
4 1
6 4
5 2
3 2
3 5
0 0
%%%%
1
%%%% end

%%%% begin
4 3
1 2
2 3
2 4
0 0
%%%%
1
%%%% end

%%%% begin
3 3
1 2
2 3
1 3
0 0
%%%%
0
%%%% end
*/
