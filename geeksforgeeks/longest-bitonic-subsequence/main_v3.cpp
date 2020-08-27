// AFTER EDITORIAL, AC

// NOTE: in main_v2.cpp, replaying "dp" by "dp_log" is not really needed...

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
// template<typename T> struct is_container {
// template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
// static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
// };
// namespace std {
// template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
// template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
// template<class T, enable_if_t<is_container<T>::value, int> = 0>
// istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
// }

// // Debugging
// #define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
// #define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
// namespace std {
// template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
// template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
// template<class T, enable_if_t<is_container<T>::value, int> = 0>
// ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
// }

// Main
void mainCase() {
  int n; // <= 100
  cin >> n;
  vector<int> ls(n, 0); // <= 200
  // cin >> ls;
  for (auto& x : ls) { cin >> x; }

  vector<int> incrs(n, -1);
  {
    vector<int> dp;
    FOR(i, 0, n) {
      auto it = lower_bound(ALL(dp), ls[i]);
      incrs[i] = distance(dp.begin(), it);
      if (it == dp.end()) {
        dp.push_back(ls[i]);
      } else {
        *it = ls[i];
      }
    }
  }

  vector<int> decrs(n, -1);
  {
    vector<int> dp;
    for (int i = n - 1; i >= 0; i--) {
      auto it = lower_bound(ALL(dp), ls[i]);
      decrs[i] = distance(dp.begin(), it);
      if (it == dp.end()) {
        dp.push_back(ls[i]);
      } else {
        *it = ls[i];
      }
    }
  }
  // DD(incrs);
  // DD(decrs);

  int res = 0;
  FOR(i, 0, n) {
    res = max(res, incrs[i] + decrs[i] + 1);
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py geeksforgeeks/longest-bitonic-subsequence/main_v3.cpp --check

%%%% begin
1
91
51 7 35 19 90 43 34 48 78 27 54 79 89 1 80 77 55 19 55 100 68 8 24 29 82 9 60 90 64 39 80 66 46 14 85 87 8 70 86 85 97 40 15 85 92 94 13 98 65 68 98 32 27 73 61 60 81 72 49 96 10 80 61 7 45 97 46 4 67 31 88 63 70 2 99 61 48 12 11 12 79 8 95 57 32 55 16 12 26 16 7
%%%%
24
%%%% end

%%%% begin
1
2
1 1
%%%%
1
%%%% end

%%%% begin
2
5
1 2 5 3 2
8
1 11 2 10 4 5 2 1
%%%%
5
6
%%%% end
*/
