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

// Main
void mainCase() {
  int n;
  cin >> n;
  vector<ll> ls(n);
  cin >> ls;

  // Split to positive/negative
  vector<ll> ps, qs;
  for (auto x : ls) {
    ((x > 0) ? ps : qs).push_back(x);
  }
  int np = ps.size(), nq = qs.size();
  sort(ALL(ps));
  sort(ALL(qs));

  auto mul = [](auto it, int k) -> ll {
    ll t = 1;
    FOR(i, 0, k) { t *= *it++; }
    return t;
  };

  // Test all positive/negative patterns

  // init
  ll res = mul(ls.begin(), 5);

  // neg x 0
  if (np >= 5 && nq >= 0) {
    ll t = mul(ps.rbegin(), 5) * mul(qs.begin(), 0);
    res = max(res, t);
  }
  // neg x 2
  if (np >= 3 && nq >= 2) {
    ll t = mul(ps.rbegin(), 3) * mul(qs.begin(), 2);
    res = max(res, t);
  }
  // neg x 4
  if (np >= 1 && nq >= 4) {
    ll t = mul(ps.rbegin(), 1) * mul(qs.begin(), 4);
    res = max(res, t);
  }

  // neg x 1
  if (np >= 4 && nq >= 1) {
    ll t = mul(ps.begin(), 4) * mul(qs.rbegin(), 1);
    res = max(res, t);
  }
  // neg x 3
  if (np >= 2 && nq >= 3) {
    ll t = mul(ps.begin(), 2) * mul(qs.rbegin(), 3);
    res = max(res, t);
  }
  // neg x 5
  if (np >= 0 && nq >= 5) {
    ll t = mul(ps.begin(), 0) * mul(qs.rbegin(), 5);
    res = max(res, t);
  }
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
python misc/run.py codeforces/contest670/b/main.cpp --check

%%%% begin
4
5
-1 -2 -3 -4 -5
6
-1 -2 -3 1 2 -1
6
-1 0 0 0 -1 -1
6
-9 -7 -5 -3 -2 1
%%%%
-120
12
0
945
%%%% end
*/
