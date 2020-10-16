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
  int n, m; // [1, 2 x 10^5]
  cin >> n >> m;
  vector<array<int, 3>> edges(m);
  cin >> edges;

  // Directed subgraph
  vector<vector<int>> adj(n);
  for (auto [t, x, y] : edges) {
    x--; y--;
    if (t == 0) { continue; }
    adj[x].push_back(y);
  }

  // DFS for out-time ordering
  vector<int> done(n);
  vector<int> out_time(n);
  int t = 0;
  function<void(int)> dfs = [&](int v) {
    done[v] = 1;
    for (auto u : adj[v]) {
      if (done[u]) { continue; }
      dfs(u);
    }
    out_time[v] = t++;
  };
  FOR(v, 0, n) {
    if (!done[v]) { dfs(v); }
  }

  // Cycle checking
  bool ok = 1;
  vector<array<int, 2>> res(m);
  FOR(i, 0, m) {
    auto [t, x, y] = edges[i];
    res[i] = {x, y};
    x--; y--;
    if (t == 0) {
      // Set direction to follow out-time
      if (out_time[y] > out_time[x]) {
        swap(res[i][0], res[i][1]);
      }
      continue;
    }
    // t == 1
    if (out_time[y] > out_time[x]) {
      ok = 0;
      break;
    }
  }
  dbg(ok, res);

  cout << (ok ? "YES" : "NO") << "\n";
  if (!ok) { return; }
  FOR(i, 0, m) {
    cout << res[i][0] << " " << res[i][1] << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1385E/main.cpp

%%%% begin
4
3 1
0 1 3
5 5
0 2 1
1 1 5
1 5 4
0 5 2
1 3 5
4 5
1 1 2
0 4 3
1 3 1
0 2 3
1 2 4
4 5
1 4 1
1 1 3
0 1 2
1 2 4
1 3 2
%%%%
YES
3 1
YES
2 1
1 5
5 4
2 5
3 5
YES
1 2
3 4
3 1
3 2
2 4
NO
%%%% end
*/
