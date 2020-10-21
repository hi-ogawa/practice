// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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
  int n, m, k; // [1, 1000]
  cin >> n >> m >> k;
  vector<array<int, 3>> edges(m); // weight \in [1, 1000]
  cin >> edges;
  vector<array<int, 2>> ls(k);
  cin >> ls;
  for (auto& [x, y, _w] : edges) { x--; y--; }
  for (auto& [x, y] : ls) { x--; y--; }

  vector<vector<array<int, 2>>> adj(n);
  for (auto [x, y, w] : edges) {
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }

  const int kInf = 1e9;

  // Shortest path x n
  vector<vector<int>> dists(n, vector<int>(n, kInf));
  auto solve = [&](int v0) {
    set<array<int, 2>> heap; // (distance, vertex)
    heap.insert({dists[v0][v0] = 0, v0});
    while (!heap.empty()) {
      auto [d, v] = *heap.begin(); heap.erase(heap.begin());
      for (auto [u, w] : adj[v]) {
        if (d + w >= dists[v0][u]) { continue; }
        heap.erase({dists[v0][u], u});
        heap.insert({dists[v0][u] = d + w, u});
      }
    }
  };
  FOR(v, 0, n) {
    solve(v);
  }
  dbg2(dists);

  int res = kInf;
  for (auto [x, y, _w] : edges) {
    // Update shortest path when removing edges (x, y)
    int t = 0;
    for (auto [xx, yy] : ls) {
      int s = dists[xx][yy];
      s = min(s, dists[x][xx] + dists[y][yy]);
      s = min(s, dists[x][yy] + dists[y][xx]);
      t += s;
    }
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
python misc/run.py codeforces/contest/1433/g/main.cpp

%%%% begin
6 5 2
1 2 5
2 3 7
2 4 4
4 5 2
4 6 8
1 6
5 3
%%%%
22
%%%% end

%%%% begin
5 5 4
1 2 5
2 3 4
1 4 3
4 3 7
3 5 2
1 5
1 3
3 3
1 5
%%%%
13
%%%% end
*/
