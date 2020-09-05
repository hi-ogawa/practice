// AFTER EDITORIAL, AC

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
  ll a, b, c; // [0, 2 10^9]
  cin >> a >> b >> c;
  {
    // a >= b >= c
    array<ll, 3> tmp = {a, b, c};
    sort(ALL(tmp));
    a = tmp[2], b = tmp[1], c = tmp[0];
  }

  // Clearly unsuable ballons "a - 2 * (b + c)"
  if (a > 2 * (b + c)) {
    a = 2 * (b + c);
  }

  //
  // PROP.
  //   Minimum unused ballons "s = (a + b + c) % 3" is achievable.
  //

  ll res = 0;
  if (a > b && b > c) {
    ll aa = a - c, bb = b - c;
    if (aa > 2 * bb) { // -> a > b = c
      a -= 2 * bb;
      b -= bb;
      res += bb;
    }
    if (aa <= 2 * bb) { // -> a = b > c
      ll d = aa - bb;
      a -= 2 * d;
      b -= d;
      res += d;
    }
  }

  if (a == b && b > c) {
    ll aa = a - c;
    dbgv(a, b, c, aa, aa % 3);
    if (aa % 3 == 0) { // -> (c, c, c)
      res += 2 * (aa / 3);
      a -= aa;
      b -= aa;
    }
    if (aa % 3 == 1) { // -> (c + 1, c + 1, c)
      res += 2 * (aa / 3);
      a -= aa - 1;
      b -= aa - 1;
    }
    if (aa % 3 == 2) { // -> (c + 1, c, c)
      res += 2 * (aa / 3);
      a -= aa - 2;
      b -= aa - 2;
      res += 1;
      a -= 1;
      b -= 2;
    }
  }

  if (a > b && b == c) { // -> (s, 0, 0)
    ll aa = a - c;
    assert(aa <= 3 * c);

    ll d = c - aa / 3;
    res += d;
    a -= d;
    b -= d;
    c -= d;
    res += b;
    a -= 2 * b;
    b -= b;
    res += c;
    a -= 2 * c;
    c -= c;
  }
  dbgv(a, b, c);

  res += c;
  a -= c; b -= c; c -= c;

  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py codeforces/problemset/478C/main.cpp --check

%%%% begin
1463615122 1988383731 837331500
%%%%
%%%% end

%%%% begin
5 4 3
%%%%
4
%%%% end
*/
