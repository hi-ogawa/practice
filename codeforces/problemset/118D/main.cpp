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

constexpr ll modulo = 1e8;
ll madd(ll x, ll y) { return (x + y) % modulo; }
ll maddeq(ll& x, ll y) { return x = madd(x, y); }

template<class T>
using V = vector<T>;

// Main
void mainCase() {
  int n1, n2, k1, k2;
  cin >> n1 >> n2 >> k1 >> k2;

  V<V<V<ll>>> dp1(n1 + 1, V<V<ll>>(n2 + 1, V<ll>(k1 + 1)));
  V<V<V<ll>>> dp2(n1 + 1, V<V<ll>>(n2 + 1, V<ll>(k2 + 1)));
  dp1[0][0][0] = 1;
  dp2[0][0][0] = 1;

  FOR(i, 0, n1 + 1) {
    FOR(j, 0, n2 + 1) {
      // Append "1"
      FOR(l, 1, k1 + 1) {
        if (i == 0) { continue; }
        dp1[i][j][l] = dp1[i - 1][j][l - 1];
        maddeq(dp2[i][j][0], dp1[i][j][l]);
      }
      // Append "0"
      FOR(l, 1, k2 + 1) {
        if (j == 0) { continue; }
        dp2[i][j][l] = dp2[i][j - 1][l - 1];
        maddeq(dp1[i][j][0], dp2[i][j][l]);
      }
    }
  }
  dbg2(dp1);
  dbg2(dp2);

  ll res = 0;
  FOR(l, 0, k1 + 1) {
    maddeq(res, dp1[n1][n2][l]);
  }
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
python misc/run.py codeforces/problemset/118D/main.cpp --check

%%%% begin
2 1 1 10
%%%%
1
%%%% end
*/
