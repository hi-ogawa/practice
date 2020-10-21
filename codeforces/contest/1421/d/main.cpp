// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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
  ll x, y; // [-10^9, 10^9]
  array<ll, 6> c; // [1, 10^9]
  cin >> x >> y >> c;

  // Misread coordinate system...
  swap(x, y);

  // Cost of going 8 directions
  //    5 0
  //  4 @ 1
  //  3 2

  map<array<int, 2>, ll> d;
  d[{ 1,  1}] = c[0];
  d[{ 1,  0}] = c[1];
  d[{ 0,  1}] = c[5];
  d[{-1, -1}] = c[3];
  d[{-1,  0}] = c[4];
  d[{ 0, -1}] = c[2];

  d[{1, 1}] = min(d[{1, 1}], d[{1, 0}] + d[{0,  1}]);
  d[{1, 0}] = min(d[{1, 0}], d[{1, 1}] + d[{0, -1}]);
  d[{0, 1}] = min(d[{0, 1}], d[{1, 1}] + d[{-1, 0}]);
  d[{-1, -1}] = min(d[{-1, -1}], d[{-1, 0}] + d[{0, -1}]);
  d[{-1,  0}] = min(d[{-1,  0}], d[{-1, -1}] + d[{0, 1}]);
  d[{ 0, -1}] = min(d[{ 0, -1}], d[{-1, -1}] + d[{1, 0}]);
  dbg2(d);

  ll res = 0;
  auto solve = [&]() {
    if (x >= 0 && y >= 0) {
      ll z = min(x, y);
      res += z * d[{1, 1}];
      x -= z; y -= z;
      if (x) { res += x * d[{1, 0}]; }
      if (y) { res += y * d[{0, 1}]; }
      return;
    }
    if (x <= 0 && y <= 0) {
      x = abs(x); y = abs(y);
      ll z = min(x, y);
      res += z * d[{-1, -1}];
      x -= z; y -= z;
      if (x) { res += x * d[{-1,  0}]; }
      if (y) { res += y * d[{ 0, -1}]; }
      return;
    }
    if (x <= 0 && y >= 0) {
      x = abs(x); y = abs(y);
      res += x * d[{-1, 0}];
      res += y * d[{ 0, 1}];
      return;
    }
    if (x >= 0 && y <= 0) {
      x = abs(x); y = abs(y);
      res += x * d[{1,  0}];
      res += y * d[{0, -1}];
      return;
    }
    assert(0);
  };
  solve();

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
python misc/run.py codeforces/contest/1421/d/main.cpp

%%%% begin
2
-3 1
1 3 5 7 9 11
1000000000 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
%%%%
18
1000000000000000000
%%%% end
*/
