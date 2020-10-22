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
  int n, m; // [1, 3000]
  cin >> n >> m;
  vector<array<int, 2>> edges(m); // connected
  cin >> edges;
  vector<array<int, 3>> ls(2);
  cin >> ls;
  for (auto& [x, y] : edges) { x--; y--; }
  for (auto& [x, y, l] : ls) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // Many-to-many distance
  const int kInf = 1e9;
  vector<vector<int>> dists(n, vector<int>(n, kInf));
  auto bfs = [&](int v0) {
    deque<int> q;
    q.push_back(v0);
    dists[v0][v0] = 0;
    while (!q.empty()) {
      auto v = q.front(); q.pop_front();
      for (auto u : adj[v]) {
        if (dists[v0][u] == kInf) {
          dists[v0][u] = dists[v0][v] + 1;
          q.push_back(u);
        }
      }
    }
  };
  FOR(v, 0, n) {
    bfs(v);
  }

  auto [s1, t1, l1] = ls[0];
  auto [s2, t2, l2] = ls[1];
  bool ok = dists[s1][t1] <= l1 && dists[s2][t2] <= l2;
  if (!ok) { cout << -1 << "\n"; return; }

  // Minimize path intersection by taking paths s.t.
  //  s1 \        / t1
  //      v1 -- v2
  //  s2 /        \ t2
  int res = dists[s1][t1] + dists[s2][t2];
  FOR(v1, 0, n) {
    FOR(v2, 0, n) {
      int d0 = dists[v1][v2];
      int d1 = min(dists[s1][v1] + dists[t1][v2], dists[s1][v2] + dists[t1][v1]);
      int d2 = min(dists[s2][v1] + dists[t2][v2], dists[s2][v2] + dists[t2][v1]);
      if (d0 + d1 <= l1 && d0 + d2 <= l2) {
        int d = d0 + d1 + d2;
        res = min(res, d);
      }
    }
  }
  int res2 = m - res;
  cout << res2 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/543B/main.cpp

%%%% begin
2 1
1 2
1 2 1
1 2 1
%%%%
0
%%%% end

%%%% begin
5 4
1 2
2 3
3 4
4 5
1 3 2
3 5 2
%%%%
0
%%%% end

%%%% begin
5 4
1 2
2 3
3 4
4 5
1 3 2
2 4 2
%%%%
1
%%%% end

%%%% begin
5 4
1 2
2 3
3 4
4 5
1 3 2
3 5 1
%%%%
-1
%%%% end
*/
