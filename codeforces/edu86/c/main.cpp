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
  ll a, b, nq;
  cin >> a >> b >> nq;
  vector<array<ll, 2>> qs(nq);
  cin >> qs;

  // WLOG a <= b then (x % a) % b = x % a
  if (a > b) { swap(a, b); }

  // Writing x = q b + r, then
  //   (x % b) % a = x % a
  //   <=> r % a = (q b + r) % a
  //   <=> a | q b
  //   <=> q b = m a b / g = m c
  ll g = gcd(a, b);
  ll c = a * b / g;

  // f(y) = #{ 0 <= x <= y | ... }
  auto solve = [&](ll y) -> ll {
    ll cnt = 0;
    for (ll r = 0; r < b; r++) {
      if (y - r < 0) { break; }
      cnt += (y - r) / c + 1;
    }
    return y - cnt;
  };

  vector<ll> res;
  for (auto [l, r] : qs) {
    ll x = solve(r) - solve(l - 1);
    res.push_back(x);
  }

  FOR(i, 0, nq) {
    cout << res[i] << " \n"[i == nq - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/edu86/c/main.cpp --check

%%%% begin
2
4 6 5
1 1
1 3
1 5
1 7
1 9
7 10 2
7 8
100 200
%%%%
0 0 0 2 4
0 91
%%%% end
*/
