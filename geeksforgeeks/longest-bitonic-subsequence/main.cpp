// WA

// NOTE: This approach doesn't reject the case where two same values occurs at turning point (e.g. a < b < c = c > d > e)

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

// Longest increasing subsequence for each prefix
vector<int> solve(const vector<int>& ls) {
  int n = ls.size();
  vector<int> res(n, 0);
  vector<int> dp;
  FOR(i, 0, n) {
    auto it = lower_bound(ALL(dp), ls[i]);
    if (it == dp.end()) {
      dp.push_back(ls[i]);
    } else {
      *it = ls[i];
    }
    res[i] = dp.size();
  }
  return res;
}

// Main
void mainCase() {
  int n; // <= 100
  cin >> n;
  vector<int> ls(n, 0); // <= 200
  // c++17
  // cin >> ls;
  for (auto& x : ls) { cin >> x; }

  auto incrs = solve(ls);

  reverse(ALL(ls));
  auto decrs = solve(ls);
  reverse(ALL(decrs));
  // DD(incrs);
  // DD(decrs);

  int res = max(decrs[0], incrs[n - 1]);
  FOR(i, 1, n) {
    // DD(incrs[i - 1] + decrs[i]);
    res = max(res, incrs[i - 1] + decrs[i]);
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
python misc/run.py geeksforgeeks/longest-bitonic-subsequence/main.cpp --check

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
