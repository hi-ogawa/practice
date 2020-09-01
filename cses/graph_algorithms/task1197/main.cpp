// AC

// Cf. task1973

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
  ll n, m; // n <= 2500, m <= 5000
  cin >> n >> m;

  vector<array<ll, 3>> edges(m, {0, 0, 0});
  cin >> edges;
  for (auto& [x, y, c] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y, _c] : edges) { adj[x].push_back(y); }

  // Find roots not reachable each other
  vector<int> roots;
  {
    vector<bool> done(n, 0);
    auto bfs = [&](int v0) {
      deque<int> q;
      q.push_back(v0);
      done[v0] = 1;
      while (!q.empty()) {
        int v = q.front(); q.pop_front();
        for (auto u : adj[v]) {
          if (!done[u]) {
            done[u] = 1;
            q.push_back(u);
          }
        }
      }
    };
    FOR(v, 0, n) {
      if (!done[v]) {
        roots.push_back(v);
        bfs(v);
      }
    }
  }
  dbg(roots);

  // Find negative cycle via Bellman-Ford (TODO: prove "parents" always leads to negative cycle)
  auto solve = [&](int v_root, vector<int>& res) -> bool {
    ll kInf = 1L << 60;
    vector<ll> dists(n, kInf);
    vector<int> parents(n, -1);
    dists[v_root] = 0;
    int v_neg = -1;
    FOR(i, 0, n) {
      bool found = 0;
      for (auto [x, y, c] : edges) {
        ll d = dists[x] + c;
        if (d < dists[y]) {
          dists[y] = d;
          parents[y] = x;
          found = 1;
          if (i == n - 1) { v_neg = y; }
        }
      }
      if (!found) { return 0; }
    }

    // Backtrack from v_neg
    vector<bool> visited(n, 0);
    int v = v_neg;
    while (!visited[v]) {
      visited[v] = 1;
      res.push_back(v);
      v = parents[v];
    }
    res.erase(res.begin(), find(ALL(res), v));
    res.push_back(v);
    reverse(ALL(res));
    return 1;
  };

  bool ok = 0;
  vector<int> res;
  for (auto v : roots) {
    if (ok = solve(v, res)) { break; }
  }

  if (!ok) {
    cout << "NO" << endl; return;
  }

  cout << "YES" << endl;
  FOR(i, 0, (int)res.size()) {
    if (i) cout << " ";
    cout << (res[i] + 1);
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
python misc/run.py cses/graph_algorithms/task1197/main.cpp --check

%%%% begin
2 1
1 1 0
2 1 3
2 2 -1
3 4 3
4 2 6
%%%%
NO
%%%% end

%%%% begin
4 5
1 2 1
2 4 1
3 1 1
4 1 -3
4 3 -2
%%%%
YES
1 2 4 1
%%%% end
*/
