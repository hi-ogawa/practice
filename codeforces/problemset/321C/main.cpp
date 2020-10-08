// AC

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

// Main
void mainCase() {
  int n; // [2, 10^5]
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<set<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].insert(y);
    adj[y].insert(x);
  }

  vector<int> res(n, -1); // 0, 1, ... (if res[i] >= 26, then invalid)
  vector<int> dists(n);
  vector<int> parents(n);

  // BFS
  function<void(int, int, int, vector<int>&)> dfs = [&](
      int v, int vp, int d, vector<int>& visited) {
    dists[v] = d;
    parents[v] = vp;
    visited.push_back(v);
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v, d + 1, visited);
    }
  };

  // Find center (assuming v0 is one of diameter vertex)
  auto findCenter = [&](int v0) -> int {
    vector<int> visited;
    dfs(v0, v0, 0, visited);
    int v1 = v0;
    for (auto u : visited) {
      if (dists[u] > dists[v1]) { v1 = u; }
    }
    int c = v1;
    FOR(i, 0, dists[v1] / 2) { c = parents[c]; }
    return c;
  };

  // Find initial center
  vector<int> visited0;
  dfs(0, 0, 0, visited0);
  int v0 = distance(dists.begin(), max_element(ALL(dists)));
  int c0 = findCenter(v0);
  dbg(v0, c0);

  // Split at the center and recursively solve for subtree
  // (clearly the depth won't exceed "26" since that would mean n >= 2^26)
  function<void(int, int)> solve = [&](int c, int depth) {
    res[c] = depth;
    for (auto u : adj[c]) {
      adj[u].erase(c);
      int cc = findCenter(u);
      solve(cc, depth + 1);
    }
  };
  solve(c0, 0);
  dbg(res);

  bool ok = *max_element(ALL(res)) < 26;
  if (!ok) { cout << "Impossible!" << "\n"; return; }
  FOR(i, 0, n) {
    cout << (char)(res[i] + 'A') << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/321C/main.cpp

%%%% begin
4
1 2
1 3
1 4
%%%%
A B B B
%%%% end

%%%% begin
10
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
%%%%
D C B A D C B D C D
%%%% end
*/
