// TLE, MLE

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
  int n; // <= 10^6
  cin >> n;
  vector<int> ls(n);
  cin >> ls;
  int k = *max_element(ALL(ls)); // <= 200

  vector<vector<int>> cnts(k + 1, vector<int>(n + 1));
  auto cnts_rev = cnts;
  FOR(i, 0, n) {
    FOR(v, 0, k + 1) {
      cnts[v][i + 1] = cnts[v][i] + (ls[i] == v);
      cnts_rev[v][i + 1] = cnts_rev[v][i] + (ls[n - 1 - i] == v);
    }
  }
  dbg2(cnts);
  dbg2(cnts_rev);

  int res = 0;
  FOR(v0, 0, k + 1) {
    if (cnts[v0][n] == 0) { continue; }

    FOR(i, 0, n + 1) {
      int c = cnts[v0][i];
      auto it = lower_bound(ALL(cnts_rev[v0]), c);
      assert(it != cnts_rev[v0].end());
      assert(*it == c);
      int i_rev = distance(cnts_rev[v0].begin(), it);
      int j = n - i_rev;
      if (j < i) { break; }
      FOR(v1, 0, k + 1) {
        int cc = cnts[v1][j] - cnts[v1][i];
        int t = 2 * c + cc;
        res = max(res, t);
      }
    }
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
python misc/run.py codeforces/problemset/1335E2/main.cpp --check

%%%% begin
1
6
1 5 6 3 2 3
%%%%
3
%%%% end

%%%% begin
1
8
1 1 2 2 3 2 1 1
%%%%
7
%%%% end

%%%% begin
6
8
1 1 2 2 3 2 1 1
3
1 3 3
4
1 10 10 1
1
26
2
2 1
3
1 1 1
%%%%
7
2
4
1
1
3
%%%% end
*/
