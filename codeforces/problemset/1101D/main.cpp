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
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 2 x 10^5]
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // Prime exponent is irrelavant in this problem
  auto factorize = [](int n) -> vector<int> {
    vector<int> res;
    for (int p = 2; p * p <= n; p++) {
      if (n % p == 0) {
        while (n % p == 0) { n /= p; }
        res.push_back(p);
      }
    }
    if (n > 1) { res.push_back(n); }
    return res;
  };

  vector<vector<int>> fs(n);
  FOR(i, 0, n) {
    fs[i] = factorize(ls[i]);
  }
  dbg2(fs);

  // dp(v, p) ∋ k  \iff  there's a path from v to its descendent with factor p and length k
  // (Actually need to hold only two longest paths)
  vector<map<int, vector<int>>> dp(n);
  function<void(int, int)> dfs = [&](int v, int vp) {
    for (auto p : fs[v]) {
      // Assure at least two "trivial" path
      dp[v][p].push_back(1);
      dp[v][p].push_back(1);
    }
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v);
      for (auto& [p, ks] : dp[u]) {
        if (count(ALL(fs[v]), p)) {
          dp[v][p].push_back(ks[0] + 1); // Extend only longest path from child
        }
      }
    }
    for (auto& [p, ks] : dp[v]) {
      sort(ALL(ks));
      reverse(ALL(ks));
    }
  };
  dfs(0, 0);
  dbg2(dp);

  int res = 0;
  FOR(v, 0, n) {
    for (auto& [p, ks] : dp[v]) {
      int t = ks[0] + ks[1] - 1;
      res = max(res, t);
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1101D/main.cpp

%%%% begin
3
2 3 4
1 2
2 3
%%%%
1
%%%% end

%%%% begin
3
2 3 4
1 3
2 3
%%%%
2
%%%% end

%%%% begin
3
1 1 1
1 2
2 3
%%%%
0
%%%% end
*/
