// WIP

// Cf. task1751 condensation graph (forest) construction
// TODO: make condensation graph without full-fledged algorithm (probably single dfs should suffice)

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
#define DD(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define DD2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define DDX(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// cf. task1684
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
  return order;
}

// Cf task1686
tuple<vector<int>, vector<vector<int>>> makeCondensationDAG(const vector<vector<int>>& adj) {
  int n = adj.size();
  vector<vector<int>> adjT(n);
  FOR(v, 0, n) {
    for (auto u : adj[v]) {
      adjT[u].push_back(v);
    }
  }
  vector<int> order = dfsOutSort(adj);
  vector<int> cg(n, -1);
  vector<vector<int>> cg_adj;
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
  for (auto& vs: cg_adj) {
    sort(ALL(vs));
    vs.erase(unique(ALL(vs)), vs.end());
  }
  return {cg, cg_adj};
}


// Main
void mainCase() {
  int n, nq; // <= 10^6
  cin >> n >> nq;
  vector<int> edges(n, 0);
  cin >> edges;
  for (auto& x : edges) { x--; }
  vector<array<int, 2>> qs(nq, {0, 0});
  cin >> qs;
  for (auto& [x, y] : qs) { x--; y--; }

  //
  // Make condensationg graph (forest)
  //
  vector<vector<int>> adj(n);
  FOR(i, 0, n) { adj[i].push_back(edges[i]); }
  DD(adj);

  vector<int> cg;
  vector<vector<int>> cg_adj;
  tie(cg, cg_adj) = makeCondensationDAG(adj);
  DD(cg);
  DD(cg_adj);

  map<int, int> cg_sizes; // size of each component
  FOR(i, 0, n) { cg_sizes[cg[i]]++; }
  DD(cg_sizes);

  int n_cg = cg_sizes.size(); // number of components
  DD(n_cg);

  vector<int> cg_depths(n_cg, -1);
  {
    function<int(int)> dfs = [&](int v) -> int {
      if (cg_depths[v] != -1) { return cg_depths[v]; }
      if (cg_adj[v][0] == v) { return cg_depths[v] = 0; } // v is root <=> cg_adj[v] = {v}
      return cg_depths[v] = dfs(cg_adj[v][0]) + 1;
    };
    FOR(v, 0, n_cg) {
      if (cg_depths[v] == -1) { dfs(v); }
    }
    DD(cg_depths);
  }

  map<int, vector<int>> compos;
  FOR(v, 0, n) {
    compos[cg[v]].push_back(v);
  }
  DD(compos);

  vector<int> loop_id(n, -1); // loop component position modulo
  FOR(v_cg, 0, n_cg) {
    if (cg_depths[v_cg] > 0) { continue; }
    int v0 = compos[v_cg][0];
    int v = v0;
    do {
      loop_id[edges[v]] = loop_id[v] + 1;
      v = edges[v];
    } while (v != v0);
  }
  DD(loop_id);

  //
  // Binary lifting table (for original graph)
  //
  int b_lim = 0; // n < 2^b
  while ((1 << b_lim) <= n) { b_lim++; }
  vector<vector<int>> table(b_lim, vector<int>(n, 0));
  table[0] = edges;
  FOR(b, 1, b_lim) {
    FOR(v, 0, n) {
      table[b][v] = table[b - 1][table[b - 1][v]];
    }
  }
  DD2(table);

  auto lift = [&](int v, int e) -> int {
    int b = 0;
    while (e > 0) {
      if (e & 1) { v = table[b][v]; }
      e >>= 1; b++;
    }
    return v;
  };

  // Answer queries
  for (auto [u, v] : qs) {
    DDX(u, v);
    int du = cg_depths[cg[u]];
    int dv = cg_depths[cg[v]];

    // depth[u] < depth[v] (unreachable)
    if (du < dv) {
      cout << -1 << endl;
      continue;
    }

    // depth[u] >= depth[v] = 0
    if (dv == 0) {
      int res = du;
      u = lift(u, res);
      if (cg[u] != cg[v]) {
        cout << -1 << endl;
        continue;
      }
      int mo = cg_sizes[cg[u]];
      DDX(u, v, res);
      res += (loop_id[v] - loop_id[u] + mo) % mo;
      cout << res << endl;
      continue;
    }

    // depth[u] >= depth[v] > 0
    {
      int res = du - dv;
      u = lift(u, res);
      cout << (u == v ? res : -1) << endl;
      continue;
    }
  }
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
python misc/run.py cses/graph_algorithms/task1160/main.cpp --check

%%%% begin
5 1
5 5 1 2 3
4 1
%%%%
4
%%%% end

%%%% begin
5 3
2 3 2 3 2
1 2
1 3
1 4
%%%%
1
2
-1
%%%% end
*/
