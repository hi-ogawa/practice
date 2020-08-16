// AFTER EDITORIAL, AC

//
// PROP.
//   For bipartite graph (and corresponding flow graph),
//     <max independent set>
//       = V - <min cut>
//       = V - <max flow>
//       = V - <max matching>
//

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
  int n; // <= 10^6
  cin >> n;
  vector<array<int, 3>> ls(n); // 1 <= x <= 10^9
  cin >> ls;
  sort(ALL(ls)); // for debug
  dbg(ls);

  enum { kIn, kOut }; // kIn < kOut
  vector<tuple<int, int, int, int>> events; // (x, in/out, 1/2, idx)
  FOR(i, 0, n) {
    auto [l, r, t] = ls[i];
    events.push_back({l, kIn, t, i});  // actually only use (in, 2) and (out, 1)
    events.push_back({r, kOut, t, i});
  }
  sort(ALL(events));

  //
  // PROP. (Normal form)
  //   For any valid mathing, there exists correponding matching which has "below property",
  //   after swapping out some pairs.
  //

  multiset<int> r2s; // 2nd type right end
  ll res = 0;
  for (auto [x, io, t, i] : events) {
    if (io == kIn && t == 2) {
      r2s.insert(ls[i][1]);
    }
    if (io == kOut && t == 1) {
      if (r2s.empty()) { continue; }

      int l1 = ls[i][0];
      auto it = r2s.lower_bound(l1);
      if (it == r2s.end()) { continue; }

      dbgv(i, ls[i], *it);
      res++;
      r2s.erase(it);
    }
  }
  dbgv(res, n - res);

  ll res2 = n - res;
  cout << res2 << endl;
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
python misc/run.py codeforces/edu92/f/main_v2.cpp --check

%%%% begin
11
7 12 2
5 11 1
1 13 1
12 12 2
6 10 2
9 11 1
8 11 1
2 6 1
2 10 1
5 6 2
1 4 2
%%%%
6
%%%% end

%%%% begin
3
1 3 1
4 6 2
2 5 1
%%%%
2
%%%% end

%%%% begin
5
5 8 1
1 3 2
3 4 2
6 6 1
2 10 2
%%%%
4
%%%% end

%%%% begin
7
19 20 1
13 15 2
6 11 2
4 10 1
14 17 1
13 13 2
5 9 1
%%%%
5
%%%% end
*/
