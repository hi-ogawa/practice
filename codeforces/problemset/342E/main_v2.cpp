// AFTER EDITORIAL, WIP

// NOTE: Get distance using centroid decomposition (cf. https://codeforces.com/blog/entry/81661?#comment-686024)

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

struct CentroidDecomposition {
  int n;
  const vector<vector<int>>& adj;
  vector<int> parents;
  vector<int> sizes;
  vector<int> depths;
  vector<vector<int>> dists;

  CentroidDecomposition(const vector<vector<int>>& adj) : adj{adj} {
    n = adj.size();
    parents.assign(n, -1);
    sizes.assign(n, 0);
    depths.assign(n, 0);
    dists.assign(31 - __builtin_clz(n), vector<int>(n));

    function<void(int, int, int, int)> dfs = [&](int v, int vp, int depth, int dist) {
      sizes[v] = 1;
      if (depth != -1) { dists[depth][v] = dist; }
      for (auto u : adj[v]) {
        if (u == vp || parents[u] != -1) { continue; }
        dfs(u, v, depth, dist + 1);
        sizes[v] += sizes[u];
      }
    };

    auto findCentroid = [&](int root) -> int {
      int v = root, vp = root;
      bool done = 0;
      while (!done) {
        done = 1;
        for (auto u : adj[v]) {
          if (u == vp || parents[u] != -1) { continue; }
          if (sizes[u] <= sizes[root] / 2) { continue; }
          vp = v; v = u;
          done = 0;
          break;
        }
      }
      return v;
    };

    function<void(int, int, bool)> decompose = [&](int child, int parent, bool init) {
      dfs(child, child, (init ? -1 : depths[parent]), 1);
      int centroid = findCentroid(child);
      parents[centroid] = init ? centroid : parent;
      depths[centroid] = init ? 0 : (depths[parent] + 1);
      for (auto v : adj[centroid]) {
        if (parents[v] == -1) {
          decompose(v, centroid, 0);
        }
      }
    };

    decompose(0, 0, 1);
  }

  int getLCA(int x, int y) {
    int dx = depths[x], dy = depths[y];
    if (dx > dy) { swap(x, y); swap(dx, dy); }
    FOR(_, 0, dy - dx) { y = parents[y]; }
    while (x != y) { x = parents[x]; y = parents[y]; }
    return x;
  }

  int getDistance(int x, int y) {
    int z = getLCA(x, y);
    return dists[depths[z]][x] + dists[depths[z]][y];
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  CentroidDecomposition cd(adj);
  dbg(cd.parents);

  const int kInf = 1e9;
  vector<int> cd_data(n, kInf);

  auto update = [&](int x) {
    int y = x;
    cd_data[y] = 0;
    while (cd.parents[y] != y) {
      y = cd.parents[y];
      int d = cd.getDistance(x, y);
      cd_data[y] = min(cd_data[y], d);
    }
  };

  auto query = [&](int x) -> int {
    int y = x;
    int res = cd_data[x];
    while (cd.parents[y] != y) {
      y = cd.parents[y];
      int d = cd.getDistance(x, y);
      res = min(res, cd_data[y] + d);
    }
    return res;
  };

  update(0);

  for (auto [t, x] : qs) {
    x--;
    if (t == 1) {
      update(x);
    }
    if (t == 2) {
      auto res = query(x);
      cout << res << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/342E/main_v2.cpp

%%%% begin
5 4
1 2
2 3
2 4
4 5
2 1
2 5
1 2
2 5
%%%%
0
3
2
%%%% end
*/
