// WIP, WA

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
  for (auto& [x, y, c] : edges) { x--; y--; c *= -1; } // Minimize cost

  int v_beg = 0, v_end = n - 1;

  // Bellman-Ford (LEMMA. shortest paths are simple <=> no negative cycle)
  bool neg_cycle = 0;
  ll kInf = 1L << 60;
  vector<ll> dists(n, kInf);
  dists[v_beg] = 0;
  FOR(i, 0, n) {
    bool found = 0;
    for (auto [x, y, c] : edges) {
      if (dists[x] == kInf) { continue; }
      ll d = dists[x] + c;
      if (d < dists[y]) {
        dists[y] = d;
        found = 1;
      }
    }
    // DD(dists);
    if (!found) { break; }
    if (found && i >= n - 1) {
      neg_cycle = 1;
    }
  }
  // TODO: Prove "nth improvement detection" detects all negative cycles
  // TODO: Need to check if v_end is reachable from some negative cycle (see 2nd test case)

  if (neg_cycle) {
    cout << -1 << endl;
    return;
  }
  cout << (-dists[v_end]) << endl;
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
python misc/run.py cses/graph_algorithms/task1673/main.cpp --check

%%%% begin
4 5
1 2 1
2 3 1
3 2 1
2 4 1
1 4 100
%%%%
%%%% end

%%%% begin
4 4
1 2 1
2 3 1
3 2 1
1 4 1
%%%%
%%%% end

%%%% begin
4 5
1 2 3
2 4 -1
1 3 -2
3 4 7
1 4 4
%%%%
5
%%%% end
*/
