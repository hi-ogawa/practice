// AFTER CONTEST, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Modulo
constexpr ll kModulo = 998244353; // prime
ll madd(ll x, ll y) { return (x + y) % kModulo; }
ll mmul(ll x, ll y) { return (x * y) % kModulo; }
ll mexp(ll b, ll e) {
  ll res = 1, be = b;
  while (e > 0) {
    if (e & 1) { res = (res * be) % kModulo; }
    be = (be * be) % kModulo;
    e >>= 1;
  }
  return res;
}
ll minv(ll x) { return mexp(x, kModulo - 2); } // Zp* inverse
vector<ll> mfactorials(ll x) {
  vector<ll> res(x + 1, 0);
  res[0] = 1;
  FOR(i, 1, x + 1) {
    res[i] = mmul(res[i - 1], i);
  }
  return res;
}

// Main
void mainCase() {
  ll n, m, k; // n <= 10^6
  cin >> n >> m >> k;

  // Precompute factorials
  auto fs = mfactorials(n + k);
  auto binom = [&](ll n, ll k) { return mmul(fs[n], mmul(minv(fs[n - k]), minv(fs[k]))); };

  ll res = 0;
  FOR(c, 0, k + 1) {
    ll x = binom(n - 1, c);
    ll y = mexp(m - 1, n - 1 - c);
    ll z = mmul(x, mmul(y, m));
    res = madd(res, z);
  }
  cout << res << endl;
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc167/e/main.cpp --check

%%%% begin
3 2 1
%%%%
4
%%%% end

%%%% begin
100 100 0
%%%%
73074801
%%%% end

%%%% begin
60522 114575 7559
%%%%
479519525
%%%% end
*/
