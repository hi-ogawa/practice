// AC

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

// Main
void mainCase() {
  int n, m; // [1, 2 x 10^5]
  cin >> n >> m;
  vector<array<ll, 3>> edges(m); // weight \in [1, 10^12]
  cin >> edges;
  vector<ll> ls(n); // [1, 10^12]
  cin >> ls;

  vector<vector<array<ll, 2>>> adj(n);
  for (auto [x, y, w] : edges) {
    x--; y--;
    adj[x].push_back({y, 2 * w});
    adj[y].push_back({x, 2 * w});
  }

  // Dijkstra DP
  auto dp = ls;
  set<array<ll, 2>> heap; // (cost, vertex)
  FOR(v, 0, n) {
    heap.insert({dp[v], v});
  }
  while (!heap.empty()) {
    auto [c, v] = *heap.begin(); heap.erase(heap.begin());
    for (auto [u, w] : adj[v]) {
      if (c + w >= dp[u]) { continue; }
      heap.erase({dp[u], u});
      heap.insert({dp[u] = c + w, u});
    }
  }

  FOR(i, 0, n) {
    cout << dp[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/938D/main.cpp

%%%% begin
4 2
1 2 4
2 3 7
6 20 1 25
%%%%
6 14 1 25
%%%% end

%%%% begin
3 3
1 2 1
2 3 1
1 3 1
30 10 20
%%%%
12 10 12
%%%% end
*/
