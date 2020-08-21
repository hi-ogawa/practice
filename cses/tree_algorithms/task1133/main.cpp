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
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& join(ostream& o, const T& x, const string& sep = " ") { for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << sep; } o << *it; } return o; }

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
  int n; // <= 10^6
  cin >> n;

  vector<tuple<int, int>> edges(n - 1, {0, 0});
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y); adj[y].push_back(x);
  }

  // 1st DFS to get subtree sizes and depths
  vector<int> depths(n, -1);
  vector<int> sizes(n, 1);
  function<int(int)> dfs = [&](int v) {
    for (auto u : adj[v]) {
      if (depths[u] == -1) {
        depths[u] = depths[v] + 1;
        sizes[v] += dfs(u);
      }
    }
    return sizes[v];
  };
  depths[0] = 0;
  dfs(0);
  // DD(depths);
  // DD(sizes);

  // 2nd DFS
  //   f(u) = f(v) - |u's sub tree size| + |other vertices|
  //        = f(v) - 2 (sizes(u) + n
  vector<ll> res(n, -1);
  function<void(int)> solve = [&](int v) {
    for (auto u : adj[v]) {
      if (res[u] == -1) {
        res[u] = res[v] - 2 * sizes[u] + n;
        solve(u);
      }
    }
  };
  res[0] = accumulate(ALL(depths), (ll)0);
  solve(0);
  // DD(res);

  join(cout, res) << endl;
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
python misc/run.py cses/tree_algorithms/task1133/main.cpp --check

%%%% begin
5
1 2
1 3
3 4
3 5
%%%%
6 9 5 8 8
%%%% end
*/
