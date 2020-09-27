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
  int n, nq; // [1, 3 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // all distinct
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  if (n == 1) {
    cout << ls[0] << "\n";
    FOR(i, 0, nq) { cout << ls[0] << "\n"; }
    return;
  }

  // n >= 2
  set<int> ls1, ls2; // local maximums/minimums
  ll sum1 = 0, sum2 = 0; // their sums

  auto insert = [&](int i) {
    int x, y, z;
    y = ls[i];
    if (i != 0)     { x = ls[i - 1]; }
    if (i != n - 1) { z = ls[i + 1]; }
    if (i == 0) {
      if (y > z) {
        ls1.insert(y);
        sum1 += y;
      }
    }
    if (i == n - 1) {
      if (x < y) {
        ls1.insert(y);
        sum1 += y;
      }
    }
    if (i != 0 && i != n - 1) {
      if (x < y && y > z) {
        ls1.insert(y);
        sum1 += y;
      }
      if (x > y && y < z) {
        ls2.insert(y);
        sum2 += y;
      }
    }
  };

  auto erase = [&](int i) {
    int x = ls[i];
    if (ls1.count(x)) { ls1.erase(x); sum1 -= x; return; }
    if (ls2.count(x)) { ls2.erase(x); sum2 -= x; return; }
  };

  auto update = [&](int i, int j) {
    set<int> ps;
    for (auto p : {i, j}) {
      for (auto d : {-1, 0, 1}) {
        if (0 <= p + d && p + d < n) { ps.insert(p + d); }
      }
    }
    for (auto p : ps) { erase(p); }
    swap(ls[i], ls[j]);
    for (auto p : ps) { insert(p); }
  };

  // Initialize
  FOR(i, 0, n) { insert(i); }
  cout << (sum1 - sum2) << "\n";

  // Update
  for (auto [i, j] : qs) {
    update(i - 1, j - 1);
    cout << (sum1 - sum2) << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest672/c2/main.cpp --check

%%%% begin
1
1 0
1
%%%%
1
%%%% end

%%%% begin
3
3 1
1 3 2
1 2
2 2
1 2
1 2
1 2
7 5
1 2 5 4 3 6 7
1 2
6 7
3 4
1 2
2 3
%%%%
3
4
2
2
2
9
10
10
10
9
11
%%%% end
*/
