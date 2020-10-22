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
  int n; // [2, 2 x 10^5]
  cin >> n;
  ll c; // [1, 10^12]
  cin >> c;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;

  // WLOG ls[0] = 0
  FOR(i, 1, n) { ls[i] -= ls[0]; }
  ls[0] = 0;

  //
  // PROP.
  //   Given (y, z), then
  //     f(x, (y, z)) = (x - y)^2 + c + z = (-2 y) x + (y^2 + z) + x^2 + c
  //
  //   Thus for {(yi, zi)}_i, we have
  //     argmin f(x, (yi, zi)) = argmin (- 2 yi) x + (yi^2 + zi) (= g(x))
  //

  using Real = long double;
  using vec2 = array<Real, 2>;
  const Real kInf = 1e18;

  // Ordered by isect.x
  using elem_t = pair<vec2, vec2>;
  vector<elem_t> hull; // (isect, (slope, y-intercept))

  auto evaluate = [&](Real x) -> Real {
    assert(x > 0);
    auto it = lower_bound(ALL(hull), elem_t({{x, -kInf}, {0, 0}}));
    assert(it != hull.begin());
    auto [_isect, g] = *prev(it);
    return g[0] * x + g[1];
  };

  auto insert = [&](Real a, Real b) { // (slope, y-intercept)
    assert(a < get<1>(hull.back())[0]);
    assert(b > 0);

    while (true) {
      assert(!hull.empty());
      auto [isect, g] = hull.back();
      auto y = a * isect[0] + b;
      if (y < isect[1]) {
        hull.pop_back();
        continue;
      }
      auto [aa, bb] = g;
      auto x = - (bb - b) / (aa - a);
      hull.push_back({{x, a * x + b}, {a, b}});
      break;
    }
  };

  // Initialize Hull as positive x-axis
  hull.push_back({{0, 0}, {0, 0}});

  vector<ll> dp(n);
  FOR(i, 1, n) {
    Real x = ls[i];
    Real gx = evaluate(x);
    Real z = gx + x * x + c; // = f(x)
    insert(- 2 * x, x * x + z);
    dbg(i, x, z);
    dbg2(hull);
    dp[i] = z;
  }

  ll res = dp[n - 1];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/dp/z/main.cpp

%%%% begin
5 6
1 2 3 4 5
%%%%
20
%%%% end

%%%% begin
2 1000000000000
500000 1000000
%%%%
1250000000000
%%%% end

%%%% begin
8 5
1 3 4 5 10 11 12 13
%%%%
62
%%%% end
*/
