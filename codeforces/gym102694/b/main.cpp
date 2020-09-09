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
  int n;
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // DFS
  vector<int> depths(n, -1);
  vector<int> parents(n, -1);
  function<void(int)> dfs = [&](int v) {
    for (auto u : adj[v]) {
      if (depths[u] == -1) {
        depths[u] = depths[v] + 1;
        parents[u] = v;
        dfs(u);
      }
    }
  };

  // Find diameter
  depths[0] = 0;
  dfs(0);
  int v0 = distance(depths.begin(), max_element(ALL(depths)));
  fill(ALL(depths), -1);
  depths[v0] = 0;
  dfs(v0);
  int v1 = distance(depths.begin(), max_element(ALL(depths)));
  int diam = depths[v1];

  // Find center
  int vc0 = v1;
  FOR(i, 0, diam / 2) { vc0 = parents[vc0]; }
  int vc1 = parents[vc0]; // two for odd diameter
  dbgv(v0, v1, vc0, vc1, diam);

  fill(ALL(depths), -1);
  depths[vc0] = 0;
  if (diam % 2 == 1) { depths[vc1] = 0; }
  dfs(vc0);
  if (diam % 2 == 1) { dfs(vc1); }

  FOR(i, 0, n) {
    int res = diam + (depths[i] == diam / 2);
    cout << res << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py codeforces/gym102694/b/main.cpp --check

%%%% begin
4
1 2
2 3
3 4
%%%%
4
3
3
4
%%%% end

%%%% begin
5
4 2
1 4
5 4
3 4
%%%%
3
3
3
2
3
%%%% end
*/
