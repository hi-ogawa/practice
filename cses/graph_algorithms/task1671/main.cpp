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
  ll n, m;
  cin >> n >> m;

  vector<array<int, 3>> edges(m, {0, 0, 0});
  cin >> edges;

  // Adjacency list
  vector<vector<tuple<int, ll>>> adj(n);
  for (auto [x, y, c] : edges) {
    x--; y--;
    adj[x].push_back({y, c});
  }

  // Dijkstra
  vector<ll> dists(n, -1);
  set<tuple<ll, int>> heap; // min-heap
  heap.insert({0, 0});
  while (!heap.empty()) {
    // DD(heap);
    // DD(dists);
    auto [d, v] = *heap.begin();  heap.erase(heap.begin());
    if (dists[v] != -1) { continue; }
    dists[v] = d;
    for (auto [vv, c] : adj[v]) {
      if (dists[vv] != -1) { continue; }
      heap.insert({d + c, vv});
    }
  }

  FOR(i, 0, n) {
    if (i) cout << " ";
    cout << dists[i];
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
python misc/run.py cses/graph_algorithms/task1671/main.cpp --check

%%%% begin
3 4
1 2 6
1 3 2
3 2 3
1 3 4
%%%%
0 5 2
%%%% end
*/
