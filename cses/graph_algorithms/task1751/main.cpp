// AC

// Cf. task1682 for condensation graph

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
  int n; // <= 10^6
  cin >> n;

  vector<int> edges(n, 0);
  cin >> edges;
  for (auto& x : edges) { x--; }

  vector<vector<int>> adjT(n);
  FOR(i, 0, n) { adjT[edges[i]].push_back(i); }

  //
  // PROP.
  //   1. Condensation graph is (transposed) forest
  //   2. Pre-period is the depth
  //   3. Period is the size of the root component
  //

  // DFS for topological sort
  vector<int> topsort(n, 0);
  {
    vector<int> in_time(n, -1), out_time(n, -1);
    int t = 0;
    function<void(int)> dfs = [&](int v) {
      in_time[v] = t++;
      int u = edges[v];
      if (in_time[u] == -1) { dfs(u); }
      out_time[v] = t++;
    };
    FOR(v, 0, n) {
      if (in_time[v] == -1) { dfs(v); }
    }
    iota(ALL(topsort), 0);
    sort(ALL(topsort), [&](auto x, auto y) { return out_time[x] > out_time[y]; });
  }
  // DD(topsort);

  // Transpose DFS for condensation graph
  vector<int> cg(n, -1);
  vector<set<int>> cg_adjT;
  int cgid = 0;
  function<void(int)> dfsT = [&](int v) {
    cg[v] = cgid;
    for (auto u : adjT[v]) {
      int other = cg[u];
      if (other != -1) {
        cg_adjT[cgid].insert(other);
        continue;
      }
      dfsT(u);
    }
  };
  FOR(i, 0, n) {
    int v = topsort[i];
    if (cg[v] == -1) {
      cg_adjT.push_back({});
      dfsT(v);
      cgid++;
    }
  }
  // DD(cg);
  // DD(cg_adjT);

  // Size of each component
  map<int, int> cg_sizes;
  FOR(i, 0, n) { cg_sizes[cg[i]]++; }
  int n_cg = cg_sizes.size(); // number of components
  // DD(cg_sizes);

  // BFS for depth in condensation graph (transposed forest)
  vector<int> cg_depths(n_cg, -1);
  vector<int> cg_roots(n_cg, -1);
  deque<int> queue;
  FOR(v, 0, n_cg) {
    if (cg_adjT[v].count(v)) { // Root component iff self loop
      cg_depths[v] = 0;
      cg_roots[v] = v;
      queue.push_back(v);
    }
  }
  while (!queue.empty()) {
    auto v = queue.front(); queue.pop_front();
    for (auto u : cg_adjT[v]) {
      if (cg_depths[u] != -1) { continue; }
      cg_depths[u] = cg_depths[v] + 1;
      cg_roots[u] = cg_roots[v];
      queue.push_back(u);
    }
  }
  // DD(cg_depths);
  // DD(cg_roots);

  // Answer f(v) = depth(c(v)) + size(root(c(v)))
  FOR(v, 0, n) {
    int c = cg[v];
    int r = cg_roots[c];
    ll res = cg_depths[c] + cg_sizes[r];
    if (v) cout << " ";
    cout << res;
  }
  cout << endl;
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
python misc/run.py cses/graph_algorithms/task1751/main.cpp --check

%%%% begin
5
2 4 3 1 4
%%%%
3 3 1 3 4
%%%% end
*/
