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
  vector<int> ls(n);
  cin >> ls;

  // True if ∃non-consecutive subseq of length "m" bounded by "b" within [i0, i1)
  auto evaluate = [&](int i0, int i1, int m, int b) -> bool {
    int cnt = 0;
    int last = -2;
    FOR(i, i0, i1) {
      if (ls[i] <= b && i != last + 1) {
        cnt++;
        last = i;
      }
    }
    return cnt >= m;
  };

  // Search min{ b | evaluate(b) = 1 }
  auto search = [&]() -> int {
    // (b0, b1]
    int b0 = 0;
    int b1 = *max_element(ALL(ls));
    while (b0 + 1 < b1) {
      int b = (b0 + b1 + 1) / 2;

      // Take care correct alternation for k odd/even
      bool e1, e2;
      if (k % 2 == 1) {
        e1 = evaluate(0, n,     (k + 1) / 2, b);
        e2 = evaluate(1, n - 1, k / 2      , b);
      } else {
        e1 = evaluate(0, n - 1, k / 2, b);
        e2 = evaluate(1, n,     k / 2, b);
      }
      if (e1 || e2) {
        b1 = b;
      } else {
        b0 = b;
      }
    }
    return b1;
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
python misc/run.py codeforces/problemset/1370D/main.cpp --check

%%%% begin
6 4
5 3 50 2 4 5
%%%%
3
%%%% end
*/
