// CONTEST

// NOTE: Probably incorrect approach

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

using Real = double;

// Main
void mainCase() {
  int n; // [1, 100]
  cin >> n;
  vector<array<int, 2>> ls(n); // (-100, 100), distinct
  cin >> ls;

  map<int, vector<int>> _ps;
  for (auto [x, y] : ls) {
    _ps[x].push_back(y);
  }
  for (auto& [x, ys] : _ps) {
    ys.push_back(-100);
    ys.push_back(+100);
    sort(ALL(ys));
  }
  vector<pair<int, vector<int>>> ps(ALL(_ps));
  int k = ps.size();
  dbg2(ps);

  // dp(i, j) = maximum diameter to pass vertical line x = xi in between y \in [y(j), y(j+1)]

  auto& [x0, ys0] = ps[0];
  int m0 = ys0.size();
  vector<Real> dp(m0);
  FOR(j, 0, m0 - 1) {
    dp[j] = ys0[j + 1] - ys0[j];
  }

  //
  // Maximum size to pass such quadraliteral
  //
  //  (x1, yr1) ----- (x2, yr2)
  //
  //
  //  (x1, yr1) ----- (x2, yl2)
  //

  auto getDistance = [](Real x1, Real yl1, Real yr1, Real x2, Real yl2, Real yr2) -> Real {
    // TODO: no idea...
    return 0;
  };

  FOR(i, 0, k - 1) {
    auto& [x1, ys1] = ps[i];
    auto& [x2, ys2] = ps[i + 1];
    int m1 = ys1.size();
    int m2 = ys2.size();
    vector<Real> dp_next(m2 - 1);
    FOR(j2, 0, m2 - 1) {
      Real t = 0;
      Real yl2 = ys2[j2];
      Real yr2 = ys2[j2 + 1];
      FOR(j1, 0, m1 - 1) {
        Real s = dp[j1];
        Real yl1 = ys1[j1];
        Real yr1 = ys1[j1 + 1];
        s = min(s, yr2 - yl2);
        s = min(s, getDistance(x1, yl1, yr1, x2, yl2, yr2));
        t = max(t, s);
      }
      dp_next[j2] = t;
    }
    dp = dp_next;
  }

  auto res = *max_element(ALL(dp)) / 2;
  cout << setprecision(numeric_limits<Real>::digits10 + 1) << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc181/f/main.cpp

%%%% begin
2
0 -40
0 40
%%%%
40
%%%% end

%%%% begin
4
0 -10
99 10
0 91
99 -91
%%%%
50.5
%%%% end

%%%% begin
10
-90 40
20 -30
0 -90
10 -70
80 70
-90 30
-20 -80
10 90
50 30
60 -70
%%%%
33.541019662496845446
%%%% end

%%%% begin
10
65 -90
-34 -2
62 99
42 -13
47 -84
84 87
16 -78
56 35
90 8
90 19
%%%%
35.003571246374276203
%%%% end
*/
