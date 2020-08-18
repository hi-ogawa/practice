// AC

// NOTE: topological order DP on condensation DAG

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

// DFS out-time sorting
vector<int> dfsOutSort(const vector<vector<int>>& adj) {
  int n = adj.size();
  vector<int> in_time(n, -1);
  vector<int> out_time(n, -1);
  int t = 0;
  function<void(int)> dfs = [&](int v) {
    in_time[v] = t++;
    for (auto u : adj[v]) {
      if (in_time[u] == -1) { dfs(u); }
    }
    out_time[v] = t++;
  };
  FOR(v, 0, n) {
    if (in_time[v] == -1) { dfs(v); }
  }
  vector<int> order(n, 0);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return out_time[x] > out_time[y]; });
  // DD(out_time);
  // DD(order);
  return order;
}

// Main
void mainCase() {
  int n, m; // <= 10^6
  cin >> n >> m;

  vector<ll> ls(n, 0);
  cin >> ls;

  vector<tuple<int, int>> edges(m, {0, 0});
  cin >> edges;

  vector<vector<int>> adj(n);
  vector<vector<int>> adjT(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adjT[y].push_back(x);
  }

  // Condensation DAG
  vector<int> cg(n, -1);
  vector<vector<int>> cg_adj;
  {
    vector<int> order = dfsOutSort(adj);
    int cgid = 0;
    function<void(int)> cgDfs = [&](int v) {
      cg[v] = cgid;
      for (auto u : adjT[v]) {
        int cgu = cg[u];
        if (cgu == -1) { cgDfs(u); continue; }
        cg_adj[cgu].push_back(cgid);
      }
    };
    FOR(i, 0, n) {
      int v = order[i];
      if (cg[v] == -1) {
        cg_adj.emplace_back();
        cgDfs(v);
        cgid++;
      }
    }
    for (auto& vs : cg_adj) {
      sort(ALL(vs));
      vs.erase(unique(ALL(vs)), vs.end());
    }
    // DD(cg);
    // DD(cg_adj);
  }

  // Gain of each component
  int ncg = cg_adj.size();
  vector<ll> ps(ncg, 0);
  FOR(i, 0, n) {
    ps[cg[i]] += ls[i];
  }
  // DD(ps);

  // Toposort DP
  vector<int> toposort = dfsOutSort(cg_adj);
  // DD(toposort);

  vector<vector<int>> cg_adjT(ncg);
  FOR(v, 0, ncg) {
    for (auto u : cg_adj[v]) {
      cg_adjT[u].push_back(v);
    }
  }

  vector<ll> dp(ncg, 0);
  FOR(i, 0, ncg) {
    int v = toposort[i];
    ll tmp = 0;
    for (auto u : cg_adjT[v]) {
      tmp = max(tmp, dp[u]);
    }
    dp[v] = tmp + ps[v];
  }
  // DD(dp);

  ll res = *max_element(ALL(dp));
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py cses/graph_algorithms/task1686/main.cpp --check

%%%% begin
2 1
250789096 1
1 2
%%%%
250789097
%%%% end

%%%% begin
4 4
4 5 2 7
1 2
2 1
1 3
2 4
%%%%
16
%%%% end
*/
