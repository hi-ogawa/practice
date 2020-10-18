// AFTER EDITORIAL, AC

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
  ll a, b; // [1, 10^9]
  cin >> a >> b;

  if (a == b) { cout << 0 << "\n"; return; }
  if (a > b) { swap(a, b); }

  //
  // PROP.
  //   Define f(k) = (a + k)(b + k) / gcd(a + k, b + k),
  //   then, for some d | (b - a),
  //     f(-a % d) = min f(k)
  //
  //   TODO: prove it
  //

  auto evaluate = [&](ll d) -> array<ll, 2> {
    ll k = ((-a % d) + d) % d;
    ll t = (a + k) * ((b + k) / gcd(a + k, b + k));
    dbg(d, k, t);
    return {t, k};
  };

  ll c = b - a;
  ll res1 = 1e18, res2;
  for (ll d = 1; d * d <= c; d++) {
    if (c % d == 0) {
      auto [t1, t2] = evaluate(d);
      auto [s1, s2] = evaluate(c / d);
      if (t1 < res1) {
        res1 = t1; res2 = t2;
      }
      if (s1 < res1) {
        res1 = s1; res2 = s2;
      }
    }
  }
  cout << res2 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1152C/main.cpp

%%%% begin
6 10
%%%%
2
%%%% end

%%%% begin
21 31
%%%%
9
%%%% end

%%%% begin
5 10
%%%%
0
%%%% end
*/
