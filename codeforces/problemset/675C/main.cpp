// WA

// NOTE: objective is not convex...

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
  int n; // [1, 10^5]
  cin >> n;
  vector<ll> ls(n); // [-10^9, 10^9]
  cin >> ls;

  // Positive sums for trivial bound of search range
  ll total = 0;
  for (auto x : ls) {
    if (x > 0) { total += x; }
  }

  //
  // PROP:
  //   f(x) = ...  is convex since each "+1" term is convex. (NO, it's NOT!!)
  //

  // f(x) = Cost when 1st bank gives "x" to the 2nd
  auto evaluate = [&](ll x) -> int {
    int res = (x != 0);
    FOR(i, 1, n) {
      x = ls[i] + x; // Pass excess/deficiency to the next
      res += (x != 0);
    }
    return res;
  };

  // debug
  dbg(ls, total);
  FOR(x, -10, 10) { dbg(x, evaluate(x)); }

  auto search = [&]() -> int {
    ll x0 = -total, x1 = total + 1; // [x0, x1)
    while (x0 + 3 <= x1) {
      ll xl = x0 + (x1 - x0) / 3;
      ll xr = x0 + (x1 - x0) / 3 * 2;
      auto fl = evaluate(xl);
      auto fr = evaluate(xr);
      dbg(x0, x1, xl, xr, fl, fr);
      if (fl < fr) {
        x1 = xr;
      } else {
        x0 = xl;
      }
    }
    auto f = evaluate(x0);
    for (ll x = x0 + 1; x < x1; x++) { // careful using FOR
      f = min(f, evaluate(x));
    }
    return f;
  };

  int res = search();
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/675C/main.cpp

%%%% begin
50
108431864 128274949 -554057370 -384620666 -202862975 -803855410 -482167063 -55139054 -215901009 0 0 0 0 0 94325701 730397219 358214459 -673647271 -131397668 -377892440 0 0 0 0 0 -487994257 -360271553 639988328 489338210 -281060728 250208758 0 993242346 -213071841 -59752620 -864351041 -114363541 506279952 999648597 -173503559 -144629749 -559693009 0 -46793577 511999017 -343503822 -741715911 647437511 821346413 993112810
%%%%
%%%% end

%%%% begin
6
1 1 0 0 -1 -1
%%%%
3
%%%% end

%%%% begin
3
5 0 -5
%%%%
1
%%%% end

%%%% begin
4
-1 0 1 0
%%%%
2
%%%% end

%%%% begin
4
1 2 3 -6
%%%%
3
%%%% end
*/
