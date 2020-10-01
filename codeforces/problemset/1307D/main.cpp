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
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> ls(k);
  vector<array<int, 2>> edges(m);
  cin >> ls >> edges;
  for (auto& x : ls) { x--; }
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  //
  // PROP.
  //   Define
  //     d0(u) = d(v0, u)
  //     d1(u) = d(v1, u)
  //     diff(u) = d1(u) - d0(u)
  //     f(u, S) = max_{u ≠ v ∈ S} min(d0(u) + d1(v), d1(u) + d0(v))
  //   then, note that,
  //     min(d0(u) + d1(v), d1(u) + d0(v))
  //       = d0(u) + d0(v) + min(d1(v) - d0(v), d1(u) - d0(u))
  //       = / d0(u) + d1(v)  (if diff(v) <= diff(u))
  //         \ d1(u) + d0(v)  (if diff(v) >= diff(u))
  //   thus, we have,
  //     f(u, S) = max(A, B)
  //     A = d0(u) + max_{diff(v) <= diff(u)} d1(v)
  //     B = d1(u) + max_{diff(v) >= diff(u)} d0(v)
  //

  // BFS for distance
  vector<int> dists0(n, -1), dists1(n, -1);
  auto bfs = [&](int root, vector<int>& dists) {
    deque<int> q;
    q.push_back(root);
    dists[root] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop_front();
      for (auto u : adj[v]) {
        if (dists[u] == -1) {
          dists[u] = dists[v] + 1;
          q.push_back(u);
        }
      }
    }
  };
  bfs(0, dists0);
  bfs(n - 1, dists1);

  // Sort S by diff
  sort(ALL(ls), [&](int x, int y) { return (dists1[x] - dists0[x]) < (dists1[y] - dists0[y]); });
  vector<int> d0(k), d1(k), diff(k);
  FOR(i, 0, k) {
    d0[i] = dists0[ls[i]];
    d1[i] = dists1[ls[i]];
    diff[i] = d1[i] - d0[i];
  }
  dbg(ls, d0, d1, diff);

  // (Reverse) cum max
  vector<int> cm0_rev(k + 1), cm1(k + 1);
  FOR(i, 0, k) {
    cm0_rev[k - i - 1] = max(cm0_rev[k - i], d0[k - i - 1]);
    cm1[i + 1] = max(cm1[i], d1[i]);
  }
  dbg(cm0_rev, cm1);

  // Compute f(u, S)
  vector<int> fs(k);
  FOR(i, 0, k) {
    int t = 0;
    if (i - 1 >= 0) {
      t = max(t, d0[i] + cm1[i]);
    }
    if (i + 1 < k) {
      t = max(t, d1[i] + cm0_rev[i + 1]);
    }
    fs[i] = t;
  }
  dbg(fs);

  // Compute max_u f(u, S) + 1
  int res = *max_element(ALL(fs)) + 1;

  // Compare with current shortest distance
  int res2 = min(res, dists0[n - 1]);
  cout << res2 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1307D/main.cpp --check

%%%% begin
5 5 3
1 3 5
1 2
2 3
3 4
3 5
2 4
%%%%
3
%%%% end

%%%% begin
5 4 2
2 4
1 2
2 3
3 4
4 5
%%%%
3
%%%% end
*/
