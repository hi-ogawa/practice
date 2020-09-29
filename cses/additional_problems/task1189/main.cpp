// AC

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
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> ls1(n), ls2(n); // [0, 10^6]
  cin >> ls1 >> ls2;

  // WLOG zero sum
  vector<int> ls(n);
  FOR(i, 0, n) { ls[i] = ls1[i] - ls2[i]; }
  assert(accumulate(ALL(ls), (ll)0) == 0);

  ll total_p = 0, total_n = 0;
  FOR(i, 0, n) {
    (ls[i] > 0 ? total_p : total_n) += abs(ls[i]);
  }
  dbgv(total_p, total_n);
  assert(total_p == total_n);

  //
  // CLAIM.
  //   1. Once accepted food from left, it's not optimal to return back to left. (same holds for "right")
  //   2. Thus, optimal strategy is
  //      - "a1" gives "x" to the right (where "x" can be negative.)
  //      - then, others follow by satisfying their needs.
  //   3. We can search minimal out of such strategies.
  //
  // PROP.
  //   f(x) = |x| + |a2 + x| + |a3 + a2 + x| + ... + |a_n + .. + a2 + x| : Convex
  //   TODO: maybe median is closed form solution?
  //

  // f(x)
  auto evaluate = [&](ll x) -> ll {
    ll res = abs(x);
    ll y = x;
    FOR(i, 1, n) {
      y += ls[i];
      res += abs(y);
    }
    return res;
  };

  FOR(x, -3, 3) {
    dbgv(100 * x, evaluate(100 * x));
  }

  // Search convex minimum (cf. cses/sorting_and_searching/task1074/main_v2.cpp)
  auto search = [&]() -> ll {
    // [x0, x1)
    ll x0 = - total_n;
    ll x1 = total_p + 1;
    while (x0 + 3 <= x1) {
      ll x2 = x0 + (x1 - x0) / 3;
      ll x3 = x0 + (x1 - x0) / 3 * 2;
      ll f2 = evaluate(x2);
      ll f3 = evaluate(x3);
      dbgv(x0, x1, x2, x3, f2, f3);
      if (f2 < f3) {
        x1 = x3;
      } else {
        x0 = x2;
      }
    }
    ll x2 = (x0 + x1) / 2;
    ll f0 = evaluate(x0);
    ll f2 = evaluate(x2);
    dbgv(x0, x1, x2, f0, f2);
    return min(f0, f2);
  };

  ll res = search();
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1189/main.cpp --check

%%%% begin
5
2 1 1 1 0
0 0 0 0 5
%%%%
7
%%%% end

%%%% begin
3
3 5 0
2 4 2
%%%%
2
%%%% end
*/
