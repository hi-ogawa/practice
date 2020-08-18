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
  ll n, m; // n, m <= 10^6
  cin >> n >> m;

  vector<array<ll, 2>> edges(m, {0, 0});
  cin >> edges;

  vector<vector<int>> adj(n);
  vector<vector<int>> adj_inv(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj_inv[y].push_back(x);
  }

  // Topological sort (via dfs out-time)
  vector<int> top_sort(n, 0);
  {
    vector<int> out_time(n, -1);
    vector<int> in_time(n, -1);
    int time = 0;
    function<void(int)> dfs = [&](int v) {
      in_time[v] = time++;
      for (auto u : adj[v]) {
        if (in_time[u] == -1) { dfs(u); }
      }
      out_time[v] = time++;
      adj[v];
    };
    dfs(0);
    iota(ALL(top_sort), 0);
    sort(ALL(top_sort), [&](auto x, auto y) { return out_time[x] > out_time[y]; });
  }
  // DD(top_sort);

  // Subset DP
  constexpr ll modulo = 1000'000'000 + 7;
  auto madd = [](ll x, ll y) -> ll { return (x + y) % modulo; };
  vector<ll> dp(n, 0);
  dp[0] = 1;
  for (auto v : top_sort) {
    for (auto u : adj[v]) {
      dp[u] = madd(dp[u], dp[v]);
    }
    // DD(tie(v, dp));
  }
  cout << dp[n - 1] << endl;
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
python misc/run.py cses/graph_algorithms/task1681/main.cpp --check

%%%% begin
4 5
1 2
2 4
1 3
3 4
1 4
%%%%
3
%%%% end
*/
