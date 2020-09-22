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

// Hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
ull hash64(ull x) {
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9ULL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebULL;
  x ^= x >> 31;
  return x;
};

array<ll, 3> solveBezout(ll a, ll b) { // p a + q b = gcd(a, b)
  bool sw = a < b;
  if (sw) { swap(a, b); }
  array<ll, 2> x = {1, 0}, y = {0, 1}, z = {a, b};
  while (z[1] != 0) {
    ll q = z[0] / z[1], r = z[0] % z[1];
    x = {x[1], x[0] - q * x[1]};
    y = {y[1], y[0] - q * y[1]};
    z = {z[1], r};
  }
  if (sw) { swap(x[0], y[0]); }
  return {x[0], y[0], z[0]};
}

ll mod(ll x, ll m) { x %= m; return x >= 0 ? x : x + m; }
ll modPow(ll x, ll e, ll m) {
  ll res = 1;
  while (e) {
    if (e & 1) { res = (res * x) % m; }
    e >>= 1; x = (x * x) % m;
  }
  return res;
}

// c a^x = b \in Zm with gcd(a, m) = 1
ll solveCoprime(ll c, ll a, ll b, ll m) {
  dbgv(c, a, b, m);
  assert(gcd(a, m) == 1);

  // Writing x = q d + r
  //   c a^(q d + r) = b  <=> c a^(dq) = b a^(-r)

  ll d = sqrt(m);
  ll a_inv = mod(solveBezout(a, m)[0], m);
  ll ad = modPow(a, d, m);

  struct Hash64 { size_t operator()(ll x) const { return hash64(x); }; };
  unordered_map<ll, ll, Hash64> qs;
  for (ll q = 0, z = 1; q <= m / d; q++) {
    ll w = (c * z) % m;
    qs[w] = q;
    z = (z * ad) % m;
  }

  for (ll r = 0, z = 1; r < d; r++) {
    ll w = (b * z) % m;
    if (qs.count(w)) { return qs[w] * d + r; }
    z = (z * a_inv) % m;
  }

  return -1;
}

// a^x = b \in Zm
ll solve(ll a, ll b, ll m) {
  assert(m > 0);

  a = mod(a, m);
  b = mod(b, m);
  ll c = 1;
  ll y = 0;
  ll g = gcd(a, m);

  // Reduce to the case gcd(a, m) = 1;
  while (g > 1) {
    dbgv(c, a, b, m, g);

    // x == 0
    if (c == b) { return y; }

    // x > 0
    if (b % g != 0) { return -1; }

    m /= g;
    b /= g;
    c = mod(c * a / g, m);
    a = mod(a, m);
    g = gcd(a, m);
    y++;
  }

  ll x = solveCoprime(c, a, b, m);
  return x == -1 ? x : x + y;
}

// Main
void mainCase() {
  ll a, b, m; // a, b \in [0, m), m \in [1, 10^9]
  cin >> a >> b >> m;

  ll res = solve(a, b, m);
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/gym101853/g/main.cpp --check

%%%% begin
1
4 6 10
%%%%
6
%%%% end

%%%% begin
3
3 9 11
2 3 5
2 1 5
%%%%
7
3
4
%%%% end
*/
