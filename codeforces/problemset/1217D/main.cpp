// AC

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
  int n, m; // [1, 5000]
  cin >> n >> m;
  vector<array<int, 2>> edges(m);
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
  }

  // Check cycle by condensation (TODO: really necessarily that much?)
  vector<int> done(n);
  vector<int> out_time(n);
  int t = 0;
  function<void(int)> dfs = [&](int v) {
    done[v] = 1;
    for (auto u : adj[v]) {
      if (done[u]) { continue; }
      dfs(u);
    }
    out_time[v] = t++;
  };
  FOR(v, 0, n) {
    if (done[v]) { continue; }
    dfs(v);
  }
  vector<int> order(n);
  iota(ALL(order), 0);
  sort(ALL(order), [&](int x, int y) { return out_time[x] > out_time[y]; });

  bool cycle = 0;
  vector<vector<int>> adjT(n);
  for (auto [x, y] : edges) {
    adjT[y].push_back(x);
  }
  vector<int> cg(n, -1);
  function<void(int, int)> dfsCG = [&](int v, int cg_id) {
    cg[v] = cg_id;
    for (auto u : adjT[v]) {
      if (cg[u] == cg_id) { cycle = 1; continue; }
      if (cg[u] != -1) { continue; } // usually make cg_adj
      dfsCG(u, cg_id);
    }
  };
  FOR(i, 0, n) {
    int v = order[i];
    if (cg[v] == -1) {
      dfsCG(v, v);
    }
  }
  dbg(out_time);
  dbg(cycle, cg);

  // If cycle, make 2 edge coloring based on out_time direction
  vector<int> res(m);
  if (cycle) {
    FOR(i, 0, m) {
      auto [x, y] = edges[i];
      res[i] = out_time[x] > out_time[y];
    }
  }

  cout << (cycle ? 2 : 1) << "\n";
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
python misc/run.py codeforces/problemset/1217D/main.cpp

%%%% begin
4 5
1 2
1 3
3 4
2 4
1 4
%%%%
1
1 1 1 1 1
%%%% end

%%%% begin
3 3
1 2
2 3
3 1
%%%%
2
1 1 2
%%%% end
*/
