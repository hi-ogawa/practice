// AFTER EDITORIAL

//
// Modulo version of main.py
//

#include <cstdio>
#include <iostream>
#include <tuple>
#include <vector>

using ll = int64_t;
using namespace std;

ll fastExp(ll base, ll exp, ll modulo) {
  ll result = 1;
  ll be = base;
  while (exp > 0) {
    if (exp & 1) {
      result = (result * be) % modulo;
    }
    be = (be * be) % modulo;
    exp >>= 1;
  }
  return result;
}

tuple<vector<ll>, vector<ll>> makeFactorials(ll n, ll modulo) {
  vector<ll> a(n + 1, 0);
  vector<ll> a_inv(n + 1, 0);
  ll k = a[0] = a_inv[0] = 1;
  for (ll i = 1; i <= n; i++) {
    k = (k * i) % modulo;
    a[i] = k;
    a_inv[i] = fastExp(k, modulo - 2, modulo);
  }
  return {a, a_inv};
}

ll solve(ll k, const string& s, int debug = 0) {
  ll modulo = 1000'000'000 + 7;  // Prime < 2^32
  ll l = 26;                     // Alphabets
  ll m = s.size();               // > 0
  ll n = k + m;
  auto [f, f_inv] = makeFactorials(n, modulo);
  auto ADD = [&](ll x, ll y) { return (x + y) % modulo; };
  auto MUL = [&](ll x, ll y) { return (x * y) % modulo; };
  auto EXP = [&](ll x, ll y) { return fastExp(x, y, modulo); };
#define COMB(N, K) MUL(f[(N)], MUL(f_inv[(K)], f_inv[(N) - (K)]))

  if (debug) {
    for (int i = 0; i <= n; i++) {
      printf("%d: %ld %ld %ld\n", i, f[i], f_inv[i], MUL(f[i], f_inv[i]));
    }
  }

  ll result = 0;
  for (int i = m; i <= n; i++) {
    ll c = COMB(i - 1, m - 1);
    ll d = EXP(l - 1, i - m);
    ll e = EXP(l, n - i);
    ll cde = MUL(c, MUL(d, e));
    result = ADD(result, cde);
  }
  return result;
}

void _main(istream& istr, ostream& ostr) {
  ll k;
  istr >> k;
  string s;
  istr >> s;
  ostr << solve(k, s) << endl;
}

int main() {
  _main(cin, cout);
  return 0;
}

/*
clang++ -std=c++17 -O2 -march=native -Wall -Wextra -o build/main atcoder/abc171_f/main.cpp
./build/main
*/
