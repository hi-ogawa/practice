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

// this solution doesn't satisfy bound "a <= 10^9"
void mainCase_v1() {
  ll n; // <= 50000
  cin >> n;

  // π(611957) = 50000
  ll p_max = 611953;
  auto ps = makePrimes(p_max);

  // Semi-primes
  vector<ll> res(n, 0);
  RANGE(i, 0, n) {
    res[i] = ps[i] * ps[(i + 1) % n];
  }

  RANGE(i, 0, n) {
    if (i) { cout << " "; }
    cout << res[i];
  }
  cout << endl;
}

// this solution doesn't satisfy "distinct" requirement
void mainCase_v2() {
  ll n; // 3 <= n <= 50000
  cin >> n;

  // Only 6 primes are needed
  vector<ll> primes = {2, 3, 5, 7, 11, 13};

  // Generate semi-primes of 3 period
  //   (p1.p2), (p2.p3), (p3.p1), ...
  // BUT, take care when it comes back to circle without complete period by e.g.
  //   (p1.p2), (p2.p3), (p3.p4), (p4.p5), (p5.p6), (p6.p1), (p1, p2)
  vector<ll> res(n, 0);
  RANGE(i, 0, n) {
    // Nice periodic case (i.e. n = 0 \in Z3)
    res[i] = primes[(i % 3)] * primes[(i + 1) % 3];
  }

  // Fix up for non-complete period cases
  if (n % 3 != 0) {
    ll m = n - 3 - (n % 3);
    ll l = n - m; // \in {1, 2, 4, 5}
    // DD(tie(n, m, l));
    RANGE(i, 0, l) {
      res[m + i] = primes[i] * primes[(i + 1) % l];
    }
  }

  RANGE(i, 0, n) {
    if (i) { cout << " "; }
    cout << res[i];
  }
  cout << endl;
}

// In order to avoid TLE for multiple test cases
vector<ll> precomputed_primes(0, 0);
void precompute() {
  precomputed_primes = makePrimes(1000000);
}

void mainCase() {
  ll n; // 3 <= n <= 50000
  cin >> n;

  // 6 primes for periodic parts and more primes for making them distinct
  // (we'll use 50000 + 6 primes)
  // (π(10^6) = 78498)
  // vector<ll> primes = makePrimes(1000000);
  auto& primes = precomputed_primes; // For multiple small test cases

  // Periodic construction as in mainCase_v2
  vector<ll> res(n, 0);
  RANGE(i, 0, n) {
    // Nice periodic case (i.e. n = 0 \in Z3)
    res[i] = primes[(i % 3)] * primes[(i + 1) % 3];
  }
  if (n % 3 != 0) {
    ll m = n - 3 - (n % 3);
    ll l = n - m; // \in {1, 2, 4, 5}
    RANGE(i, 0, l) {
      res[m + i] = primes[i] * primes[(i + 1) % l];
    }
  }

  // Multiply factor to make them distinct
  RANGE(i, 0, n) {
    res[i] *= primes[i + 6];
  }

  RANGE(i, 0, n) {
    if (i) { cout << " "; }
    cout << res[i];
  }
  cout << endl;
}

int main() {
  // Precompute primes
  precompute();

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
python misc/run.py codechef/LRNDSA05/EARTSEQ/main.cpp --check

%%%% begin
2
3
4
%%%%
6 10 15
374 595 1365 858
%%%% end

%%%% begin
1
50000
%%%%
???
%%%% end
*/
