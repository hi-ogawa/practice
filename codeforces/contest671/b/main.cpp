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
  ll x; // [1, 10^18]
  cin >> x;

  //
  // PROP.
  //   n : nice <= n = 2^k - 1
  //   PROOF
  //     Tri(2^k - 1)
  //       = 2^(k-1) (2^k - 1)
  //       = 2^(k-1) (2^0 + 2^1 + .. + 2^(k-1))
  //       = 2^0 . 2^(k-1) + 2^2 . 2^(k-2) + 2^4 . 2^(k-3) + ..
  //
  // CONJ. (TODO)
  //   n : nice  => n = 2^k - 1
  //

  auto tri = [](ll n) -> ll { return (n * (n + 1)) / 2; };

  vector<ll> nice_tris;
  ll y = 1;
  while (tri(y) <= x) {
    nice_tris.push_back(tri(y));
    y = (y << 1) | 1;
  }
  dbg(nice_tris);

  ll res = 0;
  for (auto t : nice_tris) {
    if (x < t) { break; }
    x -= t;
    res++;
  }
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
python misc/run.py codeforces/contest671/b/main.cpp --check

%%%% begin
4
1
8
6
1000000000000000000
%%%%
1
2
1
30
%%%% end
*/
