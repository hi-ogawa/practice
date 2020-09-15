// TLE

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

  int kInf = 1 << 30;
  vector<int> dp(n, kInf);
  dp[0] = 0;
  FOR(i, 0, n - 1) {
    dp[i + 1] = min(dp[i + 1], dp[i] + 1);
    int h = ls[i];
    int hh = ls[i + 1];
    if (h == hh) { continue; }
    if (h < hh) {
      FOR(j, i + 2, n) {
        if (ls[j] < hh) {
          dp[j] = min(dp[j], dp[i] + 1);
          hh = ls[j];
        }
        if (ls[j] <= h) { break; }
      }
      continue;
    }
    if (h > hh) {
      FOR(j, i + 2, n) {
        if (ls[j] > hh) {
          dp[j] = min(dp[j], dp[i] + 1);
          hh = ls[j];
        }
        if (ls[j] >= h) { break; }
      }
      continue;
    }
  }

  int res = dp[n - 1];
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest669/d/main.cpp --check

%%%% begin
5
1 3 1 4 5
%%%%
3
%%%% end

%%%% begin
4
4 2 2 4
%%%%
1
%%%% end

%%%% begin
2
1 1
%%%%
1
%%%% end

%%%% begin
5
100 1 100 1 100
%%%%
2
%%%% end
*/
