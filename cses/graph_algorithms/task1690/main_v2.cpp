// AFTER EDITORIAL, AC

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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Modulo op
constexpr ll modulo = 1000'000'000 + 7;
ll add(ll x, ll y) { return (x + y) % modulo; };
ll mul(ll x, ll y) { return (x * y) % modulo; };

// Main
void mainCase() {
  int n, m; // n <= 20
  cin >> n >> m;
  vector<array<int, 2>> edges(m, {0});
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<ll>> adj(n, vector<ll>(n, 0));
  for (auto [x, y] : edges) { adj[y][x]++; } // Take care dup edges

  auto enc = [](int v) -> ull { return 1 << v; };

  int v_beg = 0, v_end = n - 1;
  ull hamiltonian = ~((~0ULL) << n);

  // dp[v][hist] = #{ Ham-paths reaching "v" after visiting "hist" starting from "v_beg" }
  vector<vector<ll>> dp(n, vector<ll>(1 << n, 0));
  dp[v_beg][0] = 1;

  FOR(hist, 0, 1 << n) {
    FOR(v, 0, n) {
      ll p = dp[v][hist];
      if (p == 0 || (hist & enc(v))) { continue; }
      ull histv = hist | enc(v);
      FOR(u, 0, n) {
        ll q = adj[u][v];
        if (q == 0 || (histv & enc(u))) { continue; }
        dp[u][histv] = add(dp[u][histv], mul(p, q));
      }
    }
  }
  ll res = dp[v_end][hamiltonian & ~enc(v_end)];
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
python misc/run.py cses/graph_algorithms/task1690/main_v2.cpp --check

%%%% begin
2 3
1 2
1 2
1 2
%%%%
%%%% end

%%%% begin
4 6
1 2
1 3
2 3
3 2
2 4
3 4
%%%%
2
%%%% end
*/
