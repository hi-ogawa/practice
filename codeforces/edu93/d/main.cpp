// VC

// TODO: prove it

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
  ll n1, n2, n3; // <= 200
  cin >> n1 >> n2 >> n3;

  vector<ll> ls1(n1, 0);
  vector<ll> ls2(n2, 0);
  vector<ll> ls3(n3, 0);
  cin >> ls1 >> ls2 >> ls3;
  sort(ALL(ls1), greater<ll>());
  sort(ALL(ls2), greater<ll>());
  sort(ALL(ls3), greater<ll>());
  // DD(tie(ls1, ls2, ls3));

  vector<vector<vector<ll>>> dp(n1 + 1, vector<vector<ll>>(n2 + 1, vector<ll>(n3 + 1, 0)));
  FOR(i1, 0, n1 + 1) {
    FOR(i2, 0, n2 + 1) {
      FOR(i3, 0, n3 + 1) {
        ll tmp = 0;
        ll x1 = 0, x2 = 0, x3 = 0;
        if (i1) { x1 = ls1[i1 - 1]; }
        if (i2) { x2 = ls2[i2 - 1]; }
        if (i3) { x3 = ls3[i3 - 1]; }
        if (i1) { tmp = max(tmp, dp[i1 - 1][i2][i3]); }
        if (i2) { tmp = max(tmp, dp[i1][i2 - 1][i3]); }
        if (i3) { tmp = max(tmp, dp[i1][i2][i3 - 1]); }
        if (i1 && i2) { tmp = max(tmp, dp[i1 - 1][i2 - 1][i3] + x1 * x2); }
        if (i2 && i3) { tmp = max(tmp, dp[i1][i2 - 1][i3 - 1] + x2 * x3); }
        if (i3 && i1) { tmp = max(tmp, dp[i1 - 1][i2][i3 - 1] + x3 * x1); }
        dp[i1][i2][i3] = tmp;
      }
    }
  }
  // DD2(dp);

  ll res = dp[n1][n2][n3];
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
python misc/run.py codeforces/edu93/d/main.cpp --check

%%%% begin
2 1 3
9 5
1
2 8 5
%%%%
99
%%%% end

%%%% begin
1 3 6
2
8 6 7
5 2 4 1 10 4
%%%%
147
%%%% end
*/
