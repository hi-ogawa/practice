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
  int n, m;
  cin >> n >> m;
  vector<tuple<int, int>> edges(m, {0, 0});
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  vector<vector<int>> cap(n, vector<int>(n));
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
    cap[x][y] = 1;
  }
  auto cap_orig = cap;

  int v_beg = 0, v_end = n - 1;
  int kInf = 1 << 30;
  vector<int> parent(n);

  // Edmonds-Karp flow search
  auto search = [&]() -> int {
    fill(ALL(parent), -1);
    deque<tuple<int, int>> q;
    q.push_back({v_beg, kInf});
    while (!q.empty()) {
      auto [v, f] = q.front(); q.pop_front();
      if (v == v_end) { return f; }
      for (auto u : adj[v]) {
        if (parent[u] == -1 && cap[v][u] > 0) {
          parent[u] = v;
          q.push_back({u, min(f, cap[v][u])});
        }
      }
    }
    return 0;
  };

  // Update capacity
  auto update = [&](int f) {
    int v = v_end;
    while (v != v_beg) {
      int u = parent[v];
      cap[u][v] -= f;
      cap[v][u] += f;
      v = u;
    }
  };

  // Iterate search/update
  while (int f = search()) { update(f); }
  dbg2(cap);

  // Reconstruct paths from flow DAG
  vector<vector<int>> res;
  auto extendPath = [&](vector<int>& path) {
    while (path.back() != v_end) {
      int v = path.back();
      for (auto u : adj[v]) {
        if (cap_orig[v][u] - cap[v][u] > 0) {
          cap[v][u]++;
          path.push_back(u);
          break;
        }
      }
    }
  };
  for (auto u : adj[v_beg]) {
    int f = cap_orig[v_beg][u] - cap[v_beg][u];
    cap[v_beg][u] += f;
    FOR(i, 0, f) {
      auto& path = res.emplace_back();
      path = {v_beg, u};
      extendPath(path);
    }
  }
  dbg2(res);

  cout << res.size() << endl;
  for (auto path : res) {
    cout << path.size() << endl;
    FOR(i, 0, (int)path.size()) {
      if (i) cout << " ";
      cout << (path[i] + 1);
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
python misc/run.py cses/graph_algorithms/task1711/main.cpp --check

%%%% begin
6 7
1 2
1 3
2 4
2 5
3 4
4 6
5 6
%%%%
2
4
1 2 5 6
4
1 3 4 6
%%%% end

%%%% begin
6 7
1 2
1 3
2 6
3 4
3 5
4 6
5 6
%%%%
2
3
1 2 6
4
1 3 4 6
%%%% end
*/
