// AFTER EDITORIAL, AC

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
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n, m; // <= 10^3
  cin >> n >> m;
  vector<array<ll, 3>> ls1(n);
  vector<array<ll, 3>> ls2(m);
  cin >> ls1 >> ls2;
  dbg(ls1);
  dbg(ls2);

  // cell coordinates
  vector<ll> xs;
  vector<ll> ys;
  for (auto [x1, x2, y] : ls1) {
    xs.push_back(x1);
    xs.push_back(x2);
    ys.push_back(y);
  }
  for (auto [x, y1, y2] : ls2) {
    xs.push_back(x);
    ys.push_back(y1);
    ys.push_back(y2);
  }
  xs.push_back(*min_element(ALL(xs)) - 1); // for INF detection
  ys.push_back(*min_element(ALL(ys)) - 1);
  xs.push_back(0); // for initial vertex
  ys.push_back(0);
  sort(ALL(xs));
  sort(ALL(ys));
  xs.erase(unique(ALL(xs)), xs.end());
  ys.erase(unique(ALL(ys)), ys.end());
  dbg(xs);
  dbg(ys);

  // binary search
  auto search = [](const vector<ll>& xs, int x) -> int {
    auto it = lower_bound(ALL(xs), x);
    assert(it != xs.end());
    return distance(xs.begin(), it);
  };

  // cell graph
  int nx = xs.size(); // 2 x 10^3
  int ny = ys.size(); // 2 x 10^3

  // cell adjacency (up, right, down, left)
  enum { kU = 0, kR = 1, kD = 2, kL = 3};
  vector<vector<array<bool, 4>>> adj(nx, vector<array<bool, 4>>(ny, {1, 1, 1, 1}));

  // Disconnect cells by segments O(n^2 log(n))
  for (auto [x1, x2, y] : ls1) {
    int i1 = search(xs, x1);
    int i2 = search(xs, x2);
    int j = search(ys, y);
    FOR(i, i1, i2) {
      adj[i][j][kD] = 0;
      adj[i][j - 1][kU] = 0;
    }
  }
  for (auto [x, y1, y2] : ls2) {
    int i = search(xs, x);
    int j1 = search(ys, y1);
    int j2 = search(ys, y2);
    FOR(j, j1, j2) {
      adj[i][j][kL] = 0;
      adj[i - 1][j][kR] = 0;
    }
  }
  dbg2(adj);

  // BFS
  int i_beg = search(xs, 0), j_beg = search(ys, 0);
  dbgv(i_beg, j_beg);
  ll res = 0;
  bool ok = 1;
  vector<vector<bool>> done(nx, vector<bool>(ny, 0));
  deque<array<int, 2>> q;
  q.push_back({i_beg, j_beg});
  done[i_beg][j_beg] = 1;
  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop_front();
    ll area = (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);
    res += area;
    dbgv(i, j, xs[i], ys[j], area);
    if (i == 0 || i == nx - 1 || j == 0 || j == ny - 1) { // Detect INF
      ok = 0; break;
    }
    if (adj[i][j][kU] && !done[i][j + 1]) { done[i][j + 1] = 1; q.push_back({i, j + 1}); }
    if (adj[i][j][kR] && !done[i + 1][j]) { done[i + 1][j] = 1; q.push_back({i + 1, j}); }
    if (adj[i][j][kD] && !done[i][j - 1]) { done[i][j - 1] = 1; q.push_back({i, j - 1}); }
    if (adj[i][j][kL] && !done[i - 1][j]) { done[i - 1][j] = 1; q.push_back({i - 1, j}); }
  }
  dbg(res);
  dbg(ok);

  cout << (ok ? to_string(res) : "INF") << endl;
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
python misc/run.py atcoder/abc168/f/main.cpp --check

%%%% begin
2 2
-1 1 1
-1 1 -1
-1 -1 1
1 -1 1
%%%%
4
%%%% end

%%%% begin
5 6
1 2 0
0 1 1
0 2 2
-3 4 -1
-2 6 3
1 0 1
0 1 2
2 0 2
-1 -4 5
3 -2 4
1 2 4
%%%%
13
%%%% end
*/
