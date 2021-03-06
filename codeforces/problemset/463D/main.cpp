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
  int n, k;
  cin >> n >> k;
  vector<vector<int>> ls(k, vector<int>(n));
  cin >> ls;
  for (auto& xs : ls) { for (auto& x : xs) x--; } // zero-based

  // WLOG, ls[0] = (0, 1, .., n - 1)
  vector<int> enc(n);
  FOR(i, 0, n) { enc[ls[0][i]] = i; }
  FOR(i, 0, k) {
    FOR(j, 0, n) {
      ls[i][j] = enc[ls[i][j]];
    }
  }
  dbg2(ls);

  // Then, problem is equivalent to finding common increasing subseq. of ls[1], .. ls[k - 1];
  // dp[x] = max common incr subseq end with x
  vector<int> dp(n, 1);
  auto ls_inv = ls;
  FOR(i, 0, k) {
    FOR(j, 0, n) {
      ls_inv[i][ls[i][j]] = j;
    }
  }
  FOR(x, 1, n) {
    FOR(y, 0, x) {
      bool ok = 1;
      FOR(i, 1, k) {
        if (ls_inv[i][y] > ls_inv[i][x]) { ok = 0; break; }
      }
      if (ok) {
        dp[x] = max(dp[x], dp[y] + 1);
      }
    }
  }
  dbg(dp);

  int res = *max_element(ALL(dp));
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/463D/main.cpp --check

%%%% begin
4 3
1 4 2 3
4 1 2 3
1 2 4 3
%%%%
3
%%%% end
*/
