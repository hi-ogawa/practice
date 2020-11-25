// CONTEST, AC

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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  ll n; // [2, 10^10]
  cin >> n;

  auto factorize = [&](ll n) -> vector<array<ll, 2>> {
    vector<array<ll, 2>> res;
    for (ll p = 2; p * p <= n; p++) {
      if (n % p) { continue; }
      int e = 0;
      while (n % p == 0) { n /= p; e++; }
      res.push_back({p, e});
    }
    if (n > 1) { res.push_back({n, 1}); }
    return res;
  };

  auto factors = factorize(n);
  auto it = max_element(ALL(factors), [](auto x, auto y) { return x[1] < y[1]; });
  auto [p, e] = *it;
  dbg(factors, p, e);

  vector<ll> res(e, p);
  ll x = n;
  FOR(i, 0, e - 1) { x /= p; }
  res[e - 1] = x;
  dbg(res);

  cout << e << "\n";
  FOR(i, 0, e) {
    cout << res[i] << " \n"[i == e - 1];
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
python misc/run.py codeforces/contest/1454/d/main.cpp

%%%% begin
4
2
360
4999999937
4998207083
%%%%
1
2
3
2 2 90
1
4999999937
1
4998207083
%%%% end
*/
