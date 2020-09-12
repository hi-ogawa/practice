// AFTER EDITORIAL, AC

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

// Euler's sieve (cf. cp-algorithms)
tuple<vector<int>, vector<int>> makeEulerSieve(int n) {
  tuple<vector<int>, vector<int>> res; // NRVO
  auto& [ps, lp] = res;
  lp.resize(n + 1);
  for (int x = 2; x <= n; x++) {
    if (lp[x] == 0) {
      lp[x] = x;
      ps.push_back(x);
    }
    for (auto p : ps) {
      if (x * p > n || p > lp[x]) { break; }
      lp[x * p] = p;
    }
  }
  return res;
}

// Main
void mainCase() {
  int n;
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  // WLOG gcd(ls) = 1
  int g = ls[0];
  FOR(i, 1, n) { g = gcd(g, ls[i]); }
  FOR(i, 0, n) { ls[i] /= g; }

  // Not solvable if ls = {1, .., 1}
  int k = *max_element(ALL(ls));
  if (k == 1) { cout << -1 << endl; return; }

  // Make prime under k
  auto [ps, lp] = makeEulerSieve(k);
  dbg(ps);
  dbg(lp);

  // Collect factors of ls
  set<int> factors;
  for (auto x : ls) {
    while (x != 1) {
      factors.insert(lp[x]);
      x /= lp[x];
    }
  }
  dbg(factors);

  vector<int> cnts(k + 1);
  for (auto x : ls) { cnts[x]++; }

  int res = 0;
  for (auto p : factors) {
    // f(p) = #{ a | p divides a } (maximize #{not removed elements})
    int f = 0;
    for (int x = p; x <= k; x += p) { f += cnts[x]; }
    res = max(res, f);
  }
  int res2 = n - res;
  cout << res2 << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1034A/main_v3.cpp --check

%%%% begin
2
1 100
%%%%
1
%%%% end

%%%% begin
3
1 2 4
%%%%
1
%%%% end

%%%% begin
4
6 9 15 30
%%%%
2
%%%% end

%%%% begin
3
1 1 1
%%%%
-1
%%%% end
*/
