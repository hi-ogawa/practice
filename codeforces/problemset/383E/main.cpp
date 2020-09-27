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
  int n; // [1, 10^4]
  cin >> n;
  vector<string> ls(n);
  cin >> ls;

  vector<set<int>> sets(n);
  FOR(i, 0, n) {
    for (auto c : ls[i]) {
      sets[i].insert(c - 'a');
    }
  }

  const int k = 24; // a, b, .., x

  //
  // PROP.
  //   Define F, G: P(X) -> N by
  //     F(T) = #{i | Si ∧ T ≠ ∅},
  //     G({x})       = + #{i | x ∈ Si},      (G does "inclusion exclusion" for three elements)
  //     G({x, y})    = - #{i | x, y ∈ Si},
  //     G({x, y, z}) = + #{i | x, y, z ∈ Si},
  //   then,
  //     F(T) = ∑_{S ⊆ T} G(S)
  //

  // DP for sum over subsets
  vector<int> dp(1 << k, 0);
  for (auto& s : sets) {
    // Define G
    for (auto x : s) { dp[1 << x]++; }
    auto it = s.begin();
    if (s.size() == 2) {
      int x = *it, y = *next(it);
      dp[(1 << x) | (1 << y)]--;
    }
    if (s.size() == 3) {
      int x = *it, y = *next(it), z = *next(it, 2);
      dp[(1 << x) | (1 << y)]--;
      dp[(1 << y) | (1 << z)]--;
      dp[(1 << z) | (1 << x)]--;
      dp[(1 << x) | (1 << y) | (1 << z)]++;
    }
  }
  FOR(x, 0, k) {
    FOR(s, 0, 1 << k) {
      if (s & (1 << x)) { dp[s] += dp[s ^ (1 << x)]; }
    }
  }

  int res = 0;
  FOR(s, 0, 1 << k) {
    res ^= dp[s] * dp[s];
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/383E/main.cpp --check

%%%% begin
5
abc
aaa
ada
bcd
def
%%%%
0
%%%% end
*/
