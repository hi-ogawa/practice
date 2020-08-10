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

void mainCase() {
  int n;
  cin >> n;

  auto ps = makePrimes(n);
  int k = ps.size();
  // DD(ps);

  set<int> ps2;
  RANGE(i, 0, k) {
    RANGE(j, i + 1, k) {
      if (ps[i] * ps[j] < n) {
        ps2.insert(ps[i] * ps[j]);
      }
    }
  }
  // DD(ps2);
  // DD(ps2.size()); // <= 56

  bool res = 0;
  for (auto x : ps2) {
    for (auto y : ps2) {
      if (n == x + y) {
        // DD(tie(x, y));
        res = 1;
        break;
      }
    }
    if (res) { break; }
  }

  cout << (res ? "YES" : "NO") << endl;
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
python misc/run.py codechef/LRNDSA05/CHEFPRMS/main.cpp --check

%%%% begin
3
30
45
62
%%%%
YES
YES
NO
%%%% end

%%%% begin
1
200
%%%%

%%%% end
*/
