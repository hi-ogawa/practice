// AFTER EDITORIAL, AC

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
  int n; // [1, 2e5]
  cin >> n;
  vector<int> ls(n); // [1, 2e5]
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  auto getDivisors = [](int x) -> vector<int> {
    vector<int> res;
    FOR(d, 1, (int)sqrt(x) + 1) {
      if (x % d == 0) {
        res.push_back(d);
        if (d * d < x) {
          res.push_back(x / d);
        }
      }
    }
    return res;
  };

  auto divisors = getDivisors(ls[0]);
  int k = divisors.size();

  // dp1(v) = gcd(root-path(v))
  // dp2(v, d) = #{ u | u \in root-path(v) and d ∤ ls[u]}
  vector<int> dp1(n);
  vector<vector<int>> dp2(n, vector<int>(k));

  function<void(int, int)> dfs = [&](int v, int vp) {
    for (auto u : adj[v]) {
      if (u == vp) { continue; }

      int x = ls[u];
      dp1[u] = gcd(x, dp1[v]);

      dp2[u] = dp2[v];
      FOR(j, 0, k) {
        dp2[u][j] += (x % divisors[j] != 0);
      }

      dfs(u, v);
    }
  };
  dfs(0, 0);

  vector<int> res(n);
  FOR(i, 0, n) {
    int t = dp1[i];
    FOR(j, 0, k) {
      if (dp2[i][j] <= 1) {
        t = max(t, divisors[j]);
      }
    }
    res[i] = t;
  }

  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/842C/main.cpp

%%%% begin
2
6 2
1 2
%%%%
6 6
%%%% end

%%%% begin
3
6 2 3
1 2
1 3
%%%%
6 6 6
%%%% end

%%%% begin
1
10
%%%%
10
%%%% end
*/
