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
  int n; // [3, 10^5]
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  int nq; // [1, 10^5]
  cin >> nq;
  vector<array<int, 5>> qs(nq); // k \in [1, 10^9]
  cin >> qs;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS for parent/depth
  vector<int> parents(n);
  vector<int> depths(n);
  function<void(int, int)> dfs = [&](int v, int vp) {
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      depths[u] = depths[v] + 1;
      parents[u] = v;
      dfs(u, v);
    }
  };
  dfs(0, 0);

  // Binary lifting
  int b_lim = 0;
  while ((1 << b_lim) <= n) { b_lim++; }
  vector<vector<int>> table(b_lim, vector<int>(n));
  table[0] = parents;
  FOR(b, 1, b_lim) {
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

    int b = b_lim - 1;
    while (b >= 0) {
      int xx = table[b][x], yy = table[b][y];
      if (xx == yy) { b--; continue; }
      x = xx; y = yy;
    }
    return table[0][x];
  };

  auto solve = [&](int x, int y, int a, int b, int k) -> bool {
    int dx = depths[x];
    int dy = depths[y];
    int da = depths[a];
    int db = depths[b];
    int dist_ax = da + dx - 2 * depths[getLCA(a, x)];
    int dist_ay = da + dy - 2 * depths[getLCA(a, y)];
    int dist_bx = db + dx - 2 * depths[getLCA(b, x)];
    int dist_by = db + dy - 2 * depths[getLCA(b, y)];

    // Find minimum paths of different topology
    int dist1 = da + db - 2 * depths[getLCA(a, b)]; // original path
    int dist2 = min(dist_ax + dist_by, dist_ay + dist_bx) + 1; // new path

    // Parity check
    if (dist1 <= k && (k - dist1) % 2 == 0) {
      return 1;
    }
    if (dist2 <= k && (k - dist2) % 2 == 0) {
      return 1;
    }
    return 0;
  };

  for (auto [x, y, a, b, k] : qs) {
    bool res = solve(x - 1, y - 1, a - 1, b - 1, k);
    cout << (res ? "YES" : "NO") << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1304E/main.cpp

%%%% begin
5
1 2
2 3
3 4
4 5
5
1 3 1 2 2
1 4 1 3 2
1 4 1 3 3
4 2 3 3 9
5 2 3 3 9
%%%%
YES
YES
NO
YES
NO
%%%% end
*/
