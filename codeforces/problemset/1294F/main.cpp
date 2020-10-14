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
  int n; // [3, 2 x 10^5]
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // Take care when tree is a single line
  vector<int> leaves, non_leaves;
  FOR(v, 0, n) {
    ((int)adj[v].size() == 1 ? leaves : non_leaves).push_back(v);
  }
  if (leaves.size() == 2) {
    array<int, 3> res2 = {leaves[0], leaves[1], non_leaves[0]};
    cout << (n - 1) << "\n";
    FOR(i, 0, 3) {
      cout << (res2[i] + 1) << " \n"[i == 2];
    }
    return;
  }

  //
  // PROP. optimal three vertices are leaves. (except when tree is a single line)
  //
  //
  // N.B.
  //   Thus, enumerate all cases of the two patterns and find maximum from them.
  //
  //     A.
  //           /
  //          v
  //        / |\
  //       /  | \
  //      x   y  z
  //
  //     B.
  //          /
  //         .
  //        / \
  //       v   \
  //      / \   \
  //     x  y    z
  //

  // ((d(v, x), x), (d(v, y), y), (d(v, z), z))
  vector<array<array<int, 2>, 3>> dp(n);

  // Enumerate "pattern A"
  function<void(int, int)> dfs = [&](int v, int vp) {
    dp[v][0] = {0, v};
    dp[v][1] = {0, v};
    dp[v][2] = {0, v};
    vector<array<int, 2>> xs;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v);
      xs.push_back(dp[u][0]);
    }
    sort(ALL(xs)); reverse(ALL(xs));
    FOR(i, 0, min(3, (int)xs.size())) {
      dp[v][i][0] = xs[i][0] + 1;
      dp[v][i][1] = xs[i][1];
    }
  };
  dfs(0, 0);
  dbg2(dp);

  // Enumerate "pattern B" by re-rooting
  function<void(int, int)> dfs2 = [&](int v, int vp) {
    if (v != vp) {
      bool ok = 0;
      FOR(i, 0, 3) {
        ok = 1;
        FOR(j, 0, 3) {
          if (dp[vp][i][1] == dp[v][j][1]) {
            ok = 0;
            break;
          }
        }
        if (ok) {
          if (dp[vp][i][0] + 1 >= dp[v][2][0]) {
            dp[v][2][0] = dp[vp][i][0] + 1;
            dp[v][2][1] = dp[vp][i][1];
          }
          break;
        }
      }
      sort(ALL(dp[v])); reverse(ALL(dp[v]));
      assert(ok);
    }
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs2(u, v);
    }
  };
  dfs2(0, 0);
  dbg2(dp);

  int res = 0;
  array<int, 3> res2;
  FOR(v, 0, n) {
    int t = dp[v][0][0] + dp[v][1][0] + dp[v][2][0];
    if (t > res) {
      res = t;
      res2 = {dp[v][0][1], dp[v][1][1], dp[v][2][1]};
    }
  }

  cout << res << "\n";
  FOR(i, 0, 3) {
    cout << (res2[i] + 1) << " \n"[i == 2];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1294F/main.cpp

%%%% begin
3
1 2
2 3
%%%%
2
1 3 2
%%%% end

%%%% begin
8
1 2
2 3
3 4
4 5
4 6
3 7
3 8
%%%%
5
1 8 6
%%%% end
*/
