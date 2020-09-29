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
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;

  const int k = 20;
  const int k_mask = (1 << k) - 1;

  // dp[S] = #{i | ls[i] ⊆ S} by "sum over subsets"
  vector<int> dp(1 << k), dp_neg(1 << k);
  for (auto x : ls) {
    dp[x]++;
    dp_neg[~x & k_mask]++;
  }
  FOR(v, 0, k) {
    FOR(s, 0, 1 << k) {
      if (s & (1 << v)) {
        dp[s] += dp[s ^ (1 << v)];
        dp_neg[s] += dp_neg[s ^ (1 << v)];
      }
    }
  }

  // 1. x ∪ y = x  <=>  y ⊆ x
  // 2. x ∩ y = x  <=>  x ⊆ y  <=>  ¬y ⊆ ¬x
  // 3. x ∩ y ≠ ∅  <=>  not(x ∩ y = ∅)  <=>  not(y ⊆ ¬x)

  FOR(i, 0, n) {
    int x = ls[i], x_neg = ~ls[i] & k_mask;
    array<int, 3> res = {dp[x], dp_neg[x_neg], n - dp[x_neg]};
    FOR(j, 0, 3) {
      cout << res[j] << " \n"[j == 2];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1654/main.cpp --check

%%%% begin
5
3 7 2 9 2
%%%%
3 2 5
4 1 5
2 4 4
1 1 3
2 4 4
%%%% end
*/
