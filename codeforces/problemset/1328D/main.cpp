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
  int n; // 3 <= n <= 10^4
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  // Check if loop
  bool is_loop = 1;
  int i0 = -1; // start index of non-loops
  FOR(i, 0, n) {
    if (ls[i] == ls[(i + 1) % n]) {
      is_loop = 0;
      i0 = i + 1;
      break;
    }
  }

  // Check if single type
  bool single = set<int>(ALL(ls)).size() == 1;

  int res1;
  vector<int> res2(n);

  if (is_loop) {
    if (n % 2 == 0) {
      // 2 color
      res1 = 2;
      FOR(i, 0, n) { res2[i] = i % 2; }

    } else {
      // 3 color
      res1 = 3;
      FOR(i, 0, n - 1) { res2[i] = i % 2; }
      res2[n - 1] = 2;
    }

  } else if (single) {
    res1 = 1;
    fill(ALL(res2), 0);

  } else {
    // Otherwise 2-colorable each non-loop component
    res1 = 2;
    res2[i0 % n] = 0;
    FOR(i, i0 + 1, i0 + n) {
      if (ls[(i - 1) % n] == ls[i % n]) {
        res2[i % n] = 0;
      } else {
        res2[i % n] = !res2[(i - 1) % n];
      }
    }
  }

  cout << res1 << endl;
  FOR(i, 0, n) {
    if (i) cout << " ";
    cout << (res2[i] + 1);
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { dbg(i); mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1328D/main.cpp --check

%%%% begin
4
5
1 2 1 2 2
6
1 2 2 1 2 2
5
1 2 1 2 3
3
10 10 10
%%%%
2
1 2 1 2 2
2
2 1 2 1 2 1
3
2 3 2 3 1
1
1 1 1
%%%% end
*/
