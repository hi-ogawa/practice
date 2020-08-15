// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
template<class T, size_t N>  istream& operator>>(istream& i, array<T, N>& x)  { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T, size_t N>  ostream& operator<<(ostream& o, const array<T, N>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n, k; // n <= 150, k <= 9
  cin >> n >> k;

  //
  // For x = ....9999d
  //         <------> b = a + 9j
  //         <--> a
  //

  auto tri = [](ll x) -> ll {
    return (x * (x + 1)) / 2;
  };

  auto makeNumber = [](ll a, ll j, ll d) -> ll {
    //  <-j-->
    // a99..99d
    stringstream s;
    s << a;
    FOR(i, 0, j) { s << "9"; }
    s << d;
    ll res;
    s >> res;
    return res;
  };

  ll kMax = numeric_limits<ll>::max();
  ll res = kMax;
  FOR(d, 0, 10) {
    if (d + k <= 9) {
      ll h = n - (tri(d + k) - tri(d - 1));
      if (h < 0) { continue; }
      if (h % (k + 1) != 0) { continue; }
      ll b = h / (k + 1);
      ll j = b / 9;
      ll a = b % 9;
      res = min(res, makeNumber(a, j, d));
    }

    if (d + k >= 10) {
      ll h = n - (tri(9) - tri(d - 1) + tri(d + k - 10) + d + k - 9);
      if (h < 0) { continue; }
      // Solve (w, j) s.t.
      //   h = 9j (10 - d) + w (k + 1)
      for (ll j = 0; j <= h; j++) {
        ll z = h - 9 * j * (10 - d);
        if (z < 0) { continue; }
        if (z % (k + 1) != 0) { continue; }
        ll w = z / (k + 1);
        ll a;
        if (w < 9) {
          a = w;
        } else {
          // a = ?99...998 with f(a) = w
          string s;
          ll q = (w - 8) / 9;
          ll r = (w - 8) % 9;
          a = makeNumber(r, q, 8);
        }
        res = min(res, makeNumber(a, j, d));
      }
    }
  }
  cout << (res == kMax ? -1 : res) << endl;
}

int main() {
  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/edu90/e/main.cpp --check

%%%% begin
1
12 1
%%%%
19
%%%% end

%%%% begin
1
42 7
%%%%
4
%%%% end

%%%% begin
7
1 0
1 1
42 7
13 7
99 1
99 0
99 2
%%%%
1
0
4
-1
599998
99999999999
7997
%%%% end
*/
