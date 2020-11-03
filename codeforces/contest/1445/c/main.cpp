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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  ll p, q; // [1, 10^18], [2, 10^9]
  cin >> p >> q;

  // Trivial case
  if (p % q != 0) {
    cout << p << "\n";
    return;
  }

  auto factorize = [](int n) -> vector<array<int, 2>> {
    vector<array<int, 2>> res;
    for (int p = 2; p * p <= n; p++) {
      if (n % p == 0) {
        int e = 0;
        while (n % p == 0) { n /= p; e++; }
        res.push_back({p, e});
      }
    }
    if (n > 1) { res.push_back({n, 1}); }
    return res;
  };

  auto pow = [](ll x, int e) -> ll {
    ll res = 1;
    while (e > 0) {
      if (e & 1) { res *= x; }
      e >>= 1; x *= x;
    }
    return res;
  };

  auto fs = factorize(q);

  ll res = 1;
  for (auto [r, e] : fs) {
    // q = r^e ...
    // p = r^f ...
    // x = r^(e - 1) ...
    ll n = p;
    int f = 0;
    while (n % r == 0) { n /= r; f++; }
    ll x = pow(r, e - 1) * (p / pow(r, f));
    assert(p % x == 0);
    assert(x % q != 0);
    res = max(res, x);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1445/c/main.cpp

%%%% begin
3
10 4
12 6
179 822
%%%%
10
4
179
%%%% end
*/
