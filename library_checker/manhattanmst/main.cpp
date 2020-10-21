// WIP

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
  vector<array<ll, 2>> ls(n); // [0, 10^9]
  cin >> ls;

  // Projections to (+1, +1) and (-1, +1)
  vector<array<ll, 2>> ps1(n), ps2(n); // (projection, id)
  FOR(i, 0, n) {
    ps1[i] = {+ ls[i][0] + ls[i][1], i};
    ps2[i] = {- ls[i][0] + ls[i][1], i};
  }
  sort(ALL(ps1));
  sort(ALL(ps2));

  // Possible edges for MST
  vector<array<ll, 3>> edges; // (weight, v0, v1, weight)
  FOR(i, 0, n - 1) {
    edges.push_back({ps1[i + 1][0] - ps1[i][0], ps1[i][1], ps1[i + 1][1]});
    edges.push_back({ps2[i + 1][0] - ps2[i][0], ps2[i][1], ps2[i + 1][1]});
  }
  sort(ALL(edges));

  dbg(ps1);
  dbg(ps2);
  dbg(edges);
  return;

  // MST by merging shorter edges
  Dsu dsu(n);
  ll res = 0;
  vector<array<ll, 2>> res_edges;
  for (auto [w, v0, v1] : edges) {
    if (dsu.find(v0) == dsu.find(v1)) { continue; }
    dsu.merge(v0, v1);
    res += w;
    res_edges.push_back({v0, v1});
  }

  cout << res << "\n";
  for (auto [v0, v1] : res_edges) {
    cout << v0 << " " << v1 << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/manhattanmst/main.cpp

%%%% begin
6
3 8
4 9
2 1
10 5
4 9
2 0
%%%%
21
4 1
5 2
1 0
0 2
1 3
%%%% end
*/
