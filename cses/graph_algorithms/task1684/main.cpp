// AC

// NOTE: 2SAT

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

// DFS out-time sorting (from task1686)
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
  int n_clauses, n_vars; // <= 10^5
  cin >> n_clauses >> n_vars;

  vector<tuple<char, int, char, int>> formula(n_clauses);
  cin >> formula;
  // DD(formula);

  // Construct implication graph
  //   1. Encoding of literals ("XOR 1" for complment)
  //        x,  y, .. => 1, 3, .. (odd)
  //       ¬x, ¬y, .. => 0, 2, .. (even)
  int n = 2 * n_vars;
  vector<vector<int>> adj(n);
  for (auto [c1, x1, c2, x2] : formula) {
    x1--; x2--;
    int v = 2 * x1 + (c1 == '+');
    int u = 2 * x2 + (c2 == '+');
    int vc = v ^ 1; // complement
    int uc = u ^ 1;
    adj[vc].push_back(u);
    adj[uc].push_back(v);
  }
  // DD(adj);

  // Condensation graph
  auto [cg, cg_adj] = makeCondensationDAG(adj);
  // DD(cg);
  // DD(cg_adj);

  // Check satisfiability
  bool sat = 1;
  FOR(x, 0, n_vars) {
    int v = 2 * x;
    int vc = 2 * x + 1;
    if (cg[v] == cg[vc]) {
      sat = 0;
      break;
    }
  }
  if (!sat) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }

  // Assign valuation along toposort
  int ncg = cg_adj.size();
  map<int, vector<int>> cg_map;
  FOR(v, 0, n) { cg_map[cg[v]].push_back(v); }

  vector<int> toposort = dfsOutSort(cg_adj);
  vector<int> valuation(n_vars, -1);
  FOR(i, 0, ncg) {
    int cgid = toposort[i];
    for (auto v : cg_map[cgid]) {
      int x = v / 2;
      int c = v & 1;
      if (valuation[x] == -1) {
        valuation[x] = !c;
      }
    }
  }
  // DD(valuation);

  FOR(i, 0, n_vars) {
    if (i) cout << " ";
    char res = valuation[i] ? '+' : '-';
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
python misc/run.py cses/graph_algorithms/task1684/main.cpp --check

%%%% begin
3 5
+ 1 + 2
- 1 + 3
+ 4 - 2
%%%%
+ - + - +
%%%% end
*/
