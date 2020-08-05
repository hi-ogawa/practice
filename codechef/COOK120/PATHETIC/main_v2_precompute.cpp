// AFTER EDITORIAL

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
template<class ...Ts> ostream&        operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T> ostream&            operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }

// Main
vector<int> makePrimes(int n) {
  vector<bool> sieve(n + 1, 1);
  sieve[0] = sieve[1] = 0;
  RANGE(p, 2, (int)sqrt(n) + 1) {
    if (sieve[p] == 0) { continue; }
    for (int pm = p * p; pm <= n; pm += p) {
      sieve[pm] = 0;
    }
  }
  vector<int> primes(0, 0);
  RANGE(p, 0, n + 1) {
    if (sieve[p]) {
      primes.push_back(p);
    }
  }
  return primes;
}

void precompute(int n_lim, ll a_lim) {
  //
  // PROP.
  //   Define Q = ∏_{j <= π(n)} pj, then
  //     ∀k <= n. k | Q^⌊k/2⌋
  //
  // N.B.
  //   Thus it suffices to find Q = q1.q2 with q1, q2 < 2.10^18 and
  //   assign alternating value to each neighbor within tree.
  //   BUT, clearly such existence is not trivial since
  //     p1.p2...pk = 2.3...97 = 2305567963945518424753102147331756070 (37 digits)
  //   Anyway, it turned out we can find such partition.
  //

  auto primes = makePrimes(n_lim);
  int num_primes = primes.size();
  DD(num_primes); // == 25

  // Use log for easier comparision (TODO: prove precision loss is safe)
  vector<double> log_primes(num_primes, 0);
  RANGE(i, 0, num_primes) { log_primes[i] = log(primes[i]); }
  DD(primes);
  DD(log_primes);

  //
  // Brute-force subsets 2^25
  //
  double log_a_lim = log(a_lim);
  DD(log_a_lim);

  int found = -1;
  for (int b = 0; b < (1 << num_primes); b++) {
    double logq1 = 0;
    double logq2 = 0;
    RANGE(i, 0, num_primes) {
      if (b & (1 << i)) {
        logq1 += log_primes[i];
      } else {
        logq2 += log_primes[i];
      }
    }
    if (logq1 <= log_a_lim && logq2 <= log_a_lim) {
      found = b;
      break;
    }
  }

  DD(found);
  if (found == -1) {
    return;
  }

  vector<ll> ps1(0, 0);
  vector<ll> ps2(0, 0);
  ll q1 = 1;
  ll q2 = 1;
  RANGE(i, 0, num_primes) {
    int p = primes[i];
    if (found & (1 << i)) {
      q1 *= p;
      ps1.push_back(p);
    } else {
      q2 *= p;
      ps2.push_back(p);
    }
  }
  DD(q1);
  DD(q2);
  DD(ps1);
  DD(ps2);
}

int main() {
  int n_lim = 100;
  ll a_lim = 2 * 1000'000'000'000'000'000;
  precompute(n_lim, a_lim);
  return 0;
}

/*
python misc/run.py codechef/COOK120/PATHETIC/main_v2_precompute.cpp
num_primes: 25
primes: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}
log_primes: {0.693147, 1.09861, 1.60944, 1.94591, 2.3979, 2.56495, 2.83321, 2.94444, 3.13549, 3.3673, 3.43399, 3.61092, 3.71357, 3.7612, 3.85015, 3.97029, 4.07754, 4.11087, 4.20469, 4.26268, 4.29046, 4.36945, 4.41884, 4.48864, 4.57471}
log_a_lim: 42.1397
found: 65279
q1: 1416919933790871510
q2: 1627168839228008057
ps1: {2, 3, 5, 7, 11, 13, 17, 19, 29, 31, 37, 41, 43, 47, 53}
ps2: {23, 59, 61, 67, 71, 73, 79, 83, 89, 97}

%%%% begin
%%%%
%%%% end
*/
