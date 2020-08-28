// WIP

// NOTE: "Scaling algorithm" instead of Edmonds-Karp

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
  vector<tuple<int, int, ll>> edges(m, {0, 0, 0}); // capacity <= 10^9
  cin >> edges;
  for (auto& [x, y, _c] : edges) { x--; y--; }
  dbg(edges);

  vector<vector<int>> adj(n);
  vector<vector<ll>> cap(n, vector<ll>(n, 0)); // Modified by "update"
  ll flow_bound = 0;
  for (auto& [x, y, c] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
    cap[x][y] += c; // Handle duplicated edge
    flow_bound = max(flow_bound, cap[x][y]);
  }
  dbg(adj);
  dbg2(cap);
  auto cap_orig = cap;

  int v_beg = 0, v_end = n - 1;
  vector<int> parent(n); // Modified by "search"

  // Find
  auto search = [&]() -> bool {
    fill(ALL(parent), -1);
    parent[v_beg] = v_beg;
    deque<int> q;
    q.push_back(v_beg);
    while (!q.empty()) {
      int v = q.front(); q.pop_front();
      if (v == v_end) { break; }
      for (auto u : adj[v]) {
        if (cap[v][u] >= flow_bound && parent[u] == -1) {
          parent[u] = v;
          q.push_back(u);
        }
      }
    }
    return parent[v_end] != -1;
  };

  // Update capacity based on found path
  auto update = [&]() -> bool {
    // Find saturation value
    ll flow = -1;
    {
      int v = v_end;
      while (v != v_beg) {
        int u = parent[v];
        flow = min((ull)flow, (ull)cap[u][v]);
        v = u;
      }
    }

    // Update capacity
    {
      int v = v_end;
      while (v != v_beg) {
        int u = parent[v];
        cap[u][v] -= flow;
        cap[v][u] += flow;
        v = u;
      }
    }
    return 1;
  };

  // Loop search and update
  while (flow_bound > 0) {
    if (!search()) {
      flow_bound /= 2;
      continue;
    }
    update();
  }

  ll res = 0;
  FOR(v, 0, n) {
    res += cap_orig[v_beg][v] - cap[v_beg][v];
  }
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
python misc/run.py cses/graph_algorithms/task1694/main_v2.cpp --check

%%%% begin
4 5
1 2 3
2 4 2
1 3 4
3 4 5
4 1 3
%%%%
6
%%%% end
*/
