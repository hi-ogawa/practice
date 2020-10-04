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
  int n, k; // n \in [2, 2 x 10^5], k in [1, 10]
  cin >> n >> k;
  vector<array<int, 2>> ls(k);
  cin >> ls;

  const ll modulo = 998244353;
  auto _mod  = [&](ll x) { if (x >= modulo) { x -= modulo; }; return x; };
  auto add   = [&](ll x, ll y) { return _mod(x + y); };
  auto addeq = [&](ll&x, ll y) { return x = add(x, y); };
  auto subeq = [&](ll&x, ll y) { return x = add(x, - y + modulo); };

  // Difference array and its summation simultaneously
  vector<ll> dp(n + 1);
  FOR(i, 1, n + 1) {
    // Sum difference
    addeq(dp[i], dp[i - 1]);
    ll t = i == 1 ? 1 : dp[i];

    // Update difference array
    for (auto [l, r] : ls) {
      if (i + l <= n)     { addeq(dp[i + l], t); }
      if (i + r + 1 <= n) { subeq(dp[i + r + 1], t); }
    }
  }
  dbg(dp);

  ll res = dp[n];
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc179/d/main.cpp --check

%%%% begin
5 2
1 1
3 4
%%%%
4
%%%% end

%%%% begin
5 2
3 3
5 5
%%%%
0
%%%% end

%%%% begin
5 1
1 2
%%%%
5
%%%% end

%%%% begin
60 3
5 8
1 3
10 15
%%%%
221823067
%%%% end
*/
