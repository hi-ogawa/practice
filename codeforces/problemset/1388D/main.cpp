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
  int n;
  cin >> n;
  vector<ll> ls(n), parents(n);
  cin >> ls >> parents;
  for (auto& x : parents) { x--; }

  vector<int> roots;
  vector<vector<int>> adj(n);
  FOR(v, 0, n) {
    if (parents[v] < 0) {
      roots.push_back(v);
      continue;
    }
    int u = parents[v];
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // DFS for tree DP and ordering
  vector<ll> dp(n); // dp[v] = max point of subtree(v)
  vector<int> order1, order2;
  ll res = 0;
  function<void(int, int)> dfs = [&](int v, int vp) {
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v);
      if (dp[u] >= 0) {
        dp[v] += dp[u];
      }
    }
    dp[v] += ls[v];
    res += dp[v];
    ((dp[v] > 0) ? order1 : order2).push_back(v);
  };

  for (auto v : roots) {
    dfs(v, v);
  }
  dbg(dp);
  dbgv(res, order1, order2);

  // Concat ordering
  vector<int> res2;
  reverse(ALL(order2));
  copy(ALL(order1), back_inserter(res2));
  copy(ALL(order2), back_inserter(res2));
  dbg(res2);

  // [ Debug ]
  {
    auto ls2 = ls;
    ll res_check = 0;
    FOR(i, 0, n) {
      int v = res2[i];
      res_check += ls2[v];
      int u = parents[v];
      if (u >= 0) { ls2[u] += ls2[v]; }
    }
    assert(res == res_check);
  }

  cout << res << endl;
  FOR(i, 0, n) {
    cout << (res2[i] + 1) << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1388D/main.cpp --check

%%%% begin
3
1 2 3
2 3 -1
%%%%
10
1 2 3
%%%% end

%%%% begin
2
-1 100
2 -1
%%%%
99
2 1
%%%% end

%%%% begin
10
-10 -1 2 2 5 -2 -3 -4 2 -6
-1 -1 2 2 -1 5 5 7 7 9
%%%%
-9
3 5 6 1 9 4 10 7 8 2
%%%% end
*/
