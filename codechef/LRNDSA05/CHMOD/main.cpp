// AFTER CONTEST, AC

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
ll mmul(ll x, ll y, ll m) { return (x * y) % m; }
ll mexp(ll b, ll e, ll m) {
  ll res = 1;
  ll be = b;
  while (e > 0) {
    if (e & 1) { res = (res * be) % m; }
    be = (be * be) % m;
    e >>= 1;
  }
  return res;
}

vector<ll> makePrimes(ll n) {
  vector<bool> a(n + 1, 1);
  a[0] = a[1] = 0;
  RANGE(p, 2, sqrt(n) + 1) {
    if (a[p] == 0) { continue; }
    for (ll q = p * p; q <= n; q += p) {
      a[q] = 0;
    }
  }
  vector<ll> res;
  RANGE(i, 0, n + 1) {
    if (a[i]) {
      res.push_back(i);
    }
  }
  return res;
}

void mainCase() {
  // Input
  ll n; // <= 10^5
  cin >> n;

  vector<ll> ls(n, 0); // <= 100
  cin >> ls;

  ll nq; // <= 10^5
  cin >> nq;

  vector<tuple<ll, ll, ll>> qs(nq, {0, 0, 0}); // mod <= 10^9
  RANGE(i, 0, nq) { cin >> get<0>(qs[i]) >> get<1>(qs[i]) >> get<2>(qs[i]); }

  // Precompute prime exponents
  auto primes = makePrimes(100);
  ll np = primes.size(); // = 25

  vector<vector<ll>> exponents(np, vector<ll>(n, 0));
  RANGE(i, 0, np) {
    ll p = primes[i];
    RANGE(j, 0, n) {
      ll e = 0;
      while (ls[j] % p == 0) {
        ls[j] /= p;
        e++;
      }
      exponents[i][j] = e;
    }
  }
  // DD(primes);
  // DD(exponents);

  // Cumulative sum (exploit additive property of prime valuation)
  vector<vector<ll>> cumsum(np, vector<ll>(n + 1, 0));
  RANGE(i, 0, np) {
    RANGE(j, 0, n) {
      cumsum[i][j + 1] = cumsum[i][j] + exponents[i][j];
    }
  }
  // DD(cumsum);

  // Answer queries
  for (auto q : qs) {
    ll l, r, m;
    tie(l, r, m) = q;
    l--; // Zero-based index, half-open [l, r)

    ll res = 1;
    RANGE(i, 0, np) {
      ll p = primes[i];
      ll e = cumsum[i][r] - cumsum[i][l];
      res = mmul(res, mexp(p, e, m), m);
    }
    cout << res << endl;
  }
}

int main() {
  // [ Single case ]
  mainCase();
  return 0;

  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // RANGE(i, 0, t) mainCase();
  // return 0;
}

/*
python misc/run.py codechef/LRNDSA05/CHMOD/main.cpp --check

%%%% begin
5
1 2 3 4 5
4
1 2 3
2 3 4
1 1 1
1 5 1000000000
%%%%
2
2
0
120
%%%% end
*/
