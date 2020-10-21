// WIP

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
  int n, x, y;
  cin >> n >> x >> y;
  vector<int> ls(n);
  cin >> ls;

  // n = x + z + w
  // x : exact match
  // z : shuffle
  // w : set to unused color
  int w = n - y;
  int z = y - x;
  int m = z + w;
  dbgv(n, x, z, w);

  vector<int> cnts(n + 2);
  for (auto c : ls) { cnts[c]++; }

  set<tuple<int, int>> heap; // (count, color)
  FOR(i, 0, n + 2) { heap.insert({cnts[i], i}); }
  dbg(heap);

  // TODO: trivial case
  if (x == n) { return; }

  // Remove "x" from heap (correct position)
  FOR(_, 0, x) {
    auto [cnt, i] = *--heap.end(); heap.erase(--heap.end());
    heap.insert({cnt - 1, i});
  }
  dbg(heap);

  // TODO: Derive possible max shuffle
  int max_shuffle = 0;

  // // Remove "w" from heap
  // FOR(_, 0, w) {
  //   auto [cnt, i] = *--heap.end(); heap.erase(--heap.end());
  //   heap.insert({cnt - 1, i});
  // }
  // dbg(heap);

  // // Check "z" shuffle is possible
  // bool ok = (z - w) >= 2 * get<0>(*--heap.end());
  // dbg(ok);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1382E/main.cpp --check

%%%% begin
1
6 0 3
1 2 2 2 2 2
%%%%
%%%% end

%%%% begin
1
5 3 4
1 1 2 1 2
%%%%
%%%% end

%%%% begin
7
5 2 4
3 1 1 2 5
5 3 4
1 1 2 1 2
4 0 4
5 5 3 3
4 1 4
2 3 2 3
6 1 2
3 2 1 1 1 1
6 2 4
3 3 2 1 1 1
6 2 6
1 1 3 2 1 1
%%%%
YES
3 1 6 1 2
YES
3 1 1 1 2
YES
3 3 5 5
NO
YES
4 4 4 4 3 1
YES
3 1 3 1 7 7
YES
2 3 1 1 1 1
%%%% end
*/
