// WIP, WA

// TODO: theory seems fine. where's error?

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
  int n, m; // <= 10^6
  cin >> n >> m;

  vector<tuple<int, int>> edges(m, {0, 0});
  cin >> edges;

  // Find connected components
  Dsu dsu(n);
  vector<int> degs(n, 0);
  vector<set<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    degs[x]++; degs[y]++;
    dsu.merge(x, y);
    adj[x].insert(y);
    adj[y].insert(x);
  }
  map<int, vector<int>> compos;
  FOR(i, 0, n) {
    compos[dsu.find(i)].push_back(i);
  }
  // DD(compos);

  // Check if impossible
  auto& compo0 = compos[dsu.find(0)];
  bool even = 1;
  bool no_other_edges = 1;
  for (auto v : compo0) {
    even = even && (degs[v] % 2 == 0);
  }
  for (auto& [c, vs] : compos) {
    if (c != dsu.find(0)) {
      no_other_edges = no_other_edges && (vs.size() == 1);
    }
  }
  if (!(even && no_other_edges)) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }

  // Construct Euler cycle
  vector<vector<int>> cycles;
  set<int> remains(ALL(compo0));
  {
    int v0 = 0;
    while (true) {
      auto& cycle = cycles.emplace_back();
      int v = v0;
      while (!adj[v].empty()) {
        cycle.push_back(v);
        int u = *(adj[v].begin());
        // adj[v].erase(u);
        // adj[u].erase(v);
        // if (adj[v].size() == 0) { remains.erase(v); }
        // if (adj[u].size() == 0) { remains.erase(u); }
        // [ Assertions ]
        assert(adj[v].count(u));
        assert(adj[u].count(v));
        assert(u != v);
        adj[v].erase(u);
        adj[u].erase(v);
        if (adj[v].size() == 0) {
          assert(remains.count(v));
          remains.erase(v);
        }
        if (adj[u].size() == 0) {
          assert(remains.count(u));
          remains.erase(u);
        }
        v = u;
      }
      cycle.push_back(v0);
      assert(v == v0);
      // DD(cycle);

      // Pick next v0 ∈ remains ∧ cycle (so that we can reconstruct single cycle easily later)
      if (remains.empty()) { break; }
      bool ok = 0;
      for (auto u : cycle) {
        if (remains.count(u)) {
          v0 = u;
          ok = 1;
          break;
        }
      }
      assert(ok); // TODO: this fails for big test case. (shouldn't this mean component is disconnected???)
    }
  }
  // DD(cycles);

  // Reconstruct single cycle
  int nc = cycles.size();
  vector<int> res;
  function<void(int)> concatRec = [&](int i) {
    if (i + 1 == nc) {
      res.insert(res.end(), ALL(cycles[i]));
      return;
    }
    bool done = 0;
    int v = cycles[i + 1][0];
    for (auto u : cycles[i]) {
      if (u == v && !done) {
        concatRec(i + 1);
        done = 1;
        continue;
      }
      res.push_back(u);
    }
  };
  concatRec(0);
  // DD(res);

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
python misc/run.py cses/graph_algorithms/task1691/main.cpp --check

%%%% begin
10 18
5 2
3 9
10 5
2 4
10 2
5 8
8 10
7 3
4 3
3 8
2 7
1 10
8 1
6 3
3 5
4 6
5 4
9 5
%%%%
%%%% end

%%%% begin
4 3
1 2
2 3
3 1
%%%%
%%%% end

%%%% begin
6 8
1 2
1 3
2 3
2 4
2 6
3 5
3 6
4 5
%%%%
1 2 6 3 2 4 5 3 1
%%%% end
*/
