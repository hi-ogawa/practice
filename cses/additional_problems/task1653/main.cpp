// AFTER EDITORIAL, TLE

// NOTE: Partition <-> Segments of permutation
// NOTE: First idea I came up with when I heard above phrase, but this is O(x.n.2^n)

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
#define DD2(X) std::cout << #X ":" << std::endl; for (auto& x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n, x; // n <= 20, x <= 10^9
  cin >> n >> x;
  vector<int> ls(n, 0);
  cin >> ls;

  // dp[s][w] = minimum number of valid partitions of subset "s" with last sum "w"
  vector<map<int, int>> dp(1 << n);
  dp[0][0] = 1;
  FOR(s, 0, 1 << n) {
    FOR(i, 0, n) {
      int ie = (1 << i);
      if (s & ie) { continue; }

      for (auto [w, k] : dp[s]) {
        int ww = (w + ls[i]) <= x ? (w + ls[i]) : ls[i];
        int kk = (w + ls[i]) <= x ? k : k + 1;
        dp[s | ie][ww] = kk;
      }
    }
  }
  // DD2(dp);

  int res = n;
  for (auto [_w, k] : dp[(1 << n) - 1]) {
    res = min(res, k);
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
python misc/run.py cses/additional_problems/task1653/main.cpp --check

%%%% begin
4 10
4 8 6 1
%%%%
2
%%%% end
*/
