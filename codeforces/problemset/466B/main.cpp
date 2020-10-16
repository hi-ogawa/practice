// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  ll n0, a0, b0; // [1, 10^9]
  cin >> n0 >> a0 >> b0;
  ll n = n0 * 6;

  if (n <= a0 * b0) {
    cout << (a0 * b0) << "\n";
    cout << a0 << " " << b0 << "\n";
    return;
  }

  // a0 * b0 < n

  auto divCeil = [](ll x, ll y) -> ll { return (x + y - 1) / y; };
  const ll kInf = 1e18;

  // min_{x0 ≤ x ≤ x1} x . ceil(n / x)
  auto solve = [&](ll n, ll x0, ll x1) -> array<ll, 2> {
    // Brute force by splitting range to [x0, √n] and [√n, x1]
    array<ll, 2> res = {kInf, -1};
    ll z1 = min(x1, (ll)sqrt(n));
    FOR(x, x0, z1 + 1) {
      ll y = x * divCeil(n, x);
      if (y < res[0]) {
        res = {y, x};
      }
    }
    ll k1 = max((ll)1, divCeil(n, x1));
    ll k2 = sqrt(n) + 1;
    FOR(k, k1, k2 + 1) {
      // ceil(n / k) = min { x | ceil(n / x) = k }
      ll x = max(x0, divCeil(n, k));
      ll y = x * divCeil(n, x);
      if (y < res[0]) {
        res = {y, x};
      }
    }
    dbg(n, x0, x1, res);
    return res;
  };


  ll a1 = max(a0, n / b0);
  ll b1 = max(b0, n / a0);

  auto [res2, a2] = solve(n, a0, a1);
  auto [res3, b3] = solve(n, b0, b1);
  assert(b0 <= divCeil(n, a2));
  assert(a0 <= divCeil(n, b3));

  array<ll, 3> res;
  if (res2 < res3) {
    res = {res2, a2, divCeil(n, a2)};
  } else {
    res = {res3, divCeil(n, b3), b3};
  }

  cout << res[0] << "\n";
  cout << res[1] << " " << res[2] << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/466B/main.cpp

%%%% begin
3 3 5
%%%%
18
3 6
%%%% end

%%%% begin
2 4 4
%%%%
16
4 4
%%%% end
*/
