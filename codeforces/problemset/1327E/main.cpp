// AFTER EDITORIAL, AC

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
  int n; // [1, 2 x 10^5]
  cin >> n;
  const int m = 10; // 0,1,..,9

  const ll modulo = 998244353;
  auto add = [&](ll x, ll y) { return (x + y) % modulo; };
  auto mul = [&](ll x, ll y) { return (x * y) % modulo; };
  auto pow = [&](ll x, ll e) {
    ll res = 1;
    while (e) {
      if (e & 1) { res = mul(res, x); }
      e >>= 1; x = mul(x, x);
    }
    return res;
  };
  auto addeq = [&](ll& x, ll y) { x = add(x, y); };
  auto muleq = [&](ll& x, ll y) { x = mul(x, y); };

  // NOTE: we "double count" single sequence for different apperence of block.
  auto solve = [&](int k) -> ll {
    ll res = 0;
    if (n >= k + 1) {
      ll t1 = 2;
      muleq(t1, m * (m - 1));
      muleq(t1, pow(m, n - (k + 1)));
      addeq(res, t1);
    }
    if (n >= k + 2) {
      ll t2 = n - k - 1;
      muleq(t2, m * (m - 1) * (m - 1));
      muleq(t2, pow(m, n - (k + 2)));
      addeq(res, t2);
    }
    if (k == n) { addeq(res, m); }
    return res;
  };

  vector<ll> res(n + 1);
  FOR(k, 1, n + 1) {
    res[k] = solve(k);
  }

  FOR(k, 1, n + 1) {
    cout << res[k] << " \n"[k == n];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1327E/main.cpp --check

%%%% begin
1
%%%%
10
%%%% end

%%%% begin
2
%%%%
180 10
%%%% end
*/
