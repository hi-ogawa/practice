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
  int n, m;
  cin >> n >> m;
  vector<array<int, 2>> edges(m);
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  int v0, v1, v2;
  array<vector<int>, 3> sets;
  v0 = 0;
  if (adj[v0].size() < 2) { cout << -1 << endl; return; }

  v1 = adj[v0][0];
  sort(ALL(adj[v0]));
  sort(ALL(adj[v1]));
  set_intersection(ALL(adj[v0]), ALL(adj[v1]), back_inserter(sets[2]));
  if (sets[2].size() == 0) { cout << -1 << endl; return; }

  v2 = sets[2][0];
  sort(ALL(adj[v2]));
  set_intersection(ALL(adj[v1]), ALL(adj[v2]), back_inserter(sets[0]));
  set_intersection(ALL(adj[v2]), ALL(adj[v0]), back_inserter(sets[1]));
  dbgv(v0, v1, v2);
  dbg2(sets);

  vector<int> res(n, -1);
  bool ok = 1;
  // Check tri-partite
  FOR(i, 0, 3) {
    for (auto v : sets[i]) {
      if (res[v] != -1) { ok = 0; break; }
      res[v] = i;
    }
  }
  FOR(v, 0, n) {
    if (res[v] == -1) { ok = 0; break; }
  }
  for (auto [x, y] : edges) {
    if (res[x] == res[y]) { ok = 0; break; }
  }
  if (!ok) { cout << -1 << endl; return; }

  // Check complete
  vector<vector<int>> cnts(3, vector<int>(3));
  for (auto [x, y] : edges) {
    if (res[x] > res[y]) { swap(x, y); }
    cnts[res[x]][res[y]]++;
  }
  FOR(i, 0, 3) {
    FOR(j, i + 1, 3) {
      if (cnts[i][j] != (int)(sets[i].size() * sets[j].size())) {
        ok = 0; break;
      }
    }
  }

  if (!ok) { cout << -1 << endl; return; }
  FOR(i, 0, n) { cout << (res[i] + 1) << " \n"[i == n - 1]; }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1228D/main.cpp --check

%%%% begin
4 6
1 2
1 3
1 4
2 3
2 4
3 4
%%%%
-1
%%%% end

%%%% begin
3 3
1 2
2 3
1 3
%%%%
1 2 3
%%%% end

%%%% begin
6 11
1 2
1 3
1 4
1 5
1 6
2 4
2 5
2 6
3 4
3 5
3 6
%%%%
1 2 2 3 3 3
%%%% end

%%%% begin
4 6
1 2
1 3
1 4
2 3
2 4
3 4
%%%%
-1
%%%% end
*/
