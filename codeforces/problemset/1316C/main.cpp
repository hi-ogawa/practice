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
  int n, m, p;
  cin >> n >> m >> p;
  vector<int> f(n), g(m);
  cin >> f >> g;

  //
  // CLAIM.
  //     p † f.g <=> p † f and p † g
  //   So, writing
  //     i0 = min { i | p † ai }
  //     j0 = min { j | p † bj }
  //     f = f1 + f2 where f2 = ai0 . x^i0 + ...
  //     g = g1 + g2 where g2 = bj0 . x^j0 + ...
  //   Then,
  //     f.g = (f1.g1 + f1.g2 + f2.g1) + f2.g2
  //     p | (f1.g1 + f1.g2 + f2.g1)
  //     p † f2.g2 = c_{i0 + j0} x^{i0 + j0} + ....
  //

  int i0 = -1, j0 = -1;
  FOR(i, 0, n) {
    if (f[i] % p != 0) { i0 = i; break; }
  }
  FOR(j, 0, m) {
    if (g[j] % p != 0) { j0 = j; break; }
  }
  assert(i0 >= 0);
  assert(j0 >= 0);

  int res = i0 + j0;
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1316C/main.cpp --check

%%%% begin
3 2 2
1 1 2
2 1
%%%%
1
%%%% end

%%%% begin
2 2 999999937
2 1
3 1
%%%%
2
%%%% end
*/
