// WIP

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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  ll a, b, m; // [0, 10^9]
  cin >> a >> b >> m;

  auto totient = [](ll x) -> ll {
    ll y = x;
    for (ll p = 2; p * p <= x; p++) {
      if (x % p) { continue; }
      while (x % p == 0) { x /= p; }
      y = (y / p) * (p - 1);
    }
    if (x > 1) { y = (y / x) * (x - 1); }
    return y;
  };

  auto pow = [](ll x, ll e, ll m) -> ll {
    ll y = 1 % m;
    while (e > 0) {
      if (e & 1) { y = (y * x) % m; }
      e >>= 1;
      x = (x * x) % m;
    }
    return y;
  };

  function<ll(ll, ll, ll)> tetration = [&](ll a, ll b, ll m) -> ll {
    if (m == 1) { return 0; }
    if (a == 0) { return 1 - b % 2; }
    if (b == 0) { return 1; }
    if (b == 1) { return a % m; }
    if (b == 2) { return pow(a, a, m); }
    if (b == 3) {}
    ll tm = totient(m);
    return pow(a, tetration(a, b - 1, tm) + tm, m);
  };

  auto res = tetration(a, b, m);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 10^3]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py library_checker/tetration_mod/main_v2.cpp

%%%% begin
10
0 0 10
0 1 10
1 0 10
1 1 10
7 3 10
1 3 33
998 244 353
998244353 1333 1000000000
998244353 998244353 1333
1000000000 1000000000 133333
%%%%
1
0
1
1
3
1
140
998121473
170
94527
%%%% end

%%%% begin
10
2 2 1
2 2 2
2 2 3
2 2 4
2 2 5
3 3 1
3 3 2
3 3 3
3 3 4
3 3 5
%%%%
0
0
1
0
4
0
1
0
3
2
%%%% end
*/
