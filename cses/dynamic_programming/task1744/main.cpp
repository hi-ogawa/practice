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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll a, b; // <= 500
  cin >> a >> b;

  // WLOG, a <= b
  if (a > b) { swap(a, b); }

  vector<vector<ll>> dp(a + 1, vector<ll>(b + 1, 0));
  auto _dp = [&](int i, int j) {
    if (i > j) { swap(i, j); }
    return dp[i][j];
  };
  FOR(i, 1, a + 1) {
    FOR(j, i + 1, b + 1) {
      ll tmp = 1 << 30;
      FOR(i1, 1, i) {
        ll i2 = i - i1;
        tmp = min(tmp, _dp(i1, j) + _dp(i2, j));
      }
      FOR(j1, 1, j) {
        ll j2 = j - j1;
        tmp = min(tmp, _dp(i, j1) + _dp(i, j2));
      }
      dp[i][j] = tmp + 1;
    }
  }
  // DD2(dp);

  ll res = dp[a][b];
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
python misc/run.py cses/dynamic_programming/task1744/main.cpp --check

%%%% begin
3 5
%%%%
3
%%%% end
*/
