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

  vector<vector<int>> adj(n);
  Dsu dsu(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
    dsu.merge(x, y);
  }
  // DD(adj);

  set<int> roots;
  FOR(i, 0, n) { roots.insert(dsu.find(i)); }

  // BFS
  bool found = 0;
  int v0, v1;
  vector<int> dists(n, -1);
  vector<int> parents(n, -1);
  deque<int> queue;
  for (auto r : roots) {
    queue.push_back(r);
    dists[r] = 0;
  }
  while (!queue.empty()) {
    // DD(tie(dists, parents));
    int v = queue.front(); queue.pop_front();
    for (auto vv : adj[v]) {
      if (dists[vv] != -1) {
        if (vv != parents[v]) {
          v0 = v; v1 = vv;
          found = 1;
          break;
        }
        continue;
      }
      dists[vv] = dists[v] + 1;
      parents[vv] = v;
      queue.push_back(vv);
    }
    if (found) { break; }
  }
  // DD(dists);
  // DD(parents);
  // DD(tie(v0, v1));

  if (!found) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }

  // Lowest common ancestor
  deque<int> res;
  if (dists[v0] > dists[v1]) { swap(v0, v1); }
  while (dists[v0] < dists[v1]) {
    res.push_back(v1);
    v1 = parents[v1];
  }
  while (v0 != v1) {
    res.push_front(v0);
    res.push_back(v1);
    v0 = parents[v0];
    v1 = parents[v1];
  }
  res.push_front(v0);
  res.push_back(v0);
  // DD(res);

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
python misc/run.py cses/graph_algorithms/task1669/main.cpp --check

%%%% begin
5 6
1 3
1 2
5 3
1 5
2 4
4 5
%%%%
4
3 5 1 3
%%%% end
*/
