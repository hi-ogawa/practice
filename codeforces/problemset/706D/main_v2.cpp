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
  int nq; // [1, 2x10^5]
  cin >> nq;
  vector<tuple<char, ull>> qs(nq); // x ∈ [1, 10^9]
  cin >> qs;

  multiset<int> ls;
  ls.insert(0);

  auto solve = [&](int x) -> int {
    // Determine from MSB
    int res = 0;
    int y = 0; // matched MSB
    auto itl = ls.begin();
    auto itr = ls.end();
    for (int b = 30; b >= 0; b--) {
      int z = y | (1 << b);
      auto it = ls.lower_bound(z);
      // Check exclusive to "x[b]"
      if (x & (1 << b)) {
        if (itl != it) { // found [l, z)
          res = res | (1 << b);
          itr = it;
        } else {
          y = z;
        }
      } else {
        if (itr != it) { // found [z, r)
          res = res | (1 << b);
          itl = it;
          y = z;
        }
      }
    }
    return res;
  };

  for (auto [t, x] : qs) {
    dbg(ls);
    if (t == '+') { ls.insert(x); }
    if (t == '-') { ls.erase(ls.find(x)); }
    if (t == '?') {
      int res = solve(x);
      cout << res << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/706D/main_v3.cpp --check

%%%% begin
8
+ 8
+ 9
+ 11
+ 6
+ 1
? 3
- 8
? 3
%%%%
11
10
%%%% end

%%%% begin
10
+ 8
+ 9
+ 11
+ 6
+ 1
? 3
- 8
? 3
? 8
? 11
%%%%
11
10
14
13
%%%% end
*/
