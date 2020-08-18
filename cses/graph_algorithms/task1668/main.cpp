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

// Dsu
struct Dsu {
  vector<int> data_;
  Dsu(int n) { data_.resize(n); iota(ALL(data_), 0); }
  int find(int a) {
    if (data_[a] == a) { return a; }
    return data_[a] = find(data_[a]);
  }
  void merge(int dst, int src) {
    data_[find(src)] = find(dst);
  }
};

// Main
void mainCase() {
  ll n, m; // <= 10^3
  cin >> n >> m;

  vector<array<int, 2>> edges(m, {0, 0});
  cin >> edges;

  // DSU and Adjacency list
  Dsu dsu(n);
  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    dsu.merge(x, y);
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  set<int> roots;
  FOR(i, 0, n) { roots.insert(dsu.find(i)); }

  // BFS
  bool valid = 1;
  vector<int> colors(n, -1);
  deque<int> queue;
  for (auto x : roots) {
    queue.push_back(x);
    colors[x] = 0;
  }
  while (!queue.empty()) {
    int v = queue.front(); queue.pop_front();
    int c = 1 - colors[v];
    for (auto vv : adj[v]) {
      if (colors[vv] != -1) {
        if (colors[vv] != c) {
          valid = 0;
          break;
        }
        continue;
      }
      colors[vv] = c;
      queue.push_back(vv);
    }
    if (!valid) { break; }
  }

  if (!valid) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }

  FOR(i, 0, n) {
    if (i) cout << " ";
    cout << (colors[i] + 1);
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
python misc/run.py cses/graph_algorithms/task1668/main.cpp --check

%%%% begin
5 3
1 2
1 3
4 5
%%%%
1 2 2 1 2
%%%% end
*/
