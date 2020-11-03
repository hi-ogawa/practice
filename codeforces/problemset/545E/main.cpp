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
  int n, m; // [0, 3 x 10^5]
  cin >> n >> m;
  vector<array<int, 3>> edges(m); // weight \in [1, 10^9], connected
  cin >> edges;
  int v0;
  cin >> v0;
  v0--;

  vector<vector<array<int, 2>>> adj(n);
  for (auto [x, y, w] : edges) {
    x--; y--;
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }

  // Dijkstra DP variant
  const ll kInf = 1e18;
  vector<ll> dists(n, kInf);
  vector<int> parents(n, -1);
  set<array<ll, 4>> heap; // (distance, last edge weight, vertex, parent)
  heap.insert({dists[v0] = 0, 0, v0, -1});
  while (!heap.empty()) {
    dbg(heap);
    auto [d, _w, v, vp] = *heap.begin(); heap.erase(heap.begin());
    if (parents[v] != -1) { continue; }
    parents[v] = vp;
    for (auto [u, w] : adj[v]) {
      if (d + w > dists[u]) { continue; }
      heap.insert({dists[u] = d + w, w, u, v});
    }
  }
  dbg(dists);
  dbg(parents);

  ll res1 = 0;
  vector<int> res2;
  FOR(i, 0, m) {
    auto [x, y, w] = edges[i];
    x--; y--;
    if (parents[x] == y || parents[y] == x) {
      res1 += w;
      res2.push_back(i);
    }
  }

  cout << res1 << "\n";
  FOR(i, 0, n - 1) {
    cout << (res2[i] + 1) << " \n"[i == n - 2];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/545E/main.cpp

%%%% begin
3 3
1 2 1
2 3 1
1 3 2
3
%%%%
2
1 2
%%%% end

%%%% begin
4 4
1 2 1
2 3 1
3 4 1
4 1 2
4
%%%%
4
2 3 4
%%%% end
*/
