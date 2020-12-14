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

//
// PROP.
//   ⌈(a x + b) / m⌉= y
//     <=>
//   ⌊(m (y - 1) - b) / a⌋ < x ≤ ⌊(m y - b) / a⌋
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

  // NOTE: Recursion depth is same as Euclid division
  function<ll(ll, ll, ll, ll, bool)> solve = [&](ll n, ll m, ll a, ll b, bool ceil_mode) -> ll {
    // Normalize a, b ∈ [0, m)
    ll aq, bq;
    tie(aq, a) = divmod(a, m);
    tie(bq, b) = divmod(b, m);
    ll f1 = ((n * (n - 1)) / 2) * aq + n * bq;

    ll f2 = 0;
    if (a == 0) {
      f2 = n * div(b, m, ceil_mode);

    } else {
      // Reduce "ceil sum -> floor sum" or "floor sum -> ceil sum"
      ll k = div(a * n + b, m, ceil_mode);
      f2 = n * k + div(-b, a, !ceil_mode) - solve(k + !ceil_mode, a, m, -b, !ceil_mode);
      if (ceil_mode) {
        // Handle boundary difference [0, n) <-> (0, n]
        f2 += div(b, m, ceil_mode) - div(a * n + b, m, ceil_mode);
      }
    }
    return f1 + f2;
  };

  auto res = solve(n, m, a, b, /* ceil_mode */ false);
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
python misc/run.py library_checker/sum_of_floor_of_linear/main.cpp

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
