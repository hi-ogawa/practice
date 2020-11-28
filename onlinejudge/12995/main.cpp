// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
using ll = int64_t;
using ull = uint64_t;
// [ For C++ 11 ]
// namespace std {
// template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
// template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
// template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
// template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
// template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
// istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
// template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
// ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
// }

#ifdef DEBUG
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Euler's totient computed by the formula
//   ϕ(n) = n . ∏ (p - 1) / p
vector<int> makeTotient(int n) {
  vector<bool> sieve(n + 1, 1);
  vector<int> res(n + 1);
  iota(ALL(res), 0);
  res[1] = 0;
  for (int p = 2; p <= n; p++) {
    if (!sieve[p]) { continue; }
    for (int x = p; x <= n; x += p) {
      res[x] = (res[x] / p) * (p - 1);
      sieve[x] = 0;
    }
  }
  return res;
}

// Main

vector<int> phi;
vector<ll> fn;

void mainPrecompute() {
  const int n = 1e6;
  phi = makeTotient(n);
  fn = {ALL(phi)};
  FOR(i, 2, n) { fn[i + 1] += fn[i]; }
}

void mainCase(int n) { // [1, 10^6]
  //
  // PROP.
  //   For n < m, define p(n, m) = #{ (a, b) \in Zn* x Zm* | nb - ma = ± 1 }
  //   then, it's easy to see:
  //     gcd(n, m) > 1 => p(n, m) = 0.
  //
  //   Now assuming gcd(n, m) = 1, then, from isomorphism of CRT , we have
  //       Zn* x Zm* = Z(nm)*
  //      (a1, b1)  <->  +1
  //      (a2, b2)  <->  -1
  //   Thus p(n, m) = 2
  //

  // Tweak a bit to handle {0/1, 1/1}
  ll f = fn[n] + 2;
  ll g = 2 * fn[n] + 1;

  ll res = g - (f - 1);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainPrecompute();
  int n;
  while (true) {
    cin >> n;
    if (n == 0) { break; }
    mainCase(n);
  }
  return 0;
}

/*
python misc/run.py onlinejudge/12995/main.cpp

%%%% begin
1
4
0
%%%%
0
5
%%%% end
*/
