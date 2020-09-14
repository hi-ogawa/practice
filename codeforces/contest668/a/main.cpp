// AC

// TODO: prove correctness

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
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;

  // cum count 0/1/?
  vector<vector<int>> cnts(3, vector<int>(n + 1));
  FOR(i, 0, n) {
    cnts[0][i + 1] = cnts[0][i] + (s[i] == '0');
    cnts[1][i + 1] = cnts[1][i] + (s[i] == '1');
    cnts[2][i + 1] = cnts[2][i] + (s[i] == '?');
  }
  dbg2(cnts);

  // Check 0/1 balance of each k-segment
  bool ok1 = 1;
  FOR(i, 0, n - k + 1) {
    int c0 = cnts[0][i + k] - cnts[0][i];
    int c1 = cnts[1][i + k] - cnts[1][i];
    int c2 = cnts[2][i + k] - cnts[2][i];
    if (abs(c0 - c1) > c2) { ok1 = 0; break; }
  }
  if (!ok1) { cout << "NO" << endl; return; }

  // Check (k+1)-symmetry
  bool ok2 = 1;
  FOR(i, 0, n - k) {
    if (s[i] != s[i + k]) {
      if (s[i] != '?' && s[i + k] != '?') { ok2 = 0; break; }
      // Resolve symmetry
      if (s[i + k] == '?') { s[i + k] = s[i]; }
      if (s[i]     == '?') { s[i] = s[i + k]; }
    }
  }
  if (!ok2) { cout << "NO" << endl; return; }
  dbg(s);

  // Check 0/1 balance again
  FOR(i, 0, n) {
    cnts[0][i + 1] = cnts[0][i] + (s[i] == '0');
    cnts[1][i + 1] = cnts[1][i] + (s[i] == '1');
    cnts[2][i + 1] = cnts[2][i] + (s[i] == '?');
  }

  bool ok3 = 1;
  FOR(i, 0, n - k + 1) {
    int c0 = cnts[0][i + k] - cnts[0][i];
    int c1 = cnts[1][i + k] - cnts[1][i];
    int c2 = cnts[2][i + k] - cnts[2][i];
    if (abs(c0 - c1) > c2) { ok3 = 0; break; }
  }
  if (!ok3) { cout << "NO" << endl; return; }

  cout << "YES" << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest668/a/main.cpp --check

%%%% begin
9
6 4
100110
3 2
1?1
3 2
1?0
4 4
????
7 4
1?0??1?
10 10
11??11??11
4 2
1??1
4 4
?0?0
6 2
????00
%%%%
YES
YES
NO
YES
YES
NO
NO
YES
NO
%%%% end
*/
