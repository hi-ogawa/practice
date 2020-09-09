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
  int n; // [1, 10^5]
  cin >> n;
  vector<ll> ls(n);
  cin >> ls;

  const int b_lim = 60;
  // const int b_lim = 8; // [ debug ]
  vector<vector<int>> edges(b_lim); // hyper edges
  FOR(b, 0, b_lim) {
    FOR(i, 0, n) {
      if (ls[i] & (1LL << b)) {
        edges[b].push_back(i);
      }
    }
  }
  dbg2(edges);

  // 3-perfect graph
  bool ok3 = 0;
  for (auto& vs : edges) {
    if (vs.size() >= 3) { ok3 = 1; break; }
  }
  if (ok3) { cout << 3 << endl; return; }

  // Brute force (E < b_lim)
  vector<vector<int>> adj(n);
  for (auto& vs : edges) {
    if (vs.size() == 2) {
      int x = vs[0], y = vs[1];
      adj[x].push_back(y);
      adj[y].push_back(x);
    }
  }

  // Distance withouth edge (v0, v1)
  vector<int> depths(n);
  auto solve = [&](int v0, int v1) -> int {
    fill(ALL(depths), -1);
    deque<int> q;
    q.push_back(v0);
    depths[v0] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop_front();
      if (v == v1) { break; }
      for (auto u : adj[v]) {
        if (v == v0 && u == v1) { continue; }
        if (depths[u] == -1) {
          depths[u] = depths[v] + 1;
          q.push_back(u);
        }
      }
    }
    return depths[v1];
  };

  int res = -1;
  for (auto& vs : edges) {
    if (vs.size() == 2) {
      int x = vs[0], y = vs[1];
      int t = solve(x, y);
      res = min((ull)res, (ull)t);
    }
  }
  if (res != -1) { res++; }
  cout << res << endl;
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
python misc/run.py codeforces/problemset/1205B/main.cpp --check

%%%% begin
4
3 6 28 9
%%%%
4
%%%% end

%%%% begin
5
5 12 9 16 48
%%%%
3
%%%% end

%%%% begin
4
1 2 4 8
%%%%
-1
%%%% end
*/
