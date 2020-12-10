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
  int n, m; // n \in [2, 2 x 10^5], m \in [1, 5]
  cin >> n >> m;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  vector<int> sizes(n);
  vector<ll> path_sums(n); // path within subtree(v) and ending at v
  vector<ll> path_sums2(n); // path within subtree(v) and passing through v
  vector<vector<ll>> path_cnts(n, vector<ll>(m));
  vector<vector<ll>> path_cnts2(n, vector<ll>(m));

  function<void(int, int)> dfs = [&](int v, int vp) {
    sizes[v] = 1;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v);
      sizes[v] += sizes[u];
      path_sums[v] += path_sums[u] + sizes[u];
      FOR(r, 0, m) {
        path_cnts[v][(r + 1) % m] += path_cnts[u][r];
      }
    }
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      // Find path connecting to different branches of "v"
      path_sums2[v] += (path_sums[u] + sizes[u]) * (sizes[v] - sizes[u] - 1);
      FOR(r1, 0, m) {
        FOR(r2, 0, m) {
          int r = (r1 + r2 + 1) % m;
          path_cnts2[v][r] += path_cnts[u][r1] * (path_cnts[v][r2] - path_cnts[u][(r2 - 1 + m) % m]);
        }
      }
    }
    // Remove double count
    FOR(r, 0, m) {
      assert(path_cnts2[v][r] % 2 == 0);
      path_cnts2[v][r] /= 2;
    }
    path_cnts[v][0]++; // Finally count "v"
  };
  dfs(0, -1);
  dbg(sizes);
  dbg(path_sums);
  dbg(path_sums2);
  dbg(path_cnts);
  dbg(path_cnts2);

  ll res = 0;
  FOR(v, 0, n) {
    // Sum of path lengths
    ll p = path_sums[v] + path_sums2[v];
    // Sum of "non divisible" part of path lengths
    ll p_ceil = 0;
    ll cnt_ceil = 0;
    FOR(r, 1, m) {
      ll c = path_cnts[v][r] + path_cnts2[v][r];
      p_ceil += r * c;
      cnt_ceil += c;
    }
    assert((p - p_ceil) % m == 0);
    res += (p - p_ceil) / m + cnt_ceil; // Compensate "ceil" operation
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/771C/main.cpp

%%%% begin
6 2
1 2
1 3
2 4
2 5
4 6
%%%%
20
%%%% end

%%%% begin
13 3
1 2
3 2
4 2
5 2
3 6
10 6
6 7
6 13
5 8
5 9
9 11
11 12
%%%%
114
%%%% end

%%%% begin
3 5
2 1
3 1
%%%%
3
%%%% end
*/
