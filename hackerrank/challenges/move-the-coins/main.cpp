// AC

// Cf. cses/mathematics/task1099/main.cpp (analogous proposition holds here (odd depth XORs))
// NOTE: hackerrank doesn't support C++17

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
#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl << flush; } while (0)
#else
#define dbg(...)
#endif
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;

  vector<int> ls(n); // [0, 20]
  cin >> ls;

  vector<array<int, 2>> edges(n - 1);
  FOR(i, 0, n - 1) { cin >> edges[i][0] >> edges[i][1]; }

  int nq; // [1, 10^5]
  cin >> nq;

  vector<array<int, 2>> qs(nq);
  FOR(i, 0, nq) { cin >> qs[i][0] >> qs[i][1]; }

  for (auto& xy : edges) { xy[0]--; xy[1]--; }
  for (auto& xy : qs) { xy[0]--; xy[1]--; }

  vector<vector<int>> adj(n);
  for (auto xy : edges) {
    adj[xy[0]].push_back(xy[1]);
    adj[xy[1]].push_back(xy[0]);
  }

  // DFS for parents/depths
  vector<int> parents(n, -1);
  vector<int> depths(n, -1);
  function<void(int)> dfs = [&](int v) {
    for (auto u : adj[v]) {
      if (parents[u] == -1) {
        parents[u] = v;
        depths[u] = depths[v] + 1;
        dfs(u);
      }
    }
  };
  parents[0] = 0;
  depths[0] = 0;
  dfs(0);

  // Binary lifting
  int b_lim = 0; // n < 2^b
  while ((1 << b_lim) <= n) { b_lim++; }
  vector<vector<int>> table(b_lim, vector<int>(n));
  table[0] = parents;
  FOR(b, 1, b_lim) {
    FOR(v, 0, n) {
      table[b][v] = table[b - 1][table[b - 1][v]];
    }
  }
  auto lift = [&](int v, int e) -> int {
    int b = 0;
    while (e > 0) {
      if (e & 1) { v = table[b][v]; }
      e >>= 1; b++;
    }
    return v;
  };

  // Precompute subtree even/odd depth XOR
  vector<array<int, 2>> xors(n);
  function<void(int)> dfs2 = [&](int v) {
    xors[v][0] = ls[v];
    for (auto u : adj[v]) {
      if (parents[u] == v) {
        dfs2(u);
        xors[v][0] ^= xors[u][1];
        xors[v][1] ^= xors[u][0];
      }
    }
  };
  dfs2(0);
  int init_nim = xors[0][1];
  bool is_zero = accumulate(ALL(ls), 0) - ls[0] == 0;
  dbg(ls);
  dbg(xors);
  dbg(init_nim, is_zero);

  // Answer query
  auto solve = [&](int u, int v) -> string {
    // v is u's descendent
    int du = depths[u], dv = depths[v];
    if (du <= dv && u == lift(v, dv - du)) { return "INVALID"; }

    // Update Nim value
    int x = xors[u][(du + 1) % 2];
    int y = xors[u][dv % 2];
    int z = init_nim ^ x ^ y;
    dbg(u, v, x, y, z);
    return (!is_zero && z) ? "YES" : "NO";
  };

  for (auto uv : qs) {
    string res = solve(uv[0], uv[1]);
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
python misc/run.py hackerrank/challenges/move-the-coins/main.cpp --check

%%%% begin
6
0 2 2 1 3 2
1 2
1 3
3 4
3 5
4 6
3
6 2
4 1
3 6
%%%%
NO
YES
INVALID
%%%% end
*/
