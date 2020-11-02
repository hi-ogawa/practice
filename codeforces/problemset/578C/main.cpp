// WIP

// NOTE: It seems "solveMaxSumSegment" is too slow.

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

// TODO: This seems overkill but this is needed to handle "0 0 ... 0" case
using Real = long double;
const Real kEps = 1e-14;
const Real kInf = 1e18;

// Main
void mainCase() {
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [-10^4, 10^4]
  cin >> ls;

  // Cum sum
  vector<ll> ps(n + 1);
  FOR(i, 0, n) { ps[i + 1] = ps[i] + ls[i]; }

  // Max sum segment with paremeters to take care of max/min cases
  vector<Real> qs(n + 1);
  auto solveMaxSumSegment = [&](Real c, Real x) -> Real {
    // Kadane's DP
    Real dp = 0, res = -kInf;
    FOR(i, 0, n) {
      Real t = c * (ls[i] + x);
      dp = max(dp + t, Real(0));
      res = max(res, dp);
    }
    return res;
  };

  // f(x) = max abs(size(seg) x + sum(seg))  (convex)
  auto evaluate = [&](Real x) -> Real {
    auto res1 = solveMaxSumSegment(+1, -x);
    auto res2 = solveMaxSumSegment(-1, -x);
    return max(res1, res2);
  };

  // Find min f(x)
  auto search = [&]() -> Real {
    // [x0, x1)
    Real x0 = *min_element(ALL(ls)) - 1;
    Real x1 = *max_element(ALL(ls)) + 1;
    while (x1 - x0 > kEps) {
      dbg(x0, x1);
      auto l = x0 + (x1 - x0) / 3;
      auto r = x0 + (x1 - x0) / 3 * 2;
      auto fl = evaluate(l);
      auto fr = evaluate(r);
      if (fl < fr) {
        x1 = r;
      } else {
        x0 = l;
      }
    }
    return x0;
  };

  auto res1 = search();
  auto res2 = evaluate(res1);
  dbg(res1, res2);
  cout << fixed << setprecision(10) << res2 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/578C/main.cpp

%%%% begin
3
1 2 3
%%%%
1.000000000000000
%%%% end

%%%% begin
4
1 2 3 4
%%%%
2.000000000000000
%%%% end

%%%% begin
10
1 10 2 9 3 8 4 7 5 6
%%%%
4.500000000000000
%%%% end
*/
