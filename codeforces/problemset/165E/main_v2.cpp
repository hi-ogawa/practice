// AC

// NOTE: In "main.cpp", we go up the poset. But here, we go down the poset.

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
  int n; // [1, 10^6]
  cin >> n;
  vector<int> ls(n); // [1, 4 x 10^6]
  cin >> ls;

  const int k = 22;
  const int k_mask = (1 << k) - 1;

  // dp[s] = i  \iff  s ⊆ ¬ls[i]  \iff  s ∧ ls[i] = ∅
  vector<int> dp(1 << k, -1);
  FOR(i, 0, n) {
    dp[(~ls[i]) & k_mask] = i;
  }
  for (int s = k_mask; s >= 0; s--) { // Go down the poset
    if (dp[s] == -1) { continue; }
    FOR(v, 0, k) {
      int s_neg_v = s & ~(1 << v);
      if (s == s_neg_v) { continue; }
      dp[s_neg_v] = dp[s];
    }
  }

  vector<int> res(n);
  FOR(i, 0, n) {
    int j = dp[ls[i]];
    if (j != -1) { j = ls[j]; }
    res[i] = j;
  }
  dbg(res);

  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/165E/main_v2.cpp --check

%%%% begin
2
1 6
%%%%
6 1
%%%% end

%%%% begin
2
90 36
%%%%
36 90
%%%% end

%%%% begin
4
3 6 3 6
%%%%
-1 -1 -1 -1
%%%% end

%%%% begin
5
10 6 9 8 2
%%%%
-1 8 2 2 8
%%%% end
*/
