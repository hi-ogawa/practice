// AFTER CONTEST, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
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

// Main
constexpr ll kModulo = 1000000000 + 7;
ll madd(ll x, ll y) { return (x + y) % kModulo; }
ll mmul(ll x, ll y) { return (x * y) % kModulo; }
ll mexp(ll b, ll e) {
  ll res = 1;
  ll be = b;
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
  RANGE(i, 1, x + 1) {
    res[i] = mmul(res[i - 1], i);
  }
  return res;
}

void mainCase() {
  ll n;
  string s1;
  string s2;
  cin >> n >> s1 >> s2; // n <= 10^5

  // Order on input is irrelavant
  ll k1 = 0;
  ll k2 = 0;
  RANGE(i, 0, n) {
    k1 += s1[i] == '1';
    k2 += s2[i] == '1';
  }
  // WLOG, k1 <= k2
  if (k1 > k2) { swap(k1, k2); }
  // DD(tie(n, k1, k2));

  // Enumerate possible number k of "1" bits after XOR-ing k1 and k2 "1" bits.
  // then, multiply each by binom(n, k)
  ll res = 0;
  auto fs = mfactorials(n);
  auto binom = [&](ll n, ll k) { return mmul(fs[n], mmul(minv(fs[n - k]), minv(fs[k]))); };
  // DD(fs);

  RANGE(o, 0, k1 + 1) {
    ll k = k1 + k2 - 2 * o;  // XOR overwrap
    if (0 <= k && k <= n && k1 + k2 - o <= n) {
      res = madd(res, binom(n, k));
    }
  }

  cout << res << endl;
}

int main() {
  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA05/BINXOR/main.cpp --check

%%%% begin
1
2
00
10
%%%%
2
%%%% end

%%%% begin
1
10
0000000001
0000000001
%%%%
46
%%%% end

%%%% begin
1
2
11
11
%%%%
1
%%%% end
*/
