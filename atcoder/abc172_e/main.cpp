//
// Rewrite main.js in C++
//

#include <cstdio>
#include <iostream>
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

void makeFactorials(ll n, ll modulo, vector<ll>& a, vector<ll>& a_inv) {
  ll k = 1;
  ll k_inv = 1;
  a[0] = 1;
  a_inv[0] = 1;
  for (ll i = 1; i <= n; i++) {
    ll i_inv = fastExp(i, modulo - 2, modulo);
    k = (k * i) % modulo;
    k_inv = (k_inv * i_inv) % modulo;
    a[i] = k;
    a_inv[i] = k_inv;
  }
}

ll solve(ll N, ll M, int debug = 0) {
  ll modulo = 1000'000'000 + 7;  // Prime < 2^32
  auto MUL = [&](ll x, ll y) { return (x * y) % modulo; };
  vector<ll> f;
  vector<ll> f_inv;
  f.resize(M + 1);
  f_inv.resize(M + 1);
  makeFactorials(M, modulo, f, f_inv);

  if (debug) {
    for (int i = 0; i <= M; i++) {
      printf("%d: %ld %ld %ld\n", i, f[i], f_inv[i], MUL(f[i], f_inv[i]));
    }
  }

  ll result = 0;
  for (ll k = 0; k <= N; k++) {
    ll x = MUL(f[N], MUL(f_inv[N - k], f_inv[k]));
    ll y = MUL(f[M], f_inv[M - k]);
    ll z = MUL(f[M - k], f_inv[M - N]);
    ll w = MUL(z, z);
    ll xyw = MUL(x, MUL(y, w));
    if (k % 2) {
      result += modulo - xyw;
    } else {
      result += xyw;
    }
    result %= modulo;
  }
  return result;
}

void _main(std::istream& istr, std::ostream& ostr) {
  ll N, M;
  istr >> N >> M;
  ostr << solve(N, M) << std::endl;
}

int main() {
  _main(std::cin, std::cout);
  return 0;
}

/*
clang++ -O2 -march=native -Wall -Wextra -o build/main atcoder/abc172_e/main.cpp
*/
