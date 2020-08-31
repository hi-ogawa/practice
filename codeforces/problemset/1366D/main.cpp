// AC

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

// Main
void mainCase() {
  int n; // <= 10^6
  cin >> n;
  vector<int> ls(n, 0); // <= 10^7
  cin >> ls;

  // Precompute factors
  int k = *max_element(ALL(ls));
  vector<bool> sieve(k + 1, 1);
  vector<int> cnts(k + 1, 0);
  vector<int> factor(k + 1); // save only first factor
  for (int p = 2; p <= k; p++) {
    if (!sieve[p]) { continue; }
    for (int x = p; x <= k; x += p) {
      sieve[x] = 0;
      cnts[x]++;
      if (cnts[x] == 1) { factor[x] = p; }
    }
  }
  dbg(cnts);
  dbg(factor);

  vector<array<int, 2>> res(n);
  FOR(i, 0, n) {
    int x = ls[i];
    if (cnts[x] == 1) {
      res[i] = {-1, -1};
      continue;
    }
    int p = factor[x];
    int y = x;
    while (y % p == 0) { y /= p; }
    res[i] = {y, x / y};
  }
  dbg(res);

  FOR(i, 0, n) {
    if (i) cout << " ";
    cout << res[i][0];
  }
  cout << endl;

  FOR(i, 0, n) {
    if (i) cout << " ";
    cout << res[i][1];
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py codeforces/problemset/1366D/main.cpp --check

%%%% begin
10
2 3 4 5 6 7 8 9 10 24
%%%%
-1 -1 -1 -1 3 -1 -1 -1 2 2
-1 -1 -1 -1 2 -1 -1 -1 5 3
%%%% end
*/
