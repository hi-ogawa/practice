// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
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
  int n; // [3, 10^6]
  cin >> n;
  vector<array<int, 2>> ls(n); // t \in [-100, 100]
  cin >> ls;

  int v0 = -1;
  vector<vector<int>> adj(n);
  vector<int> ts(n);
  FOR(v, 0, n) {
    auto [vp, t] = ls[v];
    ts[v] = t;
    if (vp == 0) { v0 = v; continue; }
    adj[vp - 1].push_back(v);
  }

  int total = accumulate(ALL(ts), 0);
  if (total % 3 != 0) { cout << -1 << "\n"; return; }

  // DFS for tree DP

  vector<int> dp(n);      // dp(v)  = subtree-sum(v)
  vector<int> dp2(n, -1); // dp2(v) = u \iff u is descendent of v and dp(u) = total / 3
  bool ok = 0;
  array<int, 2> res = {-1, -1};
  function<void(int)> dfs = [&](int v) {
    dp[v] = ts[v];
    vector<int> us;
    for (auto u : adj[v]) {
      dfs(u);
      dp[v] += dp[u];
      if (dp2[u] != -1) {
        us.push_back(u);
        dp2[v] = dp2[u];
      }
    }
    if (!ok && us.size() >= 2) {
      ok = 1;
      res[0] = dp2[us[0]];
      res[1] = dp2[us[1]];
    }
    if (!ok && v != v0 && us.size() == 1 && dp[v] == total / 3 * 2) {
      ok = 1;
      res[0] = dp2[us[0]];
      res[1] = v;
    }
    if (dp[v] == total / 3) {
      dp2[v] = v;
    }
  };
  dfs(v0);
  dbg(total, total / 3);
  dbg(dp);
  dbg(dp2);

  if (!ok) { cout << -1 << "\n"; return; }
  auto [r1, r2] = res;
  r1++; r2++;
  cout << r1 << " " << r2 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/767C/main.cpp

%%%% begin
6
2 4
0 5
4 2
2 1
1 1
4 2
%%%%
1 4
%%%% end

%%%% begin
6
2 4
0 6
4 2
2 1
1 1
4 2
%%%%
-1
%%%% end
*/
