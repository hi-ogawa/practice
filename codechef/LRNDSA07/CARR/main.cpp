// AFTER CONTEST, AC

//
// CLAIM.
//   Consider,
//     dp[k][i] = #(length i ending by color k),
//
//   then, it's easy to see recursive relation,
//     dp[k][i + 2] = ∑_{k' ≠ k} dp[k'][i + 1] + dp[k'][i]  (appending double or single different color).
//
//   BUT, by symmetry, we have,
//     dp[k][i] = dp[k'][i] for all k, k'.
//
//   therefore, we know
//     dp[k][i] = (∑_k dp[k][i]) / m.
//
//   Thus, sum-version "sum-dp[i] = ∑_k dp[k][i]" has complete
//   information about the original "dp" data,
//   with induced recursive relation,
//     sum-dp[i + 2] = (M - 1) (sum-dp[i + 1] + sum-dp[i])  (2-deg linear rec.)
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
template<class T, size_t N>  ostream& operator<<(ostream& o, const array<T, N>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Modulo
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

// Modulo matrix
template<size_t N>
using mat = array<array<ll, N>, N>;
using mat2 = mat<2>;

template<size_t N>
mat<N> mmatmul(mat<N> x, mat<N> y) {
  mat<N> z;
  RANGE(i, 0, (int)N) {
    RANGE(j, 0, (int)N) {
      z[i][j] = 0;
      RANGE(k, 0, (int)N) {
        z[i][j] = madd(z[i][j], mmul(x[i][k], y[k][j]));
      }
    }
  }
  return z;
}

template<size_t N>
mat<N> mmatexp(mat<N> b, ll e) {
  mat<N> res;
  RANGE(i, 0, (int)N) {
    RANGE(j, 0, (int)N) {
      res[i][j] = (i == j);
    }
  }
  mat<N> be = b;
  while (e > 0) {
    if (e & 1) { res = mmatmul(res, be); }
    be = mmatmul(be, be);
    e >>= 1;
  }
  return res;
}

// Main
void mainCase() {
  ll n, m; // <= 10^18
  cin >> n >> m;
  m %= kModulo;

  // [ Naive linear recursion ]
  // ll dp1 = m;
  // ll dp2 = m * m;
  // RANGE(i, 0, n - 1) {
  //   tie(dp1, dp2) = make_tuple(dp2, (m - 1) * (dp1 + dp2));
  // }
  // ll res = dp1;

  // [ Binary exponentiation ]
  mat2 a = {{{m - 1, m - 1}, {1, 0}}};
  mat2 b = mmatexp(a, n - 1);
  mat2 c = {{{mmul(m, m), 0}, {m, 0}}};
  mat2 d = mmatmul(b, c);
  // DD(a);
  // DD(b);
  // DD(d);

  ll res = d[1][0];
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
python misc/run.py codechef/LRNDSA07/CARR/main.cpp --check

%%%% begin
2
2 2
3 4
%%%%
4
60
%%%% end
*/
