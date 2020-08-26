// TLE

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

  vector<vector<int>> adj(n, vector<int>(n, 0));
  for (auto [x, y] : edges) { adj[y][x]++; } // Take care dup edges

  auto enc = [](int v) -> ull { return 1ULL << v; };

  // TODO: TLE since P(n, n/2) where n = 20
  auto solve = [&](int v_beg, int len_tot, bool flip) -> vector<map<ull, ll>> {
    // DD(tie(v_beg, len_tot, flip));
    vector<map<ull, ll>> res(n);
    vector<tuple<int, int, ll, ull>> st; // (v, len, multiplicity, history)
    st.push_back({v_beg, 1, 1, enc(v_beg)});
    while (!st.empty()) {
      auto [v, len, k, hist] = st.back(); st.pop_back();
      if (len == len_tot) {
        // DD(tie(v, hist));
        res[v][hist] = add(res[v][hist], k);
        continue;
      }
      FOR(u, 0, n) {
        int p = flip ? adj[v][u] : adj[u][v];
        if (p && (enc(u) & hist) == 0) {
          st.push_back({u, len + 1, mul(k, p), enc(u) | hist});
        }
      }
    }
    return res;
  };

  // Meet in the middle
  int v_beg = 0, v_end = n - 1;
  auto res1 = solve(v_beg, (n / 2) + 1, 0);
  auto res2 = solve(v_end, (n + 1) / 2, 1);
  // DD(res1);
  // DD(res2);

  ull hamiltonian = ~((~0ULL) << n);

  ll res = 0;
  FOR(v, 0, n) { // O(n)
    for (auto [e1, k1] : res1[v]) { // O(binom(n, n/2))
      ull e2 = (hamiltonian & ~e1) | enc(v);
      if (res2[v].count(e2)) {
        ll k2 = res2[v][e2];
        res = add(res, mul(k1, k2));
      }
    }
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
python misc/run.py cses/graph_algorithms/task1690/main.cpp --check

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
