// AFTER EDITORIAL, AC

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
  int n, nq; // <= 10^6
  cin >> n >> nq;
  vector<int> ls(n); // [1, n]
  cin >> ls;
  vector<int> qs(nq);
  cin >> qs;

  // Check if all removed
  int n_ins = 0;
  for (auto q : qs) { n_ins += (q > 0); }
  if (n + n_ins <= (nq - n_ins)) {
    cout << 0 << endl; return;
  }

  // f(x) = #{i | ls[i] <= x } after all operations
  auto evaluate = [&](int x) -> int {
    int c = 0;
    FOR(i, 0, n) { c += (ls[i] <= x); }
    for (auto q : qs) {
      if (q > 0) {
        if (q <= x) { c++; }
      }
      if (q < 0) {
        if (abs(q) <= c) { c--; }
      }
    }
    return c;
  };

  // min {x | f(x) >= 1 }
  auto search = [&]() -> int {
    // (x0, x1]
    int x0 = 0;
    int x1 = n;
    while (x0 + 1 < x1) {
      int x = (x0 + x1 + 1) / 2;
      if (evaluate(x) >= 1) {
        x1 = x;
      } else {
        x0 = x;
      }
    }
    return x1;
  };

  int res = search();
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
python misc/run.py codeforces/problemset/1354D/main.cpp --check

%%%% begin
5 4
1 2 3 4 5
-5 -1 -3 -1
%%%%
3
%%%% end
*/
