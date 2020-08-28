// AC

// cf. task1694

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
  int n, m; // n <= 500, m <= 1000
  cin >> n >> m;
  vector<tuple<int, int>> edges(m, {0, 0});
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  vector<vector<int>> cap(n, vector<int>(n, 0));
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
    cap[x][y] = cap[y][x] = 1;
  }

  int v_beg = 0, v_end = n - 1;
  vector<int> parent(n);

  auto search = [&]() {
    fill(ALL(parent), -1);
    parent[v_beg] = v_beg;
    deque<int> q;
    q.push_back(v_beg);
    while (!q.empty()) {
      int v = q.front(); q.pop_front();
      if (v == v_end) { break; }
      for (auto u : adj[v]) {
        if (cap[v][u] > 0 && parent[u] == -1) {
          parent[u] = v;
          q.push_back(u);
        }
      }
    }
  };

  auto update = [&]() {
    int flow = -1;
    int v = v_end;
    while (v != v_beg) { // find min capacity along path
      int u = parent[v];
      flow = min((uint)flow, (uint)cap[u][v]);
      v = u;
    }
    v = v_end;
    while (v != v_beg) { // update capacity
      int u = parent[v];
      cap[u][v] -= flow;
      cap[v][u] += flow;
      v = u;
    }
  };

  // Max flow
  while (true) {
    search();
    if (parent[v_end] == -1) { break; }
    update();
  }
  dbg2(cap);
  dbg(parent);

  // Min-cut(A, ¬A) where v ∈ A <=> parent[v] != -1 (i.e. reachable from v_beg)
  vector<tuple<int, int>> res;
  FOR(v, 0, n) {
    for (auto u : adj[v]) {
      if (parent[v] != -1 && parent[u] == -1) {
        res.push_back({v, u});
      }
    }
  }
  dbg(res);

  cout << res.size() << endl;
  for (auto [x, y] : res) {
    cout << (x + 1) << " " << (y + 1) << endl;
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
python misc/run.py cses/graph_algorithms/task1695/main.cpp --check

%%%% begin
4 5
1 2
1 3
2 3
3 4
1 4
%%%%
2
3 4
1 4
%%%% end
*/
