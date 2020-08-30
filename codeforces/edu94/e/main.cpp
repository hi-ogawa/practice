// AFTER EDITORIAL, AC

//
// NOTE:
//   1. Clearly each non-zero segment is independent, thus we can optimize each segment separately.
//   2. Whenever using operation of 1st type, clearly it doesn't worth not choosing as large segment as possible.
//

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
  int n; // <= 5000
  cin >> n;
  vector<int> ls(n, 0); // <= 10^9
  cin >> ls;

  function<int(int, int)> solveRec = [&](int l, int r) {
    if (l == r) { return 0; }

    int i = l;
    int res = 0;
    while (i < r) {
      if (ls[i] == 0) {
        i++;
        continue;
      }
      // Find non zero segment [i, j)
      int j = i + 1;
      while (j < r && ls[j] > 0) { j++; }

      // Apply 1st operation with m
      int m = *min_element(ls.begin() + i, ls.begin() + j);
      FOR(k, i, j) { ls[k] -= m; }
      res += min(solveRec(i, j) + m, j - i); // Compare to 2nd operation cost = (j - i)
      i = j;
    }

    return res;
  };

  int res = solveRec(0, n);
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
python misc/run.py codeforces/edu94/e/main.cpp --check

%%%% begin
4
1 4 1 1
%%%%
2
%%%% end
*/
