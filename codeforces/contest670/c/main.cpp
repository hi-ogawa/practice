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
  int n;
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dbg(adj);

  vector<int> parents(n, -1);
  vector<int> sizes(n); // subtree size
  function<void(int)> dfs = [&](int v) {
    sizes[v] = 1;
    for (auto u : adj[v]) {
      if (parents[u] == -1) {
        parents[u] = v;
        dfs(u);
        sizes[v] += sizes[u];
      }
    }
  };
  parents[0] = 0;
  dfs(0);
  dbg(sizes);

  vector<int> cut_sizes(n);
  FOR(v, 0, n) {
    int t = n - sizes[v];
    for (auto u : adj[v]) {
      if (parents[u] == v) {
        t = max(t, sizes[u]);
      }
    }
    cut_sizes[v] = t;
  }
  dbg(cut_sizes);

  int m = *min_element(ALL(cut_sizes));
  vector<int> centroids;
  FOR(i, 0, n) {
    if (cut_sizes[i] == m) {
      centroids.push_back(i);
    }
  }
  dbg(centroids);

  int nc = centroids.size();
  if (nc == 1) {
    cout << edges[0][0] << " " << edges[0][1] << endl;
    cout << edges[0][0] << " " << edges[0][1] << endl;
    return;
  }

  assert(nc == 2);
  int v0 = centroids[0];
  int v1 = centroids[1];

  assert(count(ALL(adj[v0]), v1) == 1);
  assert(n % 2 == 0);
  assert(m == n / 2);

  // Move single leaf from v0 tree to v1
  fill(ALL(parents), -1);
  vector<int> depths(n, -1);
  {
    deque<int> q;
    parents[v0] = v0;
    depths[v0] = 0;
    q.push_back(v0);
    while (!q.empty()) {
      int v = q.front(); q.pop_front();
      for (auto u : adj[v]) {
        if (u == v1) { continue; } // skip v1 subtree
        if (parents[u] == -1) {
          parents[u] = v;
          depths[u] = depths[v] + 1;
          q.push_back(u);
        }
      }
    }
  }
  int v2 = distance(depths.begin(), max_element(ALL(depths)));
  int v3 = parents[v2];
  dbgv(v0, v1, v2, v3);
  cout << (v2 + 1) << " " << (v3 + 1) << endl;
  cout << (v2 + 1) << " " << (v1 + 1) << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest670/c/main.cpp --check

%%%% begin
1
4
1 2
2 3
3 4
%%%%
2 1
2 3
%%%% end

%%%% begin
2
5
1 2
1 3
2 4
2 5
6
1 2
1 3
1 4
2 5
2 6
%%%%
1 2
1 2
1 3
2 3
%%%% end
*/
