// AFTER EDITORIAL, AC

// NOTE: exploit insertion order so that we don't need to rely on "set".

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n; // [1, 10^6]
  cin >> n;
  vector<array<ll, 3>> ls(n);
  cin >> ls;
  sort(ALL(ls));

  using Point = array<double, 2>;
  using Line = array<ll, 2>;

  auto intersect = [](Line l1, Line l2) -> Point {
    double a1 = l1[0], b1 = l1[1];
    double a2 = l2[0], b2 = l2[1];
    assert(a1 != a2);
    double x = (b2 - b1) / (a1 - a2);
    double y = a1 * x + b1;
    return {x, y};
  };

  // ((x, y), (a, b)) <=> hull vertex at (x, y) with left edge y = a x + b
  vector<tuple<Point, Line>> hull;

  // Dummy bound at "x = 10^9 + 1"
  hull.push_back({{1e9 + 1, 0}, {0, 0}});

  auto evaluate = [&](ll x) -> ll {
    assert(x > 0);
    auto query = make_tuple(Point({(double)x, -1}), Line());
    auto it = lower_bound(hull.rbegin(), hull.rend(), query); // Reverse ordered
    assert(it != hull.rend());
    auto [a, b] = get<1>(*it);
    return a * x + b;
  };

  auto insert = [&](ll a0, ll b0) {
    assert(a0 < 0);
    assert(b0 >= 0);
    while (true) {
      auto [pt, li] = hull.back();
      auto [x, y] = pt;
      double y0 = a0 * x + b0;
      if (y0 >= y) {
        hull.pop_back();
        continue;
      }
      auto isect = intersect(Line({a0, b0}), li);
      hull.push_back({isect, {a0, b0}});
      break;
    }
  };

  vector<ll> dp(n);
  FOR(i, 0, n) {
    auto [p, q, r] = ls[i];
    ll s = evaluate(q);
    dp[i] = s + p * q - r;
    insert(-p, dp[i]);
  }

  ll res = *max_element(ALL(dp));
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1083E/main.cpp --check

%%%% begin
3
4 4 8
1 5 0
5 2 10
%%%%
9
%%%% end

%%%% begin
4
6 2 4
1 6 2
2 4 3
5 3 8
%%%%
10
%%%% end
*/
