// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

auto rng = mt19937(0x12345678);

using lll = __int128;
const int kNumTrials = 32;

// Main
void mainCase() {
  ll n; // [2, 2^63 - 1]
  cin >> n;

  auto pow = [&](ll x, ll e, ll m) -> ll {
    ll y = 1 % m;
    while (e > 0) {
      if (e & 1) { y = (lll)x * y % m; }
      e >>= 1;
      x = (lll)x * x % m;
    }
    return y;
  };

  auto test = [&](ll x, ll k, ll q, ll n) -> bool {
    ll y = pow(x, q, n);
    if (y == 1) { return 0; }
    FOR(_, 0, k) {
      if (y == n - 1) { return 0; }
      y = (lll)y * y % n;
    }
    return 1;
  };

  auto gcd = [&](ll x, ll y) -> ll {
    if (x < y) { swap(x, y); }
    while (y > 0) {
      tie(x, y) = make_tuple(y, x % y);
    }
    return x;
  };

  auto solve = [&](ll n) -> bool {
    if (n <= 2) { return 0; }
    if (n % 2 == 0) { return 1; }

    // n = 2^k q + 1
    ll q = n - 1;
    ll k = 0;
    while (q % 2 == 0) { q /= 2; k++; }

    FOR(_, 0, kNumTrials) {
      ll x = (rng() % (n - 1)) + 1;
      if (gcd(x, n) > 1) { return 1; }
      if (test(x, k, q, n)) { return 1; }
    }
    return 0;
  };

  auto res = !solve(n);
  cout << (res ? "YES" : "NO") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 500]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py spoj/PON/main.cpp

%%%% begin
5
2
3
4
5
6
%%%%
YES
YES
NO
YES
NO
%%%% end
*/
