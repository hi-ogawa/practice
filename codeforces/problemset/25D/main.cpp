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

struct Dsu {
  vector<int> data_;
  Dsu(int n) { data_.resize(n); iota(ALL(data_), 0); }
  void merge(int dst, int src) { data_[find(src)] = find(dst); }
  int find(int a) {
    if (a == data_[a]) { return a; }
    return data_[a] = find(data_[a]);
  }
};

// Main
void mainCase() {
  int n; // [2, 1000]
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  Dsu dsu(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
    dsu.merge(x, y);
  }

  // Find connected components
  map<int, vector<int>> compos;
  FOR(i, 0, n) { compos[dsu.find(i)].push_back(i); }
  dbg(compos);

  // Collect back edges
  vector<array<int, 2>> back_edges;
  vector<int> parents(n, -1);
  auto bfs = [&](int v0) -> bool {
    bool is_tree = 1;
    deque<int> q;
    parents[v0] = v0;
    q.push_back(v0);
    while (!q.empty()) {
      int v = q.front(); q.pop_front();
      for (auto u : adj[v]) {
        if (parents[u] == u) { continue; } // root
        if (parents[v] == u) { continue; } // parent edge
        if (parents[u] == -1) { // tree edge
          parents[u] = v;
          q.push_back(u);
          continue;
        }
        // back edge
        is_tree = 0;
        if (v < u) { back_edges.push_back({v, u}); }
      }
    }
    return is_tree;
  };

  // PROP. At least one component is tree
  int root = -1;
  for (auto& [u, _vs] : compos) {
    if (bfs(u)) { root = u; }
  }
  dbg(root);
  dbg(back_edges);
  assert(root != -1);
  assert(compos.size() == back_edges.size() + 1);

  // Connect component to tree instead of back edge
  vector<array<int, 4>> res;
  for (auto [u, _vs] : compos) {
    if (u == root) { continue; }
    auto [x, y] = back_edges.back(); back_edges.pop_back();
    res.push_back({x, y, u, root});
  }
  dbg(res);

  cout << res.size() << endl;
  FOR(i, 0, (int)res.size()) {
    FOR(j, 0, 4) {
      if (j) cout << " ";
      cout << (res[i][j] + 1);
    }
    cout << endl;
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
python misc/run.py codeforces/problemset/25D/main.cpp --check

%%%% begin
2
1 2
%%%%
0
%%%% end

%%%% begin
7
1 2
2 3
3 1
4 5
5 6
6 7
%%%%
1
3 1 3 7
%%%% end
*/
