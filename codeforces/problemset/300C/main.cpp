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

// Modulo
template<ll M>
struct ModOp {
  ll add(ll x, ll y) { return ((x % M) + (y % M)) % M; }
  ll mul(ll x, ll y) { return ((x % M) * (y % M)) % M; }
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
};

// Main
void mainCase() {
  int a, b, n;
  cin >> a >> b >> n;

  // Enumerate "good"
  int lim = b * n;
  vector<bool> good(lim + 1);

  int k_lim = 0;
  while (pow(10, k_lim) <= lim) { k_lim++; }
  dbgv(lim, k_lim);

  FOR(k, 1, k_lim + 1) { // num digits
    FOR(s, 0, 1 << k) { // mask a/b
      int x = 0;
      FOR(i, 0, k) {
        int c = (s & (1 << i)) ? a : b;
        x = (10 * x) + c;
      }
      if (x <= lim) {
        dbg(x);
        good[x] = 1;
      }
    }
  }
  dbg(good);

  // Count "excellent"
  static ModOp<1000'000'000 + 7> mo;
  mo.makeFact(n);

  ll res = 0;
  FOR(x, 1, lim + 1) {
    if (!good[x]) { continue; } // #{ goods } <= 2^7

    // TODO: probably we want to optimize
    // k1 a + k2 b = x
    // k1 + k2 = n
    FOR(k1, 0, n + 1) {
      int k2 = n - k1;
      if (k1 * a + k2 * b == x) {
        ll t = mo.binom(n, k1);
        dbgv(x, k1, k2, t);
        res = mo.add(res, t);
      }
    }
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/300C/main.cpp --check

%%%% begin
1 3 3
%%%%
1
%%%% end

%%%% begin
2 3 10
%%%%
165
%%%% end
*/
