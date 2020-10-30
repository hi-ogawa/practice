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
  int n; // [2, 2 x 10^5]
  cin >> n;
  vector<int> parents(n - 1);
  cin >> parents;
  vector<int> ls(n); // [0, 10^9]
  cin >> ls;

  vector<vector<int>> adj(n);
  FOR(i, 0, n - 1) {
    adj[parents[i] - 1].push_back(i + 1);
  }
  dbg(adj);

  // DFS for subtree leaf count and sum
  vector<int> cnts(n);
  vector<ll> sums(n);
  function<void(int)> dfs = [&](int v) {
    cnts[v] = adj[v].empty();
    sums[v] = ls[v];
    for (auto u : adj[v]) {
      dfs(u);
      cnts[v] += cnts[u];
      sums[v] += sums[u];
    }
  };
  dfs(0);
  dbg(cnts);
  dbg(sums);

  // f(x) = 1  \iff  values can be distributed s.t. ∀leaf, value(leaf) ≤ x
  auto evaluate = [&](ll x) -> bool {
    bool ok = 1;
    FOR(v, 0, n) {
      // if (sums[v] > x * cnts[v]) { // Overflow since x ~ 10^14, cnt ~ 10^5
      if (sums[v] > (__int128)x * cnts[v]) {
        ok = 0;
        break;
      }
    }
    return ok;
  };

  // Debug
  FOR(x, 0, 10) {
    dbg(x, evaluate(x));
  }

  // min { x | f(x) = 1 }
  auto search = [&]() -> ll {
    ll x0 = -1, x1 = accumulate(ALL(ls), (ll)0); // (x0, x1]
    while (x0 + 1 < x1) {
      ll x = (x0 + x1 + 1) / 2;
      if (evaluate(x)) {
        x1 = x;
      } else {
        x0 = x;
      }
    }
    return x1;
  };

  auto res = search();
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1436/d/main.cpp

%%%% begin
3
1 1
3 1 2
%%%%
3
%%%% end

%%%% begin
3
1 1
3 1 3
%%%%
4
%%%% end
*/
