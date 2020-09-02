// WA

// TODO: theory is right, but requires more than int64 (cf. main.py)

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
  ll n, p, w, d;
  cin >> n >> p >> w >> d;

  ll g = gcd(w, d);
  if (p % g != 0) { cout << -1 << endl; return; }

  // WLOG gcd(w, d) = 1
  w /= g; d /= g; p /= g;
  dbgv(n, p, w, d);

  // Solve Bezout identity a x + b y = 1
  auto solveBezout = [](ll x, ll y) -> tuple<ll, ll> {
    ll c1 = x, c2 = y; // x >= y
    ll a1 = 1, a2 = 0, b1 = 0, b2 = 1;
    while (c2 != 0) {
      ll q = c1 / c2, r = c1 % c2;
      tie(a1, a2) = make_tuple(a2, a1 - q * a2);
      tie(b1, b2) = make_tuple(b2, b1 - q * b2);
      tie(c1, c2) = make_tuple(c2, r);
    }
    return {a1, b1};
  };
  auto [a, b] = solveBezout(w, d);

  auto divCeil = [](ll x, ll y) { return (x + y - 1) / y; };

  // Find min y >= 0  s.t. x w + y d = p
  // TODO: large multiplication fails here
  ll x = p * a; // + s d
  ll y = p * b; // - s w
  dbgv(a, b, x, y);
  if (y < 0) {
    ll s = divCeil(-y, w);
    x -= s * d;
    y += s * w;
  }
  if (y >= 0) {
    ll s = y / w;
    x += s * d;
    y -= s * w;
  }
  dbgv(x, y);

  if (x < 0 || x + y > n) { cout << -1 << endl; return; }
  ll z = n - (x + y);
  cout << x << " " << y << " " << z << endl;
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
python misc/run.py codeforces/problemset/1244C/main.cpp --check

%%%% begin
627936103814 4254617095171609 45205 1927
%%%%
%%%% end

%%%% begin
30 60 3 1
%%%%
17 9 4
%%%% end

%%%% begin
10 51 5 4
%%%%
-1
%%%% end

%%%% begin
20 0 15 5
%%%%
0 0 20
%%%% end
*/
