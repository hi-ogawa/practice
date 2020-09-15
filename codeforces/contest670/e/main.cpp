// WA

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

vector<int> makePrimes(int n) {
  vector<bool> sieve(n + 1, 1);
  for (int p = 2; p <= sqrt(n); p++) {
    if (!sieve[p]) { continue; }
    for (int x = p * p; x <= n; x += p) {
      sieve[x] = 0;
    }
  }
  vector<int> res;
  for (int x = 2; x <= n; x++) {
    if (sieve[x]) { res.push_back(x); }
  }
  return res;
}

// Main
void mainCase() {
  int n; // [1, 10^5]  (p_9592 = 99991)
  cin >> n;

  auto ask = [](int x) -> bool {
    int k1, k2;
    cout << "B " << x << endl;;
    cin >> k1;
    cout << "A " << x << endl;;
    cin >> k2;
    return k2 == 1;
  };

  auto primes = makePrimes(n);
  auto rng = mt19937((ull)&mainCase);
  shuffle(ALL(primes), rng);

  int res = 1;
  for (auto p : primes) {
    if (res * p > n) { continue; }

    ll pe = p;
    while (pe <= n) { pe *= p; }
    pe /= p;

    while (pe != 1) {
      bool b = ask(pe);
      if (b) {
        res *= pe;
        break;
      }
      pe /= p;
    }
  }
  cout << "C " << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest670/e/main.cpp --check
*/
