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

ll modPow(ll x, ll e, ll m) {
  ll res = 1;
  while (e) {
    if (e & 1) { res = (res * x) % m; }
    e >>= 1; x = (x * x) % m;
  }
  return res;
}

int mainCheckCase(istream& inp, istream& outp) {
  ll a, b, m, res;
  inp >> a >> b >> m;
  outp >> res;

  if (res == -1) {
    ll z = 1;
    if (b == z) { return 1; }
    for (ll x = 0; x < m; x++) {
      z = (z * a) % m;
      if (b == z) { return 1; }
    }
    return 0;
  }

  return modPow(a, res, m) != b;
}

int mainCheck(istream& inp, istream& outp) {
  int t;
  inp >> t;
  FOR(i, 0, t) {
    if (int res = mainCheckCase(inp, outp)) {
      return res;
    }
  }
  return 0;
}

int main(int argc, const char* argv[]) {
  assert(argc >= 3);
  ifstream inp(argv[1]);
  ifstream outp(argv[2]);
  assert(inp);
  assert(outp);
  return mainCheck(inp, outp);
}
