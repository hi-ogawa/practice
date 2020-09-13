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
  int n, a, b, da, db;
  cin >> n >> a >> b >> da >> db;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  a--; b--;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  auto bfs = [&](int root, vector<int>& dists) {
    deque<int> q;
    q.push_back(root);
    fill(ALL(dists), -1);
    dists[root] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop_front();
      for (auto u : adj[v]) {
        if (dists[u] == -1) {
          dists[u] = dists[v] + 1;
          q.push_back(u);
        }
      }
    }
  };

  vector<int> dists(n);
  bfs(a, dists);
  int dab = dists[b];

  int v_diam = distance(dists.begin(), max_element(ALL(dists)));
  bfs(v_diam, dists);
  int diam = *max_element(ALL(dists));

  bool win_b =
    dab > da &&    // Alice won't catch at first move
    db > 2 * da &&
    2 * da < diam;
  cout << (win_b ? "Bob" : "Alice") << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1404B/main.cpp --check

%%%% begin
4
4 3 2 1 2
1 2
1 3
1 4
6 6 1 2 5
1 2
6 5
2 3
3 4
4 5
9 3 9 2 5
1 2
1 6
1 9
1 3
9 5
7 9
4 8
4 3
11 8 11 3 3
1 2
11 9
4 9
6 5
2 10
3 2
5 9
8 3
7 4
7 10
%%%%
Alice
Bob
Alice
Alice
%%%% end
*/
