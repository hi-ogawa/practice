// WIP

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

vector<int> makePrimes(int n) {
  vector<bool> sieve(n + 1, 1);
  sieve[0] = sieve[1] = 0;
  for (int p = 2; p <= sqrt(n); p++) {
    if (!sieve[p]) { continue; }
    for (int x = p * p; x <= n; x += p) {
      sieve[x] = 0;
    }
  }
  vector<int> res;
  for (int p = 2; p <= n; p++) {
    if (sieve[p]) { res.push_back(p); }
  }
  return res;
}

// Main
void mainCase() {
  int n; // [1, 100]
  cin >> n;
  vector<int> ls(n); // [1, 30]
  cin >> ls;

  int m = *max_element(ALL(ls));

  // NOTE: π(60) = 17 (primes: 2, 3, ..., 53, 59)
  int b_max = 2 * *max_element(ALL(ls)); // we don't need b > 2a since we can always use "1" instead
  auto ps = makePrimes(b_max);
  int k = ps.size();
  dbg(k, ps);

  vector<tuple<int, vector<int>>> factors; // (mask, {p, ...})

  // d(mask, a)
  // vector<vector<int>> dists(1 << k, vector<int>(m + 1));
  // FOR(s, 0, 1 << k) {
  //   FOR(a, 1, m + 1) {
  //   }
  // }

  // vector<tuple<int, vector<int>>> factors; // (mask, {p, ...})
  // // FOR(i0, 0, k) {
  // //   FOR(i1, 0, k) {
  // //     FOR(i2, 0, k) {
  // //     }
  // //   }
  // // }

  // // Precompute possible multi factor cases
  // vector<tuple<int, vector<int>>> multi_factors; // (mask, {pi, ...})
  // // TODO

  // const int kInf = 1e9;

  // // dp(i, S) = min cost for (a1, .., ai) and prime factors S
  // vector<int> dp(1 << k, kInf);
  // auto dp_prev = dp;

  // dp[0] = 0;
  // FOR(i, 0, n) {
  //   dp_prev = dp;
  //   int x = ls[i];

  //   FOR(s, 0, 1 << k) {
  //     // Match "ls[i]" to single factor
  //     FOR(j, 0, k) {
  //       if (s & (1 << j)) { continue; }
  //       int p = ps[j];
  //       dp_prev[s];
  //       dp[s | (1 << j)];
  //     }

  //     // Match "ls[i]" to multiple factors
  //     // for (auto& [t, qs] : multi_factors) {
  //     //   if (s & t) { continue; }
  //     //   dp_prev[s];
  //     //   dp[s | t];
  //     // }
  //   }
  // }

  // // Optimize when available prime factors are fixed
  // auto solve = [&](int mask) -> tuple<int, vector<int>> {
  //   return {0, {}};
  // };

  // int res1 = kInf;
  // vector<int> res2;
  // FOR(mask, 0, 1 << k) {
  //   auto [t1, t2] = solve(mask);
  //   if (t1 < res1) {
  //     res1 = t1;
  //     res2 = t2;
  //   }
  // }
  // dbg(res1, res2);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/453B/main.cpp

%%%% begin
5
1 1 1 1 1
%%%%
1 1 1 1 1
%%%% end

%%%% begin
5
1 6 4 2 8
%%%%
1 5 3 1 8
%%%% end
*/
