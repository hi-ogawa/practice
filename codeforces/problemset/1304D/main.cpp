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

// Main
void mainCase() {
  int n;
  cin >> n;
  string s;
  cin >> s;

  // Find incr/decr segments
  vector<array<int, 2>> incrs;
  vector<array<int, 2>> decrs;
  FOR(i, 0, n - 1) {
    if (s[i] == '<') {
      if (incrs.empty() || incrs.back()[1] < i) {
        incrs.push_back({i, i});
      }
      incrs.back()[1] = i + 1;
    }
    if (s[i] == '>') {
      if (decrs.empty() || decrs.back()[1] < i) {
        decrs.push_back({i, i});
      }
      decrs.back()[1] = i + 1;
    }
  }
  dbg(incrs);
  dbg(decrs);

  //
  // PROP.
  //   This construction achieves optimal.
  //
  vector<int> ls1(n), ls2(n);
  iota(ALL(ls1), 0);
  iota(ls2.rbegin(), ls2.rend(), 0);
  for (auto [l, r] : decrs) {
    reverse(ls1.begin() + l, ls1.begin() + r + 1);
  }
  for (auto [l, r] : incrs) {
    reverse(ls2.begin() + l, ls2.begin() + r + 1);
  }
  dbg(ls1);
  dbg(ls2);

  FOR(i, 0, n) { cout << (ls2[i] + 1) << " \n"[i == n - 1]; }
  FOR(i, 0, n) { cout << (ls1[i] + 1) << " \n"[i == n - 1]; }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1304D/main.cpp --check

%%%% begin
3
3 <<
7 >><>><
5 >>><
%%%%
1 2 3
1 2 3
5 4 3 7 2 1 6
4 3 1 7 5 2 6
4 3 2 1 5
5 4 2 1 3
%%%% end
*/
