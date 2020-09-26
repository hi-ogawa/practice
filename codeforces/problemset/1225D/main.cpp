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

// Euler product sieve
tuple<vector<int>, vector<int>> makeEulerSieve(int n) {
  tuple<vector<int>, vector<int>> res;
  auto& [ps, lp] = res;
  lp.resize(n + 1);
  for (int x = 2; x <= n; x++) {
    if (lp[x] == 0) { lp[x] = x; ps.push_back(x); }
    for (auto p : ps) {
      if (x * p > n || p > lp[x]) { break; }
      lp[x * p] = p;
    }
  }
  return res;
}

// Main
void mainCase() {
  int n, k; // n \in [2, 10^5]
  cin >> n >> k;
  vector<int> ls(n);
  cin >> ls;

  int a_lim = 1e5;
  vector<int> ps, lp;
  tie(ps, lp) = makeEulerSieve(a_lim);

  auto factorize = [&](int x) -> vector<array<int, 2>> {
    vector<array<int, 2>> res;
    while (x != 1) {
      int p = lp[x], e = 0;
      while (x % p == 0) { e++; x /= p; }
      res.push_back({p, e});
    }
    return res;
  };

  ll res = 0;
  map<vector<array<int, 2>>, int> cnts;
  for (auto x : ls) {
    auto fs = factorize(x);
    fs.erase(remove_if(ALL(fs), [&](auto pe) { return pe[1] % k == 0; }), fs.end());
    vector<array<int, 2>> inv_fs;
    for (auto& [p, e] : fs) {
      e %= k;
      inv_fs.push_back({p, k - e});
    }
    res += cnts[inv_fs];
    cnts[fs]++;
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1225D/main.cpp --check

%%%% begin
6 3
1 3 9 8 24 1
%%%%
5
%%%% end
*/
