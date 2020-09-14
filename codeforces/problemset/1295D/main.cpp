// MLE

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

vector<int> makeMobius(ll n) {
  vector<bool> sieve(n + 1, 1);
  vector<int> mu(n + 1, 1);
  for (ll p = 2; p <= n; p++) {
    if (!sieve[p]) { continue; }
    for (ll x = p; x <= n; x += p) {
      sieve[x] = 0;
      mu[x] *= -1;
    }
    for (ll x = p * p; x <= n; x += p * p) {
      mu[x] = 0;
    }
  }
  return mu;
}

//
// By inclusion-exclusion trick,
//   #{ x ∈ [1, r] | gcd(x, z) = y }
//     = ∑_{y | d and d | z} μ(d/y) ⌊r/d⌋
//     = ∑_{a | z/y} μ(a) ⌊r/(a.y)⌋
//
ll solve(ll y, ll z, ll r) {
  ll w = z / y;
  auto mu = makeMobius(w);
  ll res = 0;
  for (ll a = 1; a <= w; a++) {
    if (w % a == 0) {
      res += mu[a] * (r / (a * y));
    }
  }
  return res;
}

// Main
void mainCase() {
  ll a, m; // [1, 10^10]
  cin >> a >> m;

  ll g = gcd(a, m);
  ll res = solve(g, m, m - 1);
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
python misc/run.py codeforces/problemset/1295D/main.cpp --check

%%%% begin
1
4 9
%%%%
6
%%%% end

%%%% begin
3
4 9
5 10
42 9999999967
%%%%
6
1
9999999966
%%%% end
*/
