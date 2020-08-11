// AFTER CONTEST, AC

//
// PROP.
//   Define gn = \sum_{i <= n} fi
//     where fi is fibonacci sequence [f0, f1, f2, f3, ..  ] = [0, 1, 1, 2, ..]
//   Then,
//     f(n+3) = f(n+2) + f(n+1)  <=>
//     g(n+3) - g(n+2) = g(n+2) - g(n+1) + g(n+1) - g(n)  <=>
//     g(n+3) = 2g(n+2) - g(n)
//   Thus,
//     | g(n+3) | = | 2  0 -1 | | g(n+2) |
//     | g(n+2) |   | 1  0  0 | | g(n+1) |
//     | g(n+1) |   | 0  1  0 | | g(n+0) |
//
//     | .... | = A^n | 2 |
//     | .... |       | 1 |
//     | g(n) |       | 0 |
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

// Main
constexpr ll kModulo = 1000000000 + 7;
ll madd(ll x, ll y) { return (x + y) % kModulo; }
ll mmul(ll x, ll y) { return (x * y) % kModulo; }
ll mexp(ll b, ll e) {
  ll res = 1;
  ll be = b;
  while (e > 0) {
    if (e & 1) { res = mmul(res, be); }
    be = mmul(be, be);
    e >>= 1;
  }
  return res;
}

using mat3 = array<array<ll, 3>, 3>;

// [ for debugging ]
namespace std {
  template<class ...Ts> ostream& operator<<(ostream& o, const mat3& x) {
    o << "\n{ ";
    RANGE(i, 0, 3) {
      if (i) { o << ",\n "; }
      RANGE(j, 0, 3) {
        if (j) { o << ", "; }
        o << x[i][j];
      }
    }
    o << "}";
    return o;
  }
}

mat3 mmul3(mat3 x, mat3 y) {
  mat3 z;
  RANGE(i, 0, 3) {
    RANGE(j, 0, 3) {
      ll tmp = 0;
      RANGE(k, 0, 3) {
        tmp = madd(tmp, mmul(x[i][k], y[k][j]));
      }
      z[i][j] = tmp;
    }
  }
  return z;
}

mat3 mexp3(mat3 b, ll e) {
  mat3 res = {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
  mat3 be = b;
  while (e > 0) {
    if (e & 1) { res = mmul3(res, be); }
    be = mmul3(be, be);
    e >>= 1;
  }
  return res;
}

ll fib_sum(ll n) {
  mat3 a = {{
    {2, 0, -1},
    {1, 0, 0},
    {0, 1, 0},
  }};
  mat3 b = mexp3(a, n);
  // DD(n);
  // DD(b);

  ll res = madd(2 * b[2][0], b[2][1]);
  return res;
}

void mainCase() {
  ll n, k; // <= 10^9
  cin >> n >> k;

  ll n1 = n / k;
  ll n2 = n % k;

  ll g1 = mmul(n1, fib_sum(k - 1));
  ll g2 = n2 > 0 ? fib_sum(n2 - 1) : 0;
  // DD(tie(g1, g2));

  ll res = madd(g1, g2);
  res = madd(res, kModulo); // make it positive since fib_sum matrix possibly produces negative modulo
  cout << res << endl;
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
python misc/run.py codechef/LRNDSA06/FIBNK/main.cpp --check

%%%% begin
1
20 8
%%%%
70
%%%% end

%%%% begin
1
6 3
%%%%
4
%%%% end
*/
