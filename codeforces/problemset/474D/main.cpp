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

// Modulo op
constexpr ll modulo = 1000000000 + 7;
ll madd(ll x, ll y) { return (x + y) % modulo; }

// Main
void mainCase() {
  int nq, k;
  cin >> nq >> k;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  int n = 0;
  for (auto [x, y] : qs) { n = max(n, y); }

  // dp[i][0] #ways ends with W at i
  // dp[i][1] #ways ends with R at i
  vector<array<ll, 2>> dp(n + 1);
  dp[0] = {1, 0};
  FOR(i, 1, n + 1) {
    dp[i][0] = madd(dp[i - 1][0], dp[i - 1][1]);
    if (i - k >= 0) {
      dp[i][1] = madd(dp[i - k][0], dp[i - k][1]);
    }
  }
  dbg(dp);

  vector<ll> res(n + 1);
  FOR(i, 0, n + 1) {
    res[i] = madd(dp[i][0], dp[i][1]);
  }
  FOR(i, 0, n) {
    res[i + 1] = madd(res[i + 1], res[i]);
  }
  dbg(res);

  for (auto [x, y] : qs) {
    ll t = madd(res[y], -res[x - 1]);
    t = madd(t, modulo);
    cout << t << endl;
  }
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
python misc/run.py codeforces/problemset/474D/main.cpp --check

%%%% begin
3 2
1 3
2 3
4 4
%%%%
6
5
5
%%%% end
*/
