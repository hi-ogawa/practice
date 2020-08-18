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
  int m; // <= 15
  cin >> m;

  if (m == 1) {
    cout << "01" << endl;
    return;
  }

  // PROP. (De Brujin graph (k-alphabets, n-length))
  //   1. connected (∵ clearly, any two string can be transformed to each other.)
  //   2. in-deg(v) = out-deg(v) = k (for all v)  (thus Eulerian)
  //   3. |V| = k^n
  //   4. |E| = (2k |V|) / 2 = k^(n+1)

  // De Brujin graph B(2, n)
  int n = m - 1;
  int nv = 1 << n;
  vector<vector<int>> adj(nv);
  FOR(v, 0, nv) {
    adj[v].push_back((2 * v) % nv);
    adj[v].push_back((2 * v + 1) % nv);
  }
  // DD(adj);

  // Construct Euler cycle (cf. task1691 for more general case)
  vector<int> cycle;
  {
    int v = 0;
    while (!adj[v].empty()) {
      cycle.push_back(v);
      auto u = adj[v].back(); adj[v].pop_back(); // pick "1" before "0"
      v = u;
    }
  }
  // DD(cycle);
  // DD(adj);
  int k = cycle.size(); // = 2^(n+1)
  assert(k == (1 << (n + 1))); // TODO: prove above strategy always yields euler cycle in one shot

  // Convert to De Brujin sequence
  stringstream s;
  FOR(i, 0, n) { s << 0; }
  FOR(i, 0, k) {
    int v = cycle[(i + 1) % k];
    s << (v & 1);
  }
  // DD(s.str().size()); // = n + 2^(n+1) - 1
  cout << s.str() << endl;
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
python misc/run.py cses/graph_algorithms/task1692/main.cpp --check

%%%% begin
3
%%%%
0011101000
%%%% end

%%%% begin
2
%%%%
01100
%%%% end
*/
