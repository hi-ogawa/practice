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

// Modulo op
constexpr ll modulo = 1000000000 + 7;
ll madd(ll x, ll y) { return (x + y) % modulo; }
ll mmul(ll x, ll y) { return (x * y) % modulo; }
ll mexp(ll x, ll e) {
  ll res = 1;
  while (e > 0) {
    if (e & 1) { res = mmul(res, x); }
    e >>= 1; x = mmul(x, x);
  }
  return res;
}

// Main
void mainCase() {
  int n; // <= 10^6
  cin >> n;
  vector<array<ll, 2>> ls(n);
  cin >> ls;

  int cnt0 = 0;
  map<array<ll, 2>, array<int, 2>> cnts;
  for (auto [x, y] : ls) {
    // Special case
    if (x == 0 && y == 0) { cnt0++; continue; }

    // To normal form (y > 0) or (y == 0 and x > 0)
    if (y < 0) { x *= -1, y *= -1; }
    if (y == 0 && x < 0) { x *= -1; }

    ll g = gcd(x, y);
    x /= g; y /= g;
    if (x > 0) {
      cnts[{x, y}][0]++;
    } else {
      cnts[{y, -x}][1]++;
    }
  }
  dbg(cnts);

  ll res = 1;
  for (auto [_k, v01] : cnts) {
    auto [v0, v1] = v01;
    // Subset out of (x, y) and (-y, x)
    ll u0 = mexp(2, v0);
    ll u1 = mexp(2, v1);
    ll u = madd(u0, madd(u1, -1)); // remove doubly empty case
    res = mmul(res, u); // DP
    dbgv(u0, u1, u, res);
  }
  res = madd(res, cnt0); // put only one of (0, 0)
  res = madd(res, -1); // remove empty case
  res = madd(res, modulo); // to positive
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
python misc/run.py atcoder/abc168/e/main.cpp --check

%%%% begin
3
1 2
-1 1
2 -1
%%%%
5
%%%% end
*/
