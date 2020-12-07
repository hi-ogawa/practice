// AC

// NOTE: Algorithm looks a bit different but the complexity should be equivalent.

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

const int kInf = 1e9;

// Main
void mainCase() {
  int n1, n2, m; // n1, n2 \in [1, 10^5], m \in [1, 2 x 10^5]
  cin >> n1 >> n2 >> m;
  vector<array<int, 2>> edges(m); // [0, n1) x [0, n2)
  cin >> edges;

  int n = n1 + n2;

  vector<vector<pair<int, int>>> adj(n); // (u, e)
  FOR(e, 0, m) {
    auto [x, y] = edges[e];
    y += n1;
    adj[x].push_back({y, e});
    adj[y].push_back({x, e});
  }

  vector<int> vfree(n, 1);
  vector<int> efree(m, 1);
  vector<pair<int, int>> parents(n); // (parent, edge)
  vector<int> done(n);
  vector<int> dists(n);

  auto bfs = [&]() -> bool {
    deque<int> q;
    fill(ALL(dists), kInf);
    FOR(v, 0, n1) {
      if (vfree[v]) {
        dists[v] = 1;
        q.push_back(v);
      }
    }
    bool found = 0;
    while (!q.empty()) {
      auto v = q.front(); q.pop_front();
      if (v >= n1 && vfree[v]) {
        found = 1;
        continue;
      }
      for (auto [u, e] : adj[v]) {
        if (dists[u] <= dists[v] + 1) { continue; }
        if ((v < n1) != efree[e]) { continue; }
        done[u] = 1;
        dists[u] = dists[v] + 1;
        q.push_back(u);
      }
    }
    return found;
  };

  function<int(int)> dfsImpl = [&](int v) -> int {
    if (v >= n1 && vfree[v]) { return v; } // free V1 reached free V2

    for (auto [u, e] : adj[v]) {
      if (done[u]) { continue; }
      // v1 <---not-free--- v2 or
      // v1 ------free----> v2
      if (v < n1 != efree[e]) { continue; }

      // Shortest augumenting path
      if (dists[u] != dists[v] + 1) { continue; }

      done[u] = 1;
      parents[u] = {v, e};
      int res = dfsImpl(u);
      if (res >= 0) { return res; }
    }
    return -1;
  };

  auto dfs = [&]() -> vector<int> {
    vector<int> goals;
    fill(ALL(done), 0);
    FOR(v, 0, n1) {
      if (vfree[v]) {
        done[v] = 1;
        parents[v] = {v, -1};
        int res = dfsImpl(v);
        if (res >= 0) {
          goals.push_back(res);
        }
      }
    }
    return goals;
  };

  auto update = [&](int v) {
    vfree[v] = 0;
    while (parents[v].first != v) {
      auto [u, e] = parents[v];
      efree[e] ^= 1;
      v = u;
    }
    vfree[v] = 0;
  };

  while (bfs()) {
    auto goals = dfs();
    for (auto v : goals) { update(v); }
  }

  vector<int> res;
  FOR(e, 0, m) {
    if (!efree[e]) { res.push_back(e); }
  }

  int k = res.size();
  cout << k << "\n";
  FOR(i, 0, k) {
    auto [x, y] = edges[res[i]];
    cout << x << " " << y << "\n";
  }
}


int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/bipartitematching/main_v3.cpp

%%%% begin
4 4 7
1 1
2 2
0 0
3 1
1 2
2 0
3 2
%%%%
3
0 0
1 1
2 2
%%%% end
*/
