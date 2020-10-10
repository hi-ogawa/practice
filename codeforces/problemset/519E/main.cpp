// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  int nq; // [1, 10^5]
  cin >> nq;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x-- ;y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS for parents, depths, subtree sizee
  vector<int> parents(n), depths(n), sizes(n);
  function<void(int, int, int)> dfs = [&](int v, int vp, int d) {
    parents[v] = vp;
    depths[v] = d;
    sizes[v] = 1;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v, d + 1);
      sizes[v] += sizes[u];
    }
  };
  dfs(0, 0, 0);

  // Binary lifting
  int nb = 0;
  while ((1 << nb) <= n) { nb++; }
  vector<vector<int>> table(nb, vector<int>(n));
  table[0] = parents;
  FOR(b, 1, nb) {
    FOR(v, 0, n) {
      table[b][v] = table[b - 1][table[b - 1][v]];
    }
  }

  auto lift = [&](int x, int e) -> int {
    int b = 0;
    while (e > 0) {
      if (e & 1) { x = table[b][x]; }
      e >>= 1; b++;
    }
    return x;
  };

  auto getLCA = [&](int x, int y) -> int {
    int dx = depths[x], dy = depths[y];
    if (dx > dy) { swap(dx, dy); swap(x, y); }
    y = lift(y, dy - dx);
    if (x == y) { return x; }

    int b = nb - 1;
    while (b >= 0) {
      int xx = table[b][x], yy = table[b][y];
      if (xx == yy) { b--; continue; }
      x = xx; y = yy;
    }
    return table[0][x];
  };

  auto solve = [&](int x, int y) -> int {
    if (x == y) { return n; }

    int z = getLCA(x, y);
    int dx = depths[x], dy = depths[y], dz = depths[z];

    // WLOG dx <= dy
    if (dx > dy) { swap(dx, dy); swap(x, y); }

    int dist = dx + dy - 2 * dz;
    if (dist % 2 == 1) { return 0; }

    // LCA at the middle
    if (dx == dy) {
      int xx = lift(x, dist / 2 - 1), yy = lift(y, dist / 2 - 1);
      return n - sizes[xx] - sizes[yy];
    }

    // LCA not at the middle
    int yy = lift(y, dist / 2 - 1);
    int w = lift(yy, 1);
    return sizes[w] - sizes[yy];
  };

  for (auto [x, y] : qs) {
    x--; y--;
    auto res = solve(x, y);
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/519E/main.cpp

%%%% begin
5
1 2
1 3
2 5
2 4
1
5 4
%%%%
3
%%%% end

%%%% begin
4
1 2
1 3
2 4
1
2 3
%%%%
1
%%%% end

%%%% begin
4
1 2
2 3
2 4
2
1 2
1 3
%%%%
0
2
%%%% end
*/
