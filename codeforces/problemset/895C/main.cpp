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

template<ll M>
struct ModOp {
  ll modulo = M;
  ll mod(ll x)       { while (x >= M) { x -= M; }; return x; }
  ll add(ll x, ll y) { return mod(x + y); }
  ll mul(ll x, ll y) { return (x * y) % M; }
  ll div(ll x, ll y) { return mul(x, inv(y)); }
  ll inv(ll x)       { return pow(x, M - 2); }
  ll pow(ll x, ll e) {
    ll y = 1;
    while (e > 0) {
      if (e & 1) { y = mul(y, x); }
      x = mul(x, x); e >>= 1;
    }
    return y;
  }
  vector<ll> fact_;
  void makeFact(ll n) {
    if (fact_.size()) { return; }
    fact_.resize(n + 1);
    fact_[0] = 1;
    FOR(x, 1, n + 1) { fact_[x] = mul(x, fact_[x - 1]); }
  }
  ll fact(ll n) { return fact_[n]; }
  ll binom(ll n, ll k) { return div(fact(n), mul(fact(n - k), fact(k))); }

  // binom(n, 0) + binom(n, 2) + binom(n, 4) + ...
  ll binom0(ll n) {
    ll res = 0;
    for (ll x = 0; x <= n; x += 2) {
      res = add(res, binom(n, x));
    }
    return res;
  }

  // binom(n, 1) + binom(n, 3) + binom(n, 5) + ...
  ll binom1(ll n) {
    ll res = 0;
    for (ll x = 1; x <= n; x += 2) {
      res = add(res, binom(n, x));
    }
    return res;
  }
};

vector<int> makePrimes(int n) {
  vector<bool> s(n + 1, 1);
  for (int p = 2; p <= sqrt(n); p++) {
    if (!s[p]) { continue; }
    for (int x = p * p; x <= n; x += p) { s[x] = 0; }
  }
  vector<int> res;
  for (int p = 2; p <= n; p++) {
    if (s[p]) { res.push_back(p); }
  }
  return res;
}

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 70]
  cin >> ls;

  // Precompute primes
  const int x_lim = 70; // π(70) = 19
  const int k = 19;
  auto ps = makePrimes(x_lim);
  assert(ps.size() == k);

  map<int, int> cnts;
  for (auto x : ls) { cnts[x]++; }

  // Parity of ν_p(a) as bitmask of 2^k
  vector<int> masks(x_lim + 1);
  FOR(i, 1, x_lim + 1) {
    int x = i;
    int mask = 0;
    FOR(j, 0, k) {
      int p = ps[j];
      int e = 0;
      while (x % p == 0) { x /= p; e++; }
      if (e % 2 == 1) {
        mask = mask | (1 << j);
      }
    }
    masks[i] = mask;
  }

  static ModOp<(ll)1e9 + 7> mo;
  mo.makeFact(n);

  // DP for "XOR ways"
  int mask_lim = 1 << k;
  vector<ll> dp(mask_lim);
  dp[0] = 1;
  auto dp_prev = dp;
  for (auto [x, c] : cnts) {
    ll c0 = mo.binom0(c);
    ll c1 = mo.binom1(c);
    int m = masks[x];
    FOR(mask, 0, mask_lim) {
      dp[mask] = mo.add(
          mo.mul(c0, dp_prev[mask]),
          mo.mul(c1, dp_prev[mask ^ m]));
    }
    dp_prev = dp;
  }

  ll res = mo.add(dp[0], -1 + mo.modulo); // Subtract "product(empty) = 1"
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/895C/main.cpp --check

%%%% begin
4
1 1 1 1
%%%%
15
%%%% end

%%%% begin
4
2 2 2 2
%%%%
7
%%%% end

%%%% begin
5
1 2 4 5 8
%%%%
7
%%%% end
*/
