// AC

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

// Main
void mainCase() {
  ll n; // <= 10^18
  cin >> n;

  // min { e | k < 10^e }
  auto log10 = [&](ll k) -> ll {
    ll e = 0, x = 1;
    while (x <= k) { e++; x *= 10; }
    return e;
  };

  auto pow10 = [&](ll e) -> ll {
    ll x = 1;
    while (e > 0) { e--; x *= 10; }
    return x;
  };

  // Digit count in range [0, k) (if d = 0, it includes leading zeros)
  auto countDigit = [&](ll k, ll d) -> ll {
    ll e = log10(k);
    ll res = 0;
    FOR(p, 0, e) {
      ll x = pow10(p);
      ll x10 = x * 10;
      res += x * (k / x10);
      res += x *       (((k % x10) / x) > d);
      res += (k % x) * (((k % x10) / x) == d);
    }
    return res;
  };

  auto countLeadingZeros = [&](ll k) -> ll {
    ll e = log10(k);
    ll res = e;
    FOR(p, 1, e) {
      res += (e - p) * (pow10(p) - pow10(p - 1));
    }
    return res;
  };

  auto count1 = [&](ll k) -> ll {
    return countDigit(k, 1);
  };

  auto count0 = [&](ll k) -> ll {
    return countDigit(k, 0) - countLeadingZeros(k);
  };

  // Find k s.t. f(k) == n
  auto search = [&](ll n, function<ll(ll)> f) -> ll {
    // [k0, k1)
    ll k0 = 0;
    ll k1 = 1e18;
    while (k0 + 1 < k1) {
      ll k = (k0 + k1) / 2;
      if (f(k) > n) {
        k1 = k;
      } else {
        k0 = k;
      }
    }
    return k0;
  };

  // TODO: does it always hold c0 < c1 ??
  ll c0 = search(n, count0);
  ll c1 = search(n, count1);
  ll res = min(c0, c1) - 1;
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py cses/additional_problems/task1086/main.cpp --check

%%%% begin
5
%%%%
12
%%%% end
*/
