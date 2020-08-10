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
vector<int> makePrimes(int n) {
  vector<bool> a(n + 1, 1);
  a[0] = a[1] = 0;
  RANGE(p, 2, sqrt(n) + 1) {
    if (a[p] == 0) { continue; }
    for (ll q = p * p; q <= n; q += p) {
      a[q] = 0;
    }
  }
  vector<int> res;
  RANGE(i, 0, n + 1) {
    if (a[i]) {
      res.push_back(i);
    }
  }
  return res;
}

void mainCase() {
  ll n; // <= 10000
  cin >> n;
  vector<int> ls(n, 0); // <= 10000
  cin >> ls;

  // Make it increasing
  ll res_incr = 0;
  RANGE(i, 1, n) {
    if (ls[i] < ls[i - 1]) {
      res_incr += ls[i - 1] - ls[i];
      ls[i] = ls[i - 1];
    }
  }

  // Get factors
  int max_ls = *max_element(ALL(ls));
  auto primes = makePrimes(max_ls);
  ll np = primes.size();

  // Find minimum
  ll res_gcd = n;
  RANGE(i, 0, np) {
    ll tmp = 0;
    int p = primes[i];
    RANGE(j, 0, n) {
      int r = ls[j] % p;
      if (r > 0) {
        tmp += p - r;
      }
    }
    // DD(tie(p, tmp));
    res_gcd = min(res_gcd, tmp);
  }

  // DD(tie(res_incr, res_gcd));
  ll res = res_incr + res_gcd;
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
python misc/run.py codechef/LRNDSA05/CBALLS/main.cpp --check

%%%% begin
1
3
11 13 15
%%%%
3
%%%% end
*/
