// CONTEST, AC

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
  int n;
  cin >> n;
  vector<int> ls(n, 0);
  cin >> ls;

  int m = *max_element(ALL(ls));

  int g = ls[0];
  FOR(i, 1, n) { g = gcd(g, ls[i]); }
  dbg(g);
  if (g > 1) {
    cout << "not coprime" << endl;
    return;
  }

  // Precompute factors
  vector<bool> sieve(m + 1, 1);
  vector<vector<int>> factors(m + 1);
  for (int p = 2; p <= m; p++) {
    if (sieve[p] == 0) { continue; }
    for (int x = p; x <= m; x += p) {
      sieve[x] = 0;
      factors[x].push_back(p);
    }
  }
  dbg(factors);

  set<int> fs;
  bool pairwise = 1;
  FOR(i, 0, n) {
    for (auto f : factors[ls[i]]) {
      if (fs.count(f)) {
        pairwise = 0;
        break;
      }
      fs.insert(f);
    }
  }
  dbg(pairwise);

  cout << (pairwise ? "pairwise coprime" : "setwise coprime") << endl;
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
python misc/run.py atcoder/abc177/e/main.cpp --check

%%%% begin
3
3 4 5
%%%%
pairwise coprime
%%%% end

%%%% begin
2
1 1000000
%%%%
%%%% end
*/
