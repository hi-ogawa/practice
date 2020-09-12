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
  int n; // [1, 10^3]
  cin >> n;
  vector<vector<int>> adj(n);
  FOR(i, 0, n) {
    int j, k;
    cin >> j >> k;
    assert(j == i + 1);
    adj[i].resize(k);
    cin >> adj[i];
    for (auto& x : adj[i]) { x--; }
  }
  dbg2(adj);

  // n x n distance
  vector<vector<int>> dists(n, vector<int>(n, -1));
  auto makeDist = [&](int v0) {
    deque<int> q;
    q.push_back(v0);
    dists[v0][v0] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop_front();
      for (auto u : adj[v]) {
        if (dists[v0][u] == -1) {
          dists[v0][u] = dists[v0][v] + 1;
          q.push_back(u);
        }
      }
    }
  };
  FOR(i, 0, n) { makeDist(i); }
  dbg2(dists);

  // Brute force center
  int res = 1 << 30;
  FOR(v, 0, n) {
    // 1. vertex center
    {
      int d = *max_element(ALL(dists[v]));
      res = min(res, 2 * d);
    }

    // 2. edge center
    for (auto u : adj[v]) {
      int d = 0;
      FOR(t, 0, n) {
        d = max(d, min(dists[v][t], dists[u][t]));
      }
      res = min(res, 2 * d + 1);
    }
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py spoj/MDST/main.cpp --check

%%%% begin
6

10
1 3 2 3 4
2 3 1 5 7
3 3 1 5 6
4 3 1 6 8
5 3 2 3 9
6 3 3 4 10
7 1 2
8 1 4
9 1 5
10 1 6

10
1 4 4 5 7 9
2 1 8
3 4 4 7 8 10
4 3 1 3 9
5 2 1 9
6 2 8 9
7 4 1 3 8 9
8 5 2 3 6 7 9
9 7 1 4 5 6 7 8 10
10 2 3 9

1
1 0

2
1 1 2
2 1 1

3
1 1 2
2 2 1 3
3 1 2

5
1 2 2 4
2 3 1 3 4
3 1 2
4 3 2 5 1
5 1 4

%%%%
5
3
0
1
2
3
%%%% end
*/
