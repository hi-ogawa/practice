// AC

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
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n, m, v0;
  cin >> n >> m >> v0;
  vector<array<int, 2>> edges(m);
  cin >> edges;
  v0--;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n), adjT(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adjT[y].push_back(x);
  }

  // Make condense DAG (possible disconnected)
  vector<int> cgs(n, -1); // id of component after condensed
  vector<vector<int>> cg_adj;
  int n_cg = 0;
  {
    // DFS for "out time" ordering
    //
    // PROP.
    //   v1 reachable to v2       \implies  out_time[v1] > out_time[v2]
    //   v2 not reachable to v1
    //
    vector<bool> done(n);
    vector<int> out_time(n, -1);
    int t = 0;
    function<void(int, int)> dfs = [&](int v, int vp) {
      done[v] = 1;
      for (auto u : adj[v]) {
        if (u == vp) { continue; }
        if (done[u]) { continue; }
        dfs(u, v);
      }
      out_time[v] = t++;
    };
    FOR(v, 0, n) {
      if (out_time[v] == -1) {
        dfs(v, v);
      }
    }
    vector<int> order(n);
    iota(ALL(order), 0);
    sort(ALL(order), [&](auto x, auto y) { return out_time[x] > out_time[y]; });

    // Transpose DFS
    function<void(int, int)> dfs2 = [&](int v, int vp) {
      for (auto u : adjT[v]) {
        if (u == vp) { continue; }
        if (cgs[u] != -1) {
          if (cgs[u] != cgs[v]) {
            cg_adj[cgs[u]].push_back(cgs[v]);
          }
          continue;
        }
        cgs[u] = cgs[v];
        dfs2(u, v);
      }
    };
    FOR(i, 0, n) {
      int v = order[i];
      if (cgs[v] == -1) {
        cgs[v] = n_cg++;
        cg_adj.resize(n_cg);
        dfs2(v, v);
      }
    }
  }
  dbgv(n_cg, cgs);

  // Count DAG transposed leaves
  vector<vector<int>> cg_adjT(n_cg);
  FOR(v, 0, n_cg) {
    for (auto u : cg_adj[v]) {
      cg_adjT[u].push_back(v);
    }
  }

  int res = 0;
  FOR(v, 0, n_cg) {
    if (v == cgs[v0]) { continue; }
    dbgv(v, cg_adjT[v]);
    res += cg_adjT[v].size() == 0;
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/999E/main.cpp --check


%%%% begin
9 9 1
1 2
1 3
2 3
1 5
5 6
6 1
1 8
9 8
7 1
%%%%
3
%%%% end

%%%% begin
5 4 5
1 2
2 3
3 4
4 1
%%%%
1
%%%% end
*/
