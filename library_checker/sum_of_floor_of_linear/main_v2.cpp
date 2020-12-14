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

//
// PROP.
//   ⌊(a x + b) / m⌋ = y
//     <=>
//   ⌈(m y - b) / a⌉ ≤ x < ⌈(m (y + 1) - b) / a⌉
//

// Main
void mainCase() {
  ll n, m; // [1, 10^9]
  ll a, b; // [0, m)
  cin >> n >> m >> a >> b;

  auto mod = [&](ll x, ll y) -> ll {
    ll z = x % y;
    if (z < 0) { z += y; }
    return z;
  };

  auto divmod = [&](ll x, ll y) -> pair<ll, ll> {
    ll w = mod(x, y);
    ll z = (x - w) / y;
    return {z, w};
  };

  auto div = [&](ll x, ll y, bool ceil_mode) -> ll {
    auto [q, r] = divmod(x, y);
    return q + (r > 0) * ceil_mode;
  };

  auto solveBezout = [](ll a, ll b) -> tuple<ll, ll, ll> {
    assert(a >= 0 && b >= 0);
    bool flip = a < b;
    if (flip) { swap(a, b); }
    array<ll, 2> x = {1, 0}, y = {0, 1}, z = {a, b};
    while (z[1] != 0) {
      ll q = z[0] / z[1], r = z[0] % z[1];
      x = {x[1], x[0] - q * x[1]};
      y = {y[1], y[0] - q * y[1]};
      z = {z[1], r};
    }
    if (flip) { swap(x, y); }
    return {z[0], x[0], y[0]};
  };

  // #{ x \in [0, n) | x a = b ∈ Zm }
  auto countDivisibles = [&](ll n, ll m, ll a, ll b) -> ll {
    auto [g, x, _y] = solveBezout(a, m); // gcd(a, m) = x a + y m
    if (b % g != 0) { return 0; }
    ll p = m / g; // Period of "a"
    ll z = mod((b / g) * x, p); // z a = b ∈ Zm
    if (z >= n) { return 0; }
    return (n - 1 - z) / p + 1;
  };

  function<ll(ll, ll, ll, ll)> solveFloor, solveCeil;

  solveFloor = [&](ll n, ll m, ll a, ll b) -> ll {
    // Normalize a, b ∈ [0, m)
    ll aq, bq;
    tie(aq, a) = divmod(a, m);
    tie(bq, b) = divmod(b, m);
    ll f1 = ((n * (n - 1)) / 2) * aq + n * bq;

    ll f2 = 0;
    if (a == 0) {
      f2 = n * (b / m);

    } else {
      // Reduce to "ceil sum"
      ll k = (a * n + b) / m;
      f2 = n * k + div(-b, a, true) - solveCeil(k + 1, a, m, -b);
    }
    return f1 + f2;
  };

  solveCeil = [&](ll n, ll m, ll a, ll b) -> ll {
    // Reduce to "floor sum"
    ll cnt = countDivisibles(n, m, a, mod(-b, m));
    return solveFloor(n, m, a, b) + n - cnt;
  };

  auto res = solveFloor(n, m, a, b);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 10^5]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py library_checker/sum_of_floor_of_linear/main_v2.cpp

%%%% begin
5
4 10 6 3
6 5 4 3
1 1 0 0
31415 92653 58979 32384
1000000000 1000000000 999999999 999999999
%%%%
3
13
0
314095480
499999999500000000
%%%% end
*/
