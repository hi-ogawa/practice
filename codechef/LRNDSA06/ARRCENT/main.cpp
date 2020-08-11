// AFTER EDITORIAL, AC

//
// Cf. STROPR/main.cpp for theory (3-simplex number = 4-cumsum coefficient)
//
// PROP.
//   ∑_{k <= d} binom(k, 2)
//       = ∑_{k <= d} S(k - 1, 2)
//       = S(d - 1, 3) (i.e. tetrahedron number)
//

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Modulo routines
constexpr ll kModulo = 1000000000 + 7;
ll madd(ll x, ll y) { return (x + y) % kModulo; }
ll mmul(ll x, ll y) { return (x * y) % kModulo; }
ll mexp(ll b, ll e) {
  ll res = 1;
  ll be = b;
  while (e > 0) {
    if (e & 1) { res = (res * be) % kModulo; }
    be = (be * be) % kModulo;
    e >>= 1;
  }
  return res;
}
ll minv(ll x) { return mexp(x, kModulo - 2); } // Zp* inverse

// Main
void mainCase() {
  ll n; // <= 10^5
  cin >> n;

  vector<ll> ls(n, 0); // <= 10^6
  cin >> ls;

  // 3-simplex number = 4-cumsum coefficient
  vector<ll> left = ls;
  vector<ll> right = ls;
  RANGE(k, 0, 4) {
    RANGE(i, 1, n) {
      // [ non modulo op ]
      // left[i] += left[i - 1];
      // right[n - 1 - i] += right[n - i];
      left[i] = madd(left[i], left[i - 1]);
      right[n - 1 - i] = madd(right[n - 1 - i], right[n - i]);
    }
    // DD(left);
    // DD(right);
  }

  vector<ll> res(n, 0);
  RANGE(i, 0, n) {
    // [ non modulo op ]
    // if (0 <= i - 1) res[i] += left[i - 1];
    // if (i + 1 < n)  res[i] += right[i + 1];
    if (0 <= i - 1) res[i] = madd(res[i], left[i - 1]);
    if (i + 1 < n)  res[i] = madd(res[i], right[i + 1]);
  }

  RANGE(i, 0, n) {
    if (i) cout << " ";
    cout << res[i];
  }
  cout << endl;
}

int main() {
  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA06/ARRCENT/main.cpp --check

%%%% begin
2
5
1 1 1 1 1
5
2 6 4 2 3
%%%%
35 16 10 16 35
102 44 28 51 118
%%%% end
*/
