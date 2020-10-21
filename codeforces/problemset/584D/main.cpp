// AFTER EDITORIAL, AC

// Cf. Goldbach conjecture

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

array<int, 2> goldbach(int n) {
  assert(n >= 4 && n % 2 == 0);
  auto isPrime = [](int x) -> bool {
    for (int y = 2; y <= sqrt(x); y++) {
      if (x % y == 0) { return 0; }
    }
    return 1;
  };
  if (isPrime(n - 2)) {
    return {2, n - 2};
  }
  for (int p = 3; ; p += 2) {
    if (isPrime(p) && isPrime(n - p)) {
      return {p, n - p};
    }
  }
  assert(0);
}

// Main
void mainCase() {
  int n; // [3, 10^9]
  cin >> n;

  if (n == 3 || n == 5) {
    cout << 1 << endl;
    cout << n << endl;
    return;
  }

  auto [p, q] = goldbach(n - 3);
  cout << 3 << endl;
  cout << 3 << " " << p << " " << q << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/584D/main.cpp --check

%%%% begin
999999999
%%%%
3
3 59 999999937
%%%% end

%%%% begin
27
%%%%
3
5 11 11
%%%% end
*/
