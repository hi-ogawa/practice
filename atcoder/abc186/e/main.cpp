// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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

// Main
void mainCase() {
  ll n; // [2, 10^9]
  cin >> n;
  ll s; // [1, n - 1]
  cin >> s;
  ll k; // [1, 10^9]
  cin >> k;

  auto mod = [&](ll x, ll y) -> ll { x %= y; return (x >= 0) ? x : (x + y); };

  // x a + y b = z = gcd(a, b)
  auto bezout = [](ll a, ll b) -> array<ll, 3> {
    bool flip = a < b;
    if (flip) { swap(a, b); }
    array<ll, 2> x = {1, 0}, y = {0, 1}, z = {a, b};
    while (z[1] > 0) {
      ll q = z[0] / z[1];
      x = {x[1], x[0] - q * x[1]};
      y = {y[1], y[0] - q * y[1]};
      z = {z[1], z[0] - q * z[1]};
    }
    if (flip) { swap(x, y); }
    return {x[0], y[0], z[0]};
  };

  // Solve min { x | x a = b ∈ Z(n) }
  ll a = mod(k, n);
  ll b = mod(-s, n);
  ll g = gcd(a, n);

  ll res = -1;
  if (b % g == 0) {
    ll p = n / g; // Order of <a> ⊆ Z(n)
    ll q = mod(bezout(a, n)[0], n); // q a = g ∈ Z(n)
    // b = (b / g) g
    //   = (b / g) q a
    res = mod((b / g) * q, p);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 100]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py atcoder/abc186/e/main.cpp

%%%% begin
4
10 4 3
1000 11 2
998244353 897581057 595591169
10000 6 14
%%%%
2
-1
249561088
3571
%%%% end
*/
