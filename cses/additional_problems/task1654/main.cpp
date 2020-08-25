// WIP

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
  int n; // <= 10^6
  cin >> n;
  vector<int> ls(n, 0); // 1 <= x <= 10^6
  cin >> ls;

  int m = *max_element(ALL(ls));
  int k = 0; // m < 2^k
  while ((1 << k) <= m) { k++; }
  DD(tie(m, k));

  // TODO: Probably, memoized recursion style DP is convinient to enumerate all subsets 2^k
  vector<int> dp0(m + 1, 0);
  vector<int> dp1(m + 1, 0);
  vector<int> dp2(m + 1, 0);
  vector<int> dp3(m + 1, 0);

  // Single bit
  for (auto x : ls) {
    dp0[x]++;
    FOR(i, 0, k) {
      int y = 1 << i;
      if (x == y) {
        dp1[y]++;
      }
      if (x & y) {
        dp2[y]++;
        dp3[y]++;
      }
    }
  }
  DD(dp0);
  DD(dp1);
  DD(dp2);
  DD(dp3);

  // More bits


  // Results
  for (auto x : ls) {
    cout << dp1[x] << " " << dp2[x] << " " << dp3[x] << endl;
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
python misc/run.py cses/additional_problems/task1654/main.cpp --check

%%%% begin
5
3 7 2 9 2
%%%%
3 2 5
4 1 5
2 4 4
1 1 3
2 4 4
%%%% end
*/
