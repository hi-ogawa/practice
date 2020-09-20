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

tuple<vector<int>, vector<int>> makeEulerSieve(int n) {
  tuple<vector<int>, vector<int>> res;
  auto& [ps, lp] = res;
  lp.resize(n + 1);
  for (int x = 2; x <= n; x++) {
    if (lp[x] == 0) { lp[x] = x; ps.push_back(x); }
    for (auto p : ps) {
      if (p > lp[x] || x * p > n) { break; }
      lp[x * p] = p;
    }
  }
  return res;
}

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  // To one-based
  ls.resize(n + 1);
  for (int i = n; i >= 1; i--) { ls[i] = ls[i - 1]; }

  // Factorize up to "n"
  vector<int> primes, lp;
  tie(primes, lp) = makeEulerSieve(n);

  auto getFactors = [&](int x) -> vector<array<int, 3>> {
    vector<array<int, 3>> res;
    while (x > 1) {
      int p = lp[x], e = 0, pe = 1;
      while (x % p == 0) { e++; pe *= p; x /= p; }
      res.push_back({p, e, pe});
    }
    return res;
  };

  // 1st pass: resolve indeterminate so that
  //    ls[x] = -1  ==>  ls[y] = -1
  //    x | y
  bool ok = 1;
  for (int k = n; k >= 2; k--) {
    if (ls[k] == -1) { continue; }
    auto factors = getFactors(k);
    for (auto [p, _e, _pe] : factors) {
      int q = k / p;
      int r = ls[k] % q;
      if (ls[q] == -1) { ls[q] = r; }
      if (ls[q] != r) { ok = 0; break; }
    }
    if (!ok) { break; }
  }
  if (!ok) { cout << 0 << endl; return; }

  // 2nd pass: count freedom
  const ll modulo = 1e9 + 7;
  auto mul   = [&](ll x, ll y) -> ll { return (x * y) % modulo; };
  auto muleq = [&](ll&x, ll y) -> ll { return x = mul(x, y); };

  ll dp = 1;
  for (int k = 2; k <= n; k++) {
    if (ls[k] != -1) { continue; }

    auto factors = getFactors(k);

    // k : multi prime composite (unique when its factors are determined)
    if (factors.size() > 1) { continue; }

    // k : prime power
    int p = factors[0][0];
    muleq(dp, p);
  }

  ll res = dp;
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py hackerrank/challenges/number-of-sequences/main.cpp --check

%%%% begin
4
0 0 0 1
%%%%
0
%%%% end

%%%% begin
3
0 -1 -1
%%%%
6
%%%% end

%%%% begin
5
0 1 2 3 4
%%%%
1
%%%% end
*/
