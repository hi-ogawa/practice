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
  int n; // [3, 10^5]
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  vector<int> leaves;
  vector<bool> is_leaf(n);
  FOR(v, 0, n) {
    if ((int)adj[v].size() == 1) {
      leaves.push_back(v);
      is_leaf[v] = 1;
    }
  }
  assert((int)leaves.size() >= 2);
  int root = leaves[0];

  // DFS for depth (from one leaf)
  vector<int> depths(n);
  function<void(int, int)> dfs = [&](int v, int vp) {
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      depths[u] = depths[v] + 1;
      dfs(u, v);
    }
  };
  dfs(root, root);

  // PROP. min(f) <= 3
  // PROP. max(f) >= depth

  // Minimum
  int cnt1 = count_if(ALL(leaves), [&](auto x) { return depths[x] % 2 == 1; });
  int res1 = (cnt1 == 0) ? 1 : 3;

  // Maximum (imagine cancelling "path xor" by last "leaf xor")
  int res2 = 0;
  function<void(int, int)> dfs2 = [&](int v, int vp) {
    bool have_leaf = 0;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      if (is_leaf[u]) { have_leaf = 1; continue; }
      res2++;
      dfs2(u, v);
    }
    if (have_leaf) { res2++; }
  };
  if (count_if(ALL(leaves), [&](auto x) { return depths[x] == 2; })) {
    // Subtract root leaf equivalent
    res2--;
  }
  dfs2(root, root);

  cout << res1 << " " << res2 << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1338B/main.cpp --check

%%%% begin
3
1 2
2 3
%%%%
1 1
%%%% end

%%%% begin
6
1 3
2 3
3 4
4 5
5 6
%%%%
1 4
%%%% end

%%%% begin
6
1 3
2 3
3 4
4 5
4 6
%%%%
3 3
%%%% end

%%%% begin
7
1 2
2 7
3 4
4 7
5 6
6 7
%%%%
1 6
%%%% end
*/
