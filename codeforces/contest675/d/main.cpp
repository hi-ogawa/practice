// AFTER EDITORIAL, AC

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
  int k, n; // k \in [1, 10^9], n \in [0, 10^5]
  cin >> k >> n;
  array<int, 2> v0, v1;
  cin >> v0 >> v1;
  vector<array<int, 2>> ls(n); // [1, k]
  cin >> ls;

  // NOTE:
  //   Due to "reverse triangle inequality" of distance,
  //   it suffices to consider four neighbors in the axis-aligned directions.

  // For simplicity, regard "v0" as warp point
  int v_beg = n++;
  ls.push_back(v0);

  // Construct graph with edge weight = min(dx, dy)
  vector<array<int, 2>> xs(n), ys(n);
  FOR(i, 0, n) {
    xs[i] = {ls[i][0], i};
    ys[i] = {ls[i][1], i};
  }
  sort(ALL(xs));
  sort(ALL(ys));

  vector<vector<array<int, 2>>> adj(n); // (vertex, weight)
  FOR(i, 0, n) {
    auto [x, y] = ls[i];
    auto itx = lower_bound(ALL(xs), array<int, 2>({x, i}));
    auto ity = lower_bound(ALL(ys), array<int, 2>({y, i}));
    if (next(itx) != xs.end()) {
      auto [xj, j] = *next(itx);
      adj[i].push_back({j, xj - x});
    }
    if (itx != xs.begin()) {
      auto [xj, j] = *prev(itx);
      adj[i].push_back({j, x - xj});
    }
    if (next(ity) != ys.end()) {
      auto [yj, j] = *next(ity);
      adj[i].push_back({j, yj - y});
    }
    if (ity != ys.begin()) {
      auto [yj, j] = *prev(ity);
      adj[i].push_back({j, y - yj});
    }
  }
  dbg2(adj);

  // Shortest path to warp points
  const ll kInf = 1e18;
  vector<ll> dists(n, kInf);
  set<array<ll, 2>> heap; // (distance, vertex)
  dists[v_beg] = 0;
  heap.insert({0, v_beg});
  while (!heap.empty()) {
    auto [d, v] = *heap.begin(); heap.erase(heap.begin());
    for (auto [u, w] : adj[v]) {
      if (d + w >= dists[u]) { continue; }
      heap.erase({dists[u], u});
      dists[u] = d + w;
      heap.insert({dists[u], u});
    }
  }
  dbg(dists);

  // Distance to goal (edge weight = dx + dy (i.e. Manhattan))
  ll res = kInf;
  FOR(v, 0, n) {
    auto [x0, y0] = ls[v];
    auto [x1, y1] = v1;
    ll t = dists[v] + abs(x1 - x0) + abs(y1 - y0);
    res = min(res, t);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest675/d/main.cpp

%%%% begin
5 3
1 1 5 5
1 2
4 1
3 3
%%%%
5
%%%% end

%%%% begin
84 5
67 59 41 2
39 56
7 2
15 3
74 18
22 7
%%%%
42
%%%% end
*/
