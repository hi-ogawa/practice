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
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& join(ostream& o, const T& x, const string& sep = " ") { for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << sep; } o << *it; } return o; }


// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n, nq; // <= 10^6
  cin >> n >> nq;
  vector<tuple<int, int>> edges(n - 1, {0, 0});
  cin >> edges;
  vector<tuple<int, int>> qs(nq, {0, 0});
  cin >> qs;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y); adj[y].push_back(x);
  }

  // DFS for depth and parent
  vector<int> depths(n, -1);
  vector<int> parents(n, -1);
  function<void(int)> dfs = [&](int v) {
    for (auto u : adj[v]) {
      if (depths[u] == -1) {
        depths[u] = depths[v] + 1;
        parents[u] = v;
        dfs(u);
      }
    }
  };
  depths[0] = 0;
  dfs(0);

  // Make binary lifting table
  int m = 0; // n < 2^m
  while ((1 << m) <= n) { m++; }
  vector<vector<int>> table(m, vector<int>(n, -1));
  table[0] = parents;
  FOR(i, 1, m) {
    FOR(v, 0, n) {
      int u = table[i - 1][v];
      table[i][v] = u == -1 ? -1 : table[i - 1][u];
    }
  }
  // DD2(table);

  auto lift = [&](int v, int e) -> int {
    int res = v;
    int x = 0;
    while (e > 0) {
      if (e & 1) {
        res = table[x][res];
        if (res == -1) { break; }
      }
      x++;
      e >>= 1;
    }
    return res;
  };

  // Lowest common ancestor
  auto getLCA = [&](int x, int y) -> int {
    // Align to same depth
    int dx = depths[x];
    int dy = depths[y];
    if (dx > dy) { swap(x, y); swap(dx, dy); }
    y = lift(y, dy - dx);
    if (x == y) { return x; }

    // // Binary search with "lift" (TLE)
    // // (d0, d1]
    // int d0 = 0;
    // int d1 = dx;
    // while (d0 + 1 < d1) {
    //   int d = (d0 + d1 + 1) / 2;
    //   int xx = lift(x, d), yy = lift(y, d);
    //   if (xx == yy) { d1 = d; }
    //   // else          { d0 = d; } // Usual
    //   else          { x = xx; y = yy; d0 = 0; d1 = depths[x]; } // Accelerate search (still TLE)
    // }
    // int res = lift(x, d1);
    // return res;

    // Directly with table (barely make it 0.99sec)
    int b = 0;
    while (true) {
      int xx = table[b][x], yy = table[b][y];
      if (xx != yy) {
        x = xx; y = yy; b++;
        continue;
      }
      if (b == 0) { x = xx; break; }
      b = 0;
    }
    return x;
  };

  // Answer queries
  for (auto [x, y] : qs) {
    x--; y--;
    int z = getLCA(x, y);
    int res = depths[x] + depths[y] - 2 * depths[z];
    cout << res << endl;
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
python misc/run.py cses/tree_algorithms/task1135/main.cpp --check

%%%% begin
5 3
1 2
1 3
3 4
3 5
1 3
2 5
1 4
%%%%
1
3
2
%%%% end
*/
