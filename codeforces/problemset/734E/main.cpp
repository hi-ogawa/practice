// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// DSU
struct Dsu {
  vector<int> ps;
  Dsu(int n) { ps.resize(n); iota(ALL(ps), 0); }
  int find(int a) {
    if (a == ps[a]) { return a; }
    return ps[a] = find(ps[a]);
  }
  void merge(int dst, int src) {
    ps[find(src)] = find(dst);
  }
};

// Main
void mainCase() {
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // {0, 1}
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  // Components by colors
  Dsu dsu(n);
  for (auto [x, y] : edges) {
    if (ls[x] == ls[y]) {
      dsu.merge(x, y);
    }
  }

  map<int, vector<int>> components;
  FOR(i, 0, n) {
    components[dsu.find(i)].push_back(i);
  }

  vector<int> ids(n);
  int id = 0;
  for (auto& [k, vs] : components) {
    for (auto v : vs) {
      ids[v] = id;
    }
    id++;
  }

  // Quotient graph
  int new_n = components.size();
  vector<array<int, 2>> new_edges;
  for (auto [x, y] : edges) {
    if (ls[x] != ls[y]) {
      new_edges.push_back({ids[x], ids[y]});
    }
  }

  // Diameter
  auto getDiameter = [&](int n, const vector<array<int, 2>>& edges) -> int {
    vector<vector<int>> adj(n);
    for (auto [x, y] : edges) {
      adj[x].push_back(y);
      adj[y].push_back(x);
    }

    // DFS twice for diameter
    vector<int> depths(n);
    function<void(int, int)> dfs = [&](int v, int vp) {
      for (auto u : adj[v]) {
        if (u == vp) { continue; }
        depths[u] = depths[v] + 1;
        dfs(u, v);
      }
    };
    dfs(0, 0);

    int v0 = distance(depths.begin(), max_element(ALL(depths)));
    fill(ALL(depths), 0);
    dfs(v0, v0);

    int res = *max_element(ALL(depths));
    return res;
  };


  // Ceneter of quotient graph (TODO: prove/disprove optimality)
  int diam = getDiameter(new_n, new_edges);
  int res = (diam + 1) / 2;

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/734E/main.cpp

%%%% begin
11
0 0 0 1 1 0 1 0 0 1 1
1 2
1 3
2 4
2 5
5 6
5 7
3 8
3 9
3 10
9 11
%%%%
2
%%%% end

%%%% begin
4
0 0 0 0
1 2
2 3
3 4
%%%%
0
%%%% end
*/
