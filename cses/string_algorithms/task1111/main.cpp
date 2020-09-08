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
  string s;
  cin >> s;

  // Same spirit as the construction of Z function
  int n = s.size();
  vector<int> d1(n), d2(n);
  {
    int l = 0, r = 0; // (l, r)
    FOR(i, 0, n) {
      if (i < r) { d1[i] = min(d1[l + r - i], r - i); }
      while (
        0 <= i - d1[i] && i + d1[i] < n &&
        s[i - d1[i]] == s[i + d1[i]]) { d1[i]++; }
      if (r < i + d1[i]) { l = i - d1[i]; r = i + d1[i]; }
    }
    dbg(d1);
  }
  {
    int l = 0, r = 0; // (l, r)
    FOR(i, 0, n) {
      if (i + 1 < r) { d2[i] = min(d2[l + r - (i + 1)], r - (i + 1)); }
      while (
        0 <= i - d2[i] && i + d2[i] + 1 < n &&
        s[i - d2[i]] == s[i + d2[i] + 1]) { d2[i]++; }
      if (r < i + d2[i] + 1) { l = i - d2[i]; r = i + d2[i] + 1; }
    }
    dbg(d2);
  }

  int res1 = 0, res2 = 0, res3 = 0; // (length, odd/even, index)
  FOR(i, 0, n) {
    int l = 2 * d1[i] - 1;
    if (l > res1) { res1 = l, res2 = 1, res3 = i; }
  }
  FOR(i, 0, n) {
    int l = 2 * d2[i];
    if (l > res1) { res1 = l, res2 = 2, res3 = i; }
  }
  dbgv(res1, res2, res3);

  string res = s.substr(res3 - res1 / 2 + (res2 == 2), res1);
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
python misc/run.py cses/string_algorithms/task1111/main.cpp --check

%%%% begin
010220
%%%%
0220
%%%% end

%%%% begin
aybabtu
%%%%
bab
%%%% end
*/
