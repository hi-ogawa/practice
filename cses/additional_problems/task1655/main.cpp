// TLE

// NOTE: this problem can be seen as a special case of codeforces/problemset/706D/main_v2.cpp
//       it should be correct but not fast enough (1.3 sec on my machine)

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

  // cum xor
  auto ps = ls;
  FOR(i, 1, n) { ps[i] ^= ps[i - 1]; }

  multiset<int> ms(ALL(ps));

  // Find max { u ^ x | u \in ms }
  auto solve = [&](int x) -> int {
    // Determine from MSB
    int res = 0;
    int q = 0; // Matched MSB
    auto itl = ms.begin(); auto itr = ms.end(); // [l, r)
    for (int b = 30; b >= 0; b--) {
      int qq = q | (1 << b);
      auto it = ms.lower_bound(qq);
      // Check exclusive to "x[b]"
      if (x & (1 << b)) {
        if (itl != it) { // Found [l, qq)
          res = res | (1 << b);
          itr = it;
        } else {
          q = qq;
        }
      } else {
        if (itr != it) { // Found [qq, r)
          res = res | (1 << b);
          itl = it;
          q = qq;
        }
      }
    }
    return res;
  };

  int res = *--ms.end();
  FOR(i, 0, n - 1) {
    // Find max xor segment starting from "i"
    ms.erase(ms.find(ps[i]));
    res = max(res, solve(ps[i]));
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1655/main.cpp --check

%%%% begin
4
5 1 5 9
%%%%
13
%%%% end
*/
