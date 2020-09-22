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
  ll n1, n2; // [0, 2 x 10^5]
  cin >> n1 >> n2;
  if (n1 > n2) { swap(n1, n2); }

  ll n = n1 + n2;

  auto tri = [](ll x) -> ll { return (x * (x + 1)) / 2; };

  // max { m | tri(m) <= n }
  ll m = 0;
  while (tri(m + 1) <= n) { m++; }
  dbg(m);

  // DP for sum possiblity
  ll h = 0;
  {
    vector<bool> dp(n1 + 1);
    dp[0] = 1;
    FOR(i, 1, m + 1) {
      for (int j = n1; j >= 0; j--) {
        if (j - i >= 0) {
          dp[j] = dp[j] || dp[j - i];
        }
        if (dp[j] && tri(i) - j <= n2) { // possible height
          h = i;
        }
      }
    }
    dbgv(h, dp);
  }

  // DP for sum counting
  const ll modulo = 1e9 + 7;
  auto _mod  = [&](ll x) { while (x >= modulo) { x -= modulo; }; return x; };
  auto add   = [&](ll x, ll y) { return _mod(x + y); };
  auto addeq = [&](ll&x, ll y) { return x = add(x, y); };

  vector<ll> dp(n1 + 1);
  dp[0] = 1;
  FOR(i, 1, h + 1) {
    for (int j = n1; j >= i; j--) {
      addeq(dp[j], dp[j - i]);
    }
  }
  dbg(dp);

  ll res = 0;
  ll k = max(tri(h) - n2, (ll)0);
  FOR(j, k, n1 + 1) {
    addeq(res, dp[j]);
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/478D/main.cpp --check

%%%% begin
100000 1
%%%%
2
%%%% end

%%%% begin
4 6
%%%%
2
%%%% end

%%%% begin
9 7
%%%%
6
%%%% end

%%%% begin
1 1
%%%%
2
%%%% end
*/
