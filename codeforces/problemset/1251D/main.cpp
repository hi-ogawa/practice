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
  ll n, s;
  cin >> n >> s;
  vector<array<ll, 2>> ls(n);
  cin >> ls;

  ll m = (n + 1) / 2;
  sort(ALL(ls));

  // f(x) = true  \iff  ∃strategy s.t. median >= x
  auto evaluate = [&](ll x) -> bool {
    // S0 = { (l, r) | r < x }
    // S1 = { (l, r) | l < x <= r }
    // S2 = { (l, r) | x <= l }
    ll k1 = 0; // #S1
    ll k2 = 0; // #S2
    for (auto [l, r] : ls) {
      if (l < x && x <= r) { k1++; }
      if (x <= l) { k2++; }
    }
    if (k1 + k2 < m) { return 0; }

    ll pay = 0;

    // Pay minimum to S0 and S2
    for (auto [l, r] : ls) {
      if (l < x && x <= r) { continue; }
      pay += l;
    }

    if (k2 < m) {
      // Pay minimum or "x" to S1
      int c = 0;
      for (auto [l, r] : ls) {
        if (x <= l) { break; }
        if (c == k1 + k2 - m) { break; }
        if (l < x && x <= r) {
          pay += l;
          c++;
        }
      }
      pay += x * (m - k2);
    } else {
      // Pay minimum to S1
      for (auto [l, r] : ls) {
        if (x <= l) { break; }
        if (l < x && x <= r) {
          pay += l;
        }
      }
    }

    return pay <= s;
  };

  // max {x | f(x) = 1}
  auto search = [&]() -> ll {
    ll x0 = 0, x1 = s + 1; // [x0, x1)
    while (x0 + 1 < x1) {
      ll x = (x0 + x1) / 2;
      if (evaluate(x)) {
        x0 = x;
      } else {
        x1 = x;
      }
    }
    return x0;
  };

  ll res = search();
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1251D/main.cpp --check

%%%% begin
3
3 26
10 12
1 4
10 11
1 1337
1 1000000000
5 26
4 4
2 4
6 8
5 6
2 7
%%%%
11
1337
6
%%%% end
*/
