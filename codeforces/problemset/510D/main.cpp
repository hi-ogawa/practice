// MLE

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
  int n; // [1, 300]
  cin >> n;
  vector<int> xs(n), ys(n); // [1, 10^9], [1, 10^5]
  cin >> xs >> ys;

  int xs_gcd = 0;
  for (auto x : xs) {
    xs_gcd = gcd(xs_gcd, x);
  }
  dbg(xs_gcd);
  if (xs_gcd > 1) { cout << -1 << "\n"; return; }

  int k = accumulate(ALL(ys), 0);

  // TODO: do we have nice bound of such sets??
  // dp(i, c) = { gcd(S) | S ⊆ {x1, ..., xi} and cost(S) = c }
  vector<set<int>> dp(k + 1), dp_prev;
  dp[0].insert(0);
  FOR(i, 0, n) {
    dp_prev = dp;
    int x = xs[i];
    int c = ys[i];
    FOR(j, c, k + 1) {
      for (auto g : dp_prev[j - c]) {
        dp[j].insert(gcd(g, x));
      }
    }
  }
  dbg(dp);

  int res = k;
  FOR(c, 0, k + 1) {
    if (dp[c].count(1)) {
      res = c;
      break;
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
python misc/run.py codeforces/problemset/510D/main.cpp

%%%% begin
3
100 99 9900
1 1 1
%%%%
2
%%%% end

%%%% begin
5
10 20 30 40 50
1 1 1 1 1
%%%%
-1
%%%% end

%%%% begin
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
%%%%
6
%%%% end

%%%% begin
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
%%%%
7237
%%%% end
*/
