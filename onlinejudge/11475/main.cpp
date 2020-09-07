// AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
// [ For c++11 ]
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
// #ifndef DEBUG
// #define DEBUG 0
// #endif
// #define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
// #define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
// #define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
// namespace std {
// template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
// template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
// template<class T, enable_if_t<is_container<T>::value, int> = 0>
// ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
// }

// Z function
vector<int> makeZ(const string& s) {
  int n = s.size();
  vector<int> z(n);
  int l = 1, r = 1; // [l, r)
  FOR(i, 1, n) {
    if (i < r) { z[i] = min(z[i - l], r - i); }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) { z[i]++; }
    if (i + z[i] > r) { l = i; r = i + z[i]; }
  }
  return z;
}

// Main
void mainCase() {
  string tmp;
  vector<string> ls;
  while (cin >> tmp) { ls.push_back(tmp); }

  auto solve = [](const string& s) -> string {
    auto s_rev = s;
    reverse(ALL(s_rev));
    auto z = makeZ(s_rev + s);
    int n = s.size();
    string res;
    FOR(i, 0, n) {
      if (z[n + i] == n - i) {
        return s + s_rev.substr(n - i);
      }
    }
    assert(0);
  };

  for (auto& s : ls) {
    string res = solve(s);
    cout << res << endl;
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
python misc/run.py onlinejudge/11475/main.cpp --check

%%%% begin
aaaa
abba
amanaplanacanal
xyz
%%%%
aaaa
abba
amanaplanacanalpanama
xyzyx
%%%% end
*/
