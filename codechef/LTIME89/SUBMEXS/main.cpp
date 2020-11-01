// CONTEST, AC

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
  int n; // [2, 10^5]
  cin >> n;
  vector<int> ls(n - 1);
  cin >> ls;

  vector<vector<int>> adj(n);
  FOR(i, 0, n - 1) {
    adj[ls[i] - 1].push_back(i + 1);
  }
  dbg(adj);

  // DFS for DP
  vector<int> depths(n);
  vector<int> sizes(n);
  vector<ll> dp(n); // We can only gain in single path
  function<void(int)> dfs = [&](int v) {
    sizes[v] = 1;
    ll t = 0;
    for (auto u : adj[v]) {
      depths[u] = depths[v] + 1;
      dfs(u);
      sizes[v] += sizes[u];
      t = max(t, dp[u]);
    }
    dp[v] = sizes[v] + t;
  };
  dfs(0);
  dbg(depths);
  dbg(sizes);
  dbg(dp);

  ll res = dp[0];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/LTIME89/SUBMEXS/main.cpp

%%%% begin
2
3
1 1
5
1 1 2 2
%%%%
4
9
%%%% end
*/
