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
  int n; // [2, 3 x 10^5]
  cin >> n;
  string s;
  cin >> s;

  vector<array<int, 2>> edges;
  FOR(i, 0, n) {
    int j = (i + 1) % n;
    if (s[i] == '-') {
      edges.push_back({i, j});
      edges.push_back({j, i});
    }
    if (s[i] == '<') {
      edges.push_back({i, j});
    }
    if (s[i] == '>') {
      edges.push_back({j, i});
    }
  }

  vector<vector<int>> adj(n), adjT(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adjT[y].push_back(x);
  }

  // Condenstation graph (probably overkill but ok)
  vector<int> done(n);
  vector<int> out_time(n);
  int time = 0;
  function<void(int)> dfs = [&](int v) {
    done[v] = 1;
    for (auto u : adj[v]) {
      if (!done[u]) { dfs(u); }
    }
    out_time[v] = time++;
  };
  FOR(v, 0, n) {
    if (!done[v]) { dfs(v); }
  }
  vector<int> order(n);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return out_time[x] > out_time[y]; });

  vector<int> cg(n, -1);
  function<void(int)> dfs2 = [&](int v) {
    for (auto u : adjT[v]) {
      if (cg[u] == -1) {
        cg[u] = cg[v];
        dfs2(u);
      }
    }
  };
  int ncg = 0;
  FOR(i, 0, n) {
    int v = order[i];
    if (cg[v] == -1) {
      cg[v] = ncg++;
      dfs2(v);
    }
  }

  map<int, vector<int>> components;
  FOR(v, 0, n) {
    components[cg[v]].push_back(v);
  }
  dbg(components);

  int res = 0;
  for (auto& [k, c]: components) {
    if (c.size() == 1) { continue; }
    res += c.size();
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1428/b/main.cpp

%%%% begin
4
4
-><-
5
>>>>>
3
<--
2
<>
%%%%
3
5
3
0
%%%% end
*/
