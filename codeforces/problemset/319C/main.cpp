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
  int n; // [1, 10^5]
  cin >> n;
  vector<ll> ls1(n), ls2(n); // ls1 : incr, ls2 : decr  [0, 10^9]
  cin >> ls1 >> ls2;

  // f(1) = 0
  // f(i) = min_{j < i} b(j).a(i) + f(j)  (NOTE: b(j) decreasing wrt j)

  using Real = long double;
  using elem_t = array<Real, 4>; // (x, y, a, b) where vertex (x, y) with the line a x + y
  vector<elem_t> hull;

  auto evaluate = [&](Real x0) -> Real {
    assert(x0 > 0);
    elem_t query = {x0, -1};
    auto it = upper_bound(ALL(hull), query);
    assert(it != hull.begin());
    auto [x, y, a, b] = *prev(it);
    return a * x0 + b;
  };

  auto insert = [&](Real a0, Real b0) {
    while (true) {
      assert(!hull.empty());
      auto [x, y, a, b] = hull.back();
      if (a0 * x + b0 <= y) {
        hull.pop_back();
        continue;
      }
      assert(a != a0);
      auto x0 = - (b - b0) / (a - a0);
      auto y0 = a0 * x0 + b0;
      hull.push_back({x0, y0, a0, b0});
      break;
    }
  };

  // Initialize
  vector<ll> dp(n);
  hull.push_back({0, 1, Real(ls2[0]), 0});

  FOR(i, 1, n) {
    Real a = ls1[i], b = ls2[i];
    dbg(hull);
    auto f = evaluate(a);
    dbg(i, a, b, f);
    insert(b, f);
    dp[i] = (ll)round(f);
  }

  auto res = dp[n - 1];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/319C/main.cpp

%%%% begin
5
1 2 3 4 5
5 4 3 2 0
%%%%
25
%%%% end

%%%% begin
6
1 2 3 10 20 30
6 5 4 3 2 0
%%%%
138
%%%% end
*/
