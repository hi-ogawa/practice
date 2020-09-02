// WA

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
  vector<int> ls(n);
  cin >> ls;

  // Kadane style DP
  int res = 0;
  int f = ls[0];  // max sum segment end at "i" (usual Kadane)
  int mf = ls[0]; // max{segment} of f
  int g = 0;      // max { sum segment - max{segment} } end at "i"
  int mg = ls[0]; // max{segment} of g
  FOR(i, 1, n) {
    dbgv(i, f, mf, g, mg);
    int x = ls[i];

    // Usual Kadane
    if (f + x >= x) {
      f = f + x;
      mf = max(mf, x);
    } else {
      f = x;
      mf = x;
    }

    // Kadane variant
    if (x < mg) {
      if (g + x >= 0) {
        g = g + x;
      } else {
        g = 0;
        mg = x;
      }
    } else {
      int t1 = f - mf;
      int t2 = g + mg - x;
      int t3 = 0;
      g = max(t1, max(t2, t3));
      if (g == t1) {
        mg = mf;
      } else if (g == t2) {
        mg = x;
      } else {
        mg = x;
      }
    }

    res = max(res, g);
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
python misc/run.py codeforces/edu88/d/main.cpp --check

%%%% begin
5
0 5 -4 3 -1
%%%%
%%%% end

%%%% begin
8
5 2 5 3 -30 -30 6 9
%%%%
10
%%%% end
*/
