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
  ll n, m, b, modulo;
  cin >> n >> m >> b >> modulo;
  vector<ll> ls(n);
  cin >> ls;
  auto mod   = [&](ll x) -> ll { while (x >= modulo) { x -= modulo; }; return x; };
  auto add   = [&](ll x, ll y) -> ll { return mod(x + y); };
  auto addeq = [&](ll&x, ll y) -> ll { return x = add(x, y); };

  vector<vector<ll>> dp(b + 1, vector<ll>(m + 1));
  dp[0][0] = 1;
  FOR(i, 0, n) {
    int a = ls[i];
    FOR(j, 0, b - a + 1) {
      FOR(k, 0, m) {
        addeq(dp[j + a][k + 1], dp[j][k]);
      }
    }
  }
  dbg2(dp);

  ll res = 0;
  FOR(j, 0, b + 1) { addeq(res, dp[j][m]); }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/543A/main_v2.cpp --check

%%%% begin
3 3 3 100
1 1 1
%%%%
10
%%%% end

%%%% begin
3 6 5 1000000007
1 2 3
%%%%
0
%%%% end

%%%% begin
3 5 6 11
1 2 1
%%%%
0
%%%% end
*/
