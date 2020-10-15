// AFTER EDITORIAL, WIP

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
  ll n, x, y; // n \in [1, 10^7], x, y \in [1, 10^9]
  cin >> n >> x >> y;

  //
  // PROP. Shortest path doesn't need back edge "2k <--x-- 2k+1".
  //

  vector<ll> dp(n + 2);
  dp[1] = x;
  dp[2] = x + min(x, y);
  FOR(k, 1, (n + 1) / 2) {
    ll f = dp[2 * k];
    ll g = dp[k + 1];
    dp[2 * k + 1] = min(f + x, g + y + x);
    dp[2 * k + 2] = min(f + x + x, g + y);
  }
  ll res = dp[n];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/710E/main_v2.cpp --check

// 2.3 sec
%%%% begin
10000000 1000000000 1
%%%%
8000000023
%%%% end

%%%% begin
4528217 187553422 956731625
%%%%
21178755627
%%%% end

%%%% begin
8 1 1
%%%%
4
%%%% end

%%%% begin
8 1 10
%%%%
8
%%%% end
*/
