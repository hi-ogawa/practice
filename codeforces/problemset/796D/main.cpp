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
  int n, k, d; // [0, 3 x 10^5]
  cin >> n >> k >> d;
  vector<int> ls(k);
  cin >> ls;
  vector<array<int, 2>> edges(n - 1); // tree
  cin >> edges;
  for (auto& x : ls) { x--; }
  for (auto& [x, y] : edges) { x--; y--; }

  // WLOG, "ls" unique
  auto ls_tmp = set<int>(ALL(ls));
  ls = vector<int>(ALL(ls_tmp));
  k = ls.size();

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // Find shortest path forest
  const int kInf = 1e9;
  vector<int> dists(n, kInf);
  vector<int> parents(n, -1);
  deque<int> q;
  for (auto v : ls) {
    q.push_back(v);
    dists[v] = 0;
    parents[v] = v;
  }
  while (!q.empty()) {
    auto v = q.front(); q.pop_front();
    int w = dists[v];
    for (auto u : adj[v]) {
      if (dists[u] != kInf) { continue; }
      dists[u] = w + 1;
      parents[u] = v;
      q.push_back(u);
    }
  }
  dbg(dists);

  // Shortest path edges
  set<array<int, 2>> sp_edges;
  FOR(v, 0, n) {
    assert(dists[v] <= d);
    int u = parents[v];
    assert(u != -1);
    if (u == v) { continue; }
    sp_edges.insert({min(u, v), max(u, v)});
  }
  dbg(sp_edges);
  assert((int)sp_edges.size() == n - k); // k components

  // Cull non shortest-path edges
  vector<int> res;
  FOR(i, 0, n - 1) {
    auto [x, y] = edges[i];
    if (x > y) { swap(x, y); }
    if (sp_edges.count({x, y})) { continue; }
    res.push_back(i);
  }
  dbg(res);

  int m = res.size();
  cout << m << "\n";
  FOR(i, 0, m) {
    cout << (res[i] + 1) << " \n"[i == m - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/796D/main.cpp

%%%% begin
6 2 4
1 6
1 2
2 3
3 4
4 5
5 6
%%%%
1
5
%%%% end

%%%% begin
6 3 2
1 5 6
1 2
1 3
1 4
1 5
5 6
%%%%
2
4 5
%%%% end
*/
