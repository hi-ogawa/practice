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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, m; // [0, 10^5]
  cin >> n >> m;
  vector<array<int, 3>> edges(m);
  cin >> edges;

  int v_beg = 0, v_end = n - 1;
  int m1 = 0;

  vector<vector<array<int, 2>>> adj(n);
  for (auto [x, y, w] : edges) {
    x--; y--;
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
    m1 += w;
  }

  //
  // PROP.
  //   Writing
  //     k = #{repares}
  //     d = d(1, n)
  //   then,
  //     #{destructs} + #{repares} = (m1 - (d - k)) + k = m1 - d + 2k
  //   Thus, optimum is achieved when k is minimum.
  //

  // Dijkstra DP
  const int kInf = 1e9;
  vector<array<int, 2>> dists(n, {kInf, kInf}); // (d, k)
  set<pair<array<int, 2>, int>> heap; // ((d, k), v)
  vector<int> parents(n, -1);
  heap.insert({dists[v_beg] = {0, 0}, v_beg});
  while (!heap.empty()) {
    auto [dk, v] = *heap.begin(); heap.erase(heap.begin());
    auto [d, k] = dk;
    for (auto [u, w] : adj[v]) {
      array<int, 2> dk2 = {d + 1, k + (w == 0)};
      if (dk2 >= dists[u]) { continue; }
      parents[u] = v;
      heap.erase({dists[u], u});
      heap.insert({dists[u] = dk2, u});
    }
  }

  auto [d, k] = dists[v_end];

  set<array<int, 2>> path;
  int v = v_end;
  FOR(_, 0, d) {
    int vp = parents[v];
    path.insert({vp, v});
    v = vp;
  }

  int res = m1 - d + 2 * k;
  cout << res << "\n";
  for (auto [x, y, w1] : edges) {
    x--; y--;
    int w2 = path.count({x, y}) || path.count({y, x});
    if (w1 == w2) { continue; }
    x++; y++;
    cout << x << " " << y << " " << w2 << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/507E/main.cpp

%%%% begin
2 1
1 2 0
%%%%
1
1 2 1
%%%% end

%%%% begin
4 4
1 2 1
1 3 0
2 3 1
3 4 1
%%%%
3
1 2 0
1 3 1
2 3 0
%%%% end

%%%% begin
8 9
1 2 0
8 3 0
2 3 1
1 4 1
8 7 0
1 5 1
4 6 1
5 7 0
6 8 0
%%%%
3
2 3 0
1 5 0
6 8 1
%%%% end
*/
