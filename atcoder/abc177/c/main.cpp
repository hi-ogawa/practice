// CONTEST, AC

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

// Modulo op
constexpr ll modulo = 1000000000 + 7;
ll madd(ll x, ll y) { return (x + y) % modulo; }
ll msub(ll x, ll y) { return (x - y) % modulo; }
ll mmul(ll x, ll y) { return (x * y) % modulo; }
ll mexp(ll x, ll e) {
  ll res = 1;
  while (e > 0) {
    if (e & 1) { res = mmul(res, x); }
    x = mmul(x, x); e >>= 1;
  }
  return res;
}
ll minv(ll x) { return mexp(x, modulo - 2); }
ll mdiv(ll x, ll y) { return mmul(x, minv(y)); }

// Main
void mainCase() {
  ll n;
  cin >> n;
  vector<ll> ls(n, 0);
  cin >> ls;

  ll s = 0;
  FOR(i, 0, n) {
    s = madd(s, ls[i]);
  }

  ll res = 0;
  FOR(i, 0, n) {
    s = msub(s, ls[i]);
    res = madd(res, mmul(ls[i], s));
  }
  res = madd(res, modulo);
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py atcoder/abc177/c/main.cpp --check

%%%% begin
3
1 2 3
%%%%
11
%%%% end
*/
