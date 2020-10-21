// WIP

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
  int n, m, v0; // \in [1, 2 x 10^5]
  cin >> n >> m >> v0;
  vector<array<int, 3>> edges(m); // weight \in [0, 10^9]
  cin >> edges;

  vector<vector<array<int, 2>>> adj(n);
  for (auto [x, y, w] : edges) {
    adj[x].push_back({y, w});
  }

  // TODO: clearly not optimal... (see 1st test case)

  // Dijkstra's shortest path
  const ll kInf = 1e18;
  vector<ll> dists(n, kInf);
  vector<int> parents(n);
  set<tuple<ll, int>> heap;
  heap.insert({0, v0});
  dists[v0] = 0;
  parents[v0] = v0;
  while (!heap.empty()) {
    auto [d, v] = *heap.begin(); heap.erase(heap.begin());
    for (auto [u, w] : adj[v]) {
      if (d + w >= dists[u]) { continue; }
      heap.erase({u, dists[u]});
      parents[u] = v;
      dists[u] = d + w;
      heap.insert({d + w, u});
    }
  }

  ll res = 0;
  for (auto [x, y, w] : edges) {
    if (parents[y] == x) { res += w; }
  }
  cout << res << "\n";
  FOR(i, 0, n) {
    cout << parents[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/directedmst/main.cpp

%%%% begin
3 3 0
0 1 3
0 2 2
1 2 1
%%%%
4
0 0 1
%%%% end

%%%% begin
4 4 0
0 1 10
0 2 10
0 3 3
3 2 4
%%%%
17
0 0 3 0
%%%% end

%%%% begin
7 8 3
3 1 10
1 2 1
2 0 1
0 1 1
2 6 10
6 4 1
4 5 1
5 6 1
%%%%
24
2 3 1 3 6 4 2
%%%% end
*/
