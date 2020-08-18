// AC

// cf. task1193

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
  ll n, m; // <= 10^3
  cin >> n >> m;

  vector<array<int, 2>> edges(m, {0, 0});
  cin >> edges;

  // Adjacency list
  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  // DD(adj);

  // BFS
  int vbeg = 0, vend = n - 1;
  vector<int> parents(n, -1);
  deque<int> queue;
  queue.push_back(vbeg);
  while (!queue.empty()) {
    int v = queue.front(); queue.pop_front();
    if (v == vend) { break; }
    for (auto vv : adj[v]) {
      if (parents[vv] != -1) { continue; }
      parents[vv] = v;
      queue.push_back(vv);
    }
  }
  // DD(parents);

  bool res1 = parents[vend] != -1;
  vector<int> res2;
  if (res1) {
    int v = vend;
    while (v != vbeg) {
      res2.push_back(v);
      v = parents[v];
    }
    res2.push_back(vbeg);
    reverse(ALL(res2));
  }

  if (!res1) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    cout << res2.size() << endl;
    FOR(i, 0, (int)res2.size()) {
      if (i) cout << " ";
      cout << (res2[i] + 1);
    }
    cout << endl;
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
python misc/run.py cses/graph_algorithms/task1667/main.cpp --check

%%%% begin
5 5
1 2
1 3
1 4
2 3
5 4
%%%%
3
1 4 5
%%%% end
*/
