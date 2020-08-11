// AFTER EDITORIAL, AC

//
// DEF. [Simplex number]
//   S(k | 0) = 1
//   S(k | n + 1) = ∑_{l ≤ k} S(l | n) = S(k | n) + S(k - 1 | n + 1)  (aka. cumulative sum)
//
//
// PROP.
//   S(k | n) = binom(k + n - 1, n)
//
//   PROOF.
//     By induction.
//     1. Base step
//       For any n, we have S(1 | n) = s(1 | 0) = 1 = binom(1 + n - 1, n)
//
//     2. Inductive step
//       S(k + 1 | n + 1)
//         = S(k + 1 | n) + S(k | n + 1)
//         = binom(k + n, n) + binom(k + n, n + 1)  (∵ IH)
//         = binom(k + n + 1, n + 1)  (∵ usual binom equation)
//         = binom((k + 1) + (n + 1) - 1, n + 1)
//
//
// PROP. [Iterated cumulative sum]
//   For [A1, A2, .., An], M-iterated cumulative sum B(M) is:
//     B(M) = ∑_{i: 1..n} S(i | M - 1) A(n + 1 - i)
//          = ∑_{i: 1..n} binom(i + M - 2, M - 1) A(n + 1 - i)
//
//   PROOF. you see similar cumulative sum relation as Simplex number.
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
    if (e & 1) { res = mmul(res, be); }
    be = mmul(be, be);
    e >>= 1;
  }
  return res;
}
ll minv(ll x) { return mexp(x, kModulo - 2); } // Zp* inverse

// Main
void mainCase() {
  ll n, x, m;
  cin >> n >> x >> m;
  // x <= n <= 10^5
  // m <= 10^18

  vector<ll> ls(n, 0); // <= 10^18
  cin >> ls;

  // AFTER EDITORIAL (mmul's argument has to be small already)
  ll m_modulo = m % kModulo;
  RANGE(i, 0, n) {
    ls[i] %= kModulo;
  }

  // DD(tie(n, x, m));
  // DD(ls);

  // Answer = ∑_{i: 1..x} binom(i + M - 2, i - 1) A(x + 1 - i)

  // Precompute binom
  vector<ll> binoms(x, 0); // binom(m - 1, 0), binom(m, 1), .. binom(m + x - 2, x - 1)
  binoms[0] = 1;
  RANGE(i, 1, x) {
    binoms[i] = mmul(binoms[i - 1], mmul(m_modulo - 1 + i, minv(i)));
  }

  ll res = 0;
  RANGE(i, 1, x + 1) {
    res = madd(res, mmul(binoms[i - 1], ls[x - i]));
  }
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
python misc/run.py codechef/LRNDSA06/STROPR/main.cpp --check

%%%% begin
1
4 4 2
1 2 3 4
%%%%
20
%%%% end

%%%% begin
1
4 4 4
1 2 3 4
%%%%
56
%%%% end

%%%% begin
1
3 1 10000
1 2 3
%%%%
1
%%%% end

%%%% begin
1
3 3 1
1 2 3
%%%%
6
%%%% end

%%%% begin
2
3 2 3
1 2 3
3 3 3
1 2 3
%%%%
5
15
%%%% end
*/
