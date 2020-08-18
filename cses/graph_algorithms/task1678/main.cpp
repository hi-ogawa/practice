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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, m; // n, m <= 10^6
  cin >> n >> m;

  vector<array<ll, 2>> edges(m, {0, 0});
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
  }

  // Detect back edge during DFS
  vector<int> in_time(n, -1);
  vector<int> out_time(n, -1);
  vector<int> parents(n, -1);
  int time = 0;
  bool found = 0;
  tuple<int, int> back_edge;
  function<void(int)> dfs = [&](int v) {
    in_time[v] = time++;
    for (auto u : adj[v]) {
      if (in_time[u] == -1) {
        parents[u] = v;
        dfs(u);
        continue;
      }
      if (out_time[u] == -1 && !found) {
        found = 1;
        back_edge = {v, u};
      }
    }
    out_time[v] = time++;
  };

  FOR(v, 0, n) {
    if (in_time[v] == -1) { dfs(v); }
    if (found) { break; }
  }
  // DD(back_edge);

  if (!found) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }

  // Backtrack from back edge
  auto [v, vp] = back_edge;
  vector<int> res;
  res.push_back(vp);
  while (v != vp) {
    res.push_back(v);
    v = parents[v];
  }
  res.push_back(vp);
  reverse(ALL(res));

  cout << res.size() << endl;
  FOR(i, 0, (int)res.size()) {
    if (i) cout << " ";
    cout << (res[i] + 1);
  }
  cout << endl;
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
python misc/run.py cses/graph_algorithms/task1678/main.cpp --check

%%%% begin
4 5
1 3
2 1
2 4
3 2
3 4
%%%%
4
2 1 3 2
%%%% end
*/
