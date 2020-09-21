// TLE

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
  vector<array<int, 3>> edges(m); // w \in [1, 10^5]
  cin >> edges;
  for (auto& [x, y, _w] : edges) { x--; y--; }

  // Sort by weight
  sort(ALL(edges), [](auto x, auto y) { return x[2] < y[2]; });
  dbg(edges);

  vector<vector<array<int, 3>>> adjT(n);
  FOR(i, 0, m) {
    auto [x, y, w] = edges[i];
    adjT[y].push_back({x, i, w});
  }
  FOR(v, 0, n) {
    sort(ALL(adjT[v]), [](auto x, auto y) { return x[2] < y[2]; });
  }

  vector<int> dp(m);
  FOR(i, 0, m) {
    auto [v1, _y, w1] = edges[i];
    int t = 0;
    for (auto [v2, j, w2] : adjT[v1]) { // TODO: analyze complexity (bounded by degree or something?)
      if (w2 >= w1) { break; }
      t = max(t, dp[j]);
    }
    dp[i] = t + 1;
  }
  dbg(dp);

  int res = *max_element(ALL(dp));
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/459E/main.cpp --check

%%%% begin
3 3
1 2 1
2 3 1
3 1 1
%%%%
1
%%%% end

%%%% begin
3 3
1 2 1
2 3 2
3 1 3
%%%%
3
%%%% end

%%%% begin
6 7
1 2 1
3 2 5
2 4 2
2 5 2
2 6 9
5 4 3
4 3 4
%%%%
6
%%%% end
*/
