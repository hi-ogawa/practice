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
  ll n; // [1, 10^18]
  int k; // [1, 20]
  cin >> n >> k;
  vector<ll> ls(k); // [2, n], distinct primes
  cin >> ls;

  // returns -1 if overflow
  auto getProduct = [&](int s) -> ll {
    ll x = 1;
    FOR(i, 0, k) {
      if (!(s & (1 << i))) { continue; }
      ll y = ls[i];
      if (x > n / y) { return -1; }
      x *= y;
    }
    return x;
  };

  // Count indivisibles by inclusion-exclusion
  ll res = 0;
  FOR(s, 0, 1 << k) {
    ll d = getProduct(s);
    if (d == -1) { continue; }
    int inc_exc = 1 - 2 * (__builtin_popcount(s) % 2);
    res += inc_exc * (n / d);
  }

  ll res2 = n - res;
  cout << res2 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/mathematics/task2185/main.cpp

%%%% begin
20 2
2 5
%%%%
12
%%%% end
*/
