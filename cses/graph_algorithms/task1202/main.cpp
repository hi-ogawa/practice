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
  int n, m; // <= 10^6
  cin >> n >> m;
  vector<array<int, 3>> edges(m); // cost > 0
  cin >> edges;
  int v_beg = 0, v_end = n -1; // reachable

  vector<vector<tuple<ll, int>>> adj(n);
  for (auto [x, y, c] : edges) {
    x--; y--;
    adj[x].push_back({y, c});
  }

  // Shortest paths from v_beg
  ll kInf = 1LL << 60;
  vector<ll> dists(n, kInf);
  set<tuple<ll, int>> heap;
  dists[v_beg] = 0;
  heap.insert({dists[v_beg], v_beg});
  while (!heap.empty()) {
    auto [d, v] = *heap.begin(); heap.erase(heap.begin());
    if (v == v_end) { break; }
    for (auto [u, c] : adj[v]) {
      if (dists[u] > d + c) {
        if (heap.count({dists[u], u})) { heap.erase({dists[u], u}); }
        dists[u] = d + c;
        heap.insert({dists[u], u});
      }
    }
  }
  dbg(dists);
  ll res1 = dists[v_end];

  // Order by distance from v_beg
  vector<int> order(n, 0);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return dists[x] < dists[y]; });

  // Min cost path counting from v_beg
  ll res2 = 0;
  {
    constexpr ll modulo = 1e9 + 7;
    auto add = [](ll x, ll y) -> ll { return (x + y) % modulo; };

    vector<ll> dp(n, 0);
    dp[v_beg] = 1;
    FOR(i, 0, n) {
      int v = order[i];
      for (auto [u, c] : adj[v]) {
        if (dists[u] == dists[v] + c) {
          dp[u] = add(dp[u], dp[v]);
        }
      }
    }
    dbg(dp);
    res2 = dp[v_end];
  }

  // Min edge count of min cost path from v_beg
  ll res3 = 0;
  {
    vector<ll> dp(n, 1 << 30);
    dp[v_beg] = 0;
    FOR(i, 0, n) {
      int v = order[i];
      for (auto [u, c] : adj[v]) {
        if (dists[u] == dists[v] + c) {
          dp[u] = min(dp[u], dp[v] + 1);
        }
      }
    }
    dbg(dp);
    res3 = dp[v_end];
  }

  // Max edge count of min cost path from v_beg
  ll res4 = 0;
  {
    vector<ll> dp(n, 0);
    FOR(i, 0, n) {
      int v = order[i];
      for (auto [u, c] : adj[v]) {
        if (dists[u] == dists[v] + c) {
          dp[u] = max(dp[u], dp[v] + 1);
        }
      }
    }
    dbg(dp);
    res4 = dp[v_end];
  }

  cout << res1 << " " << res2 << " " << res3 << " " << res4 << endl;
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
python misc/run.py cses/graph_algorithms/task1202/main.cpp --check

%%%% begin
4 5
1 4 5
1 2 4
2 4 5
1 3 2
3 4 3
%%%%
5 2 1 2
%%%% end
*/
