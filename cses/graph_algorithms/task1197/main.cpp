// WIP, WA

// Cf. task1973

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
  ll n, m; // n <= 2500, m <= 5000
  cin >> n >> m;

  vector<array<ll, 3>> edges(m, {0, 0, 0});
  cin >> edges;
  for (auto& [x, y, c] : edges) { x--; y--; }

  // TODO: Use roots of components

  // Bellman-Ford
  ll kInf = 1L << 60;
  vector<ll> dists(n, kInf);
  vector<int> parents(n, -1);
  dists[0] = 0;
  FOR(i, 0, n) {
    bool found = 0;
    for (auto [x, y, c] : edges) {
      if (dists[x] == kInf) { continue; }
      ll d = dists[x] + c;
      if (d < dists[y]) {
        dists[y] = d;
        found = 1;
        // TODO: prove the LAST improving edge always leads to negative cycle
        // TODO: prove why restricting to "if (i == n - 1)" doesn't work.
        parents[y] = x;
      }
    }
    if (!found) { break; }
  }
  // DD(dists);
  // DD(parents);

  // No improvement at nth step
  auto it = find_if(ALL(parents), [](auto x) { return x != -1; });
  if (it == parents.end()) {
    cout << "NO" << endl;
    return;
  }

  // Backtrack improvement path/loop
  vector<bool> visited(n, 0);
  vector<int> vs;
  // int v = *it;
  int v = distance(parents.begin(), it);
  while (visited[v] == 0) {
    // DD(v);
    visited[v] = 1;
    vs.push_back(v);
    v = parents[v];
  }
  // DD(v);
  // DD(vs);

  vector<int> res(find(ALL(vs), v), vs.end());
  res.push_back(v);
  reverse(ALL(res));

  cout << "YES" << endl;
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
python misc/run.py cses/graph_algorithms/task1197/main.cpp --check

%%%% begin
2 1
1 1 0
2 1 3
2 2 -1
3 4 3
4 2 6
%%%%
%%%% end

%%%% begin
4 5
1 2 1
2 4 1
3 1 1
4 1 -3
4 3 -2
%%%%
YES
1 2 4 1
%%%% end
*/
