// AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, m;
  cin >> n >> m;
  vector<ll> ps(n);
  vector<ll> hs(n);
  cin >> ps >> hs;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS for subtree ps
  vector<ll> ts(n);
  vector<int> parents(n, -1);
  int root = 0;
  function<void(int)> dfs = [&](int v) {
    ts[v] = ps[v];
    for (auto u : adj[v]) {
      if (parents[u] == -1) {
        parents[u] = v;
        dfs(u);
        ts[v] += ts[u];
      }
    }
  };
  parents[root] = root;
  dfs(root);
  dbg(ts);

  // Solve
  //   t = q + r
  //   h = q - r
  vector<ll> qs(n);
  vector<ll> rs(n);
  bool ok1 = 1;
  FOR(i, 0, n) {
    ll t = ts[i], h = hs[i];
    if ((t + h) % 2 != 0) { ok1 = 0; break; }
    if (t + h < 0 || t - h < 0) { ok1 = 0; break; }
    qs[i] = (t + h) / 2;
    rs[i] = (t - h) / 2;
  }
  dbg(hs);
  dbg(qs);
  dbg(rs);
  dbg(ok1);
  if (!ok1) { cout << "NO" << endl; return; }

  // Check ri - pi <= ∑_{i->j} rj
  bool ok2 = 1;
  FOR(v, 0, n) {
    ll s = 0;
    for (auto u : adj[v]) {
      if (parents[u] == v) {
        s += rs[u];
      }
    }
    dbgv(v, rs[v], ps[v], s);
    if (rs[v] - ps[v] > s) { ok2 = 0; break; }
  }

  if (!ok2) { cout << "NO" << endl; return; }
  cout << "YES" << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1388C/main.cpp --check

%%%% begin
2
4 4
1 1 1 1
4 1 -3 -1
1 2
1 3
1 4
3 13
3 3 7
13 1 4
1 2
1 3
%%%%
NO
NO
%%%% end

%%%% begin
2
7 4
1 0 1 1 0 1 0
4 0 0 -1 0 -1 0
1 2
1 3
1 4
3 5
3 6
3 7
5 11
1 2 5 2 1
-11 -2 -6 -2 -1
1 2
1 3
1 4
3 5
%%%%
YES
YES
%%%% end
*/
