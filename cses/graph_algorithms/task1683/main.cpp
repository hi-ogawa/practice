// AC

// Cf. task1682

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
  int n, m; // n, m <= 10^6
  cin >> n >> m;

  vector<array<int, 2>> edges(m, {0, 0});
  cin >> edges;

  vector<vector<int>> adj(n);
  vector<vector<int>> adjT(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adjT[y].push_back(x);
  }

  //
  // Condensation graph
  //

  // Topological sort (via DFS out-time)
  vector<int> top_sort(n, 0);
  {
    vector<int> out_time(n, -1);
    vector<int> in_time(n, -1);
    int t = 0;
    function<void(int)> dfs = [&](int v) {
      in_time[v] = t++;
      for (auto u : adj[v]) {
        if (in_time[u] == -1) { dfs(u); }
      }
      out_time[v] = t++;
      adj[v];
    };
    FOR(v, 0, n) {
      if (in_time[v] == -1) { dfs(v); }
    }
    iota(ALL(top_sort), 0);
    sort(ALL(top_sort), [&](auto x, auto y) { return out_time[x] > out_time[y]; });
  }
  // DD(top_sort);

  // DFS in transpose
  vector<int> compos(n, -1);
  {
    int c = 0;
    function<void(int)> dfs = [&](int v) {
      compos[v] = c;
      for (auto u : adjT[v]) {
        if (compos[u] == -1) { dfs(u); }
      }
    };
    FOR(i, 0, n) {
      int v = top_sort[i];
      if (compos[v] == -1) {
        dfs(v);
        c++;
      }
    }
  }
  // DD(compos);
  // DD(adj_compo);

  ll cm = *max_element(ALL(compos));
  cout << (cm + 1) << endl;
  FOR(i, 0, n) {
    if (i) cout << " ";
    cout << (compos[i] + 1);
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
python misc/run.py cses/graph_algorithms/task1683/main.cpp --check

%%%% begin
5 6
1 2
2 3
3 1
3 4
4 5
5 4
%%%%
2
1 1 1 2 2
%%%% end
*/
