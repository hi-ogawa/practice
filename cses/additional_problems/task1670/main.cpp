// AC

// TODO: probably, optimizing hash is not the purpose of this problem...

//
// PROP.
//   Puzzle is solvable.
//
//   PROOF.
//     First note that any permutation is generated by "adjacent swap" (cf. insertion sort).
//     So, it's possible to make it to
//       1 2 3
//       6 5 4
//       7 8 9
//     But from this, (6, 5, 4) can be swapped to (4, 5, 6).
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
#ifdef DEBUG
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
#else
#define dbg(X)
#define dbg2(X)
#define dbgv(...)
#endif
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
uint32_t hash32(uint32_t x) {
  x ^= x >> 16;
  x *= 0x7feb352dU;
  x ^= x >> 15;
  x *= 0x846ca68bU;
  x ^= x >> 16;
  return x;
}

using board_t = array<int, 9>;

struct BoardHash {
  size_t operator()(const board_t& xs) const {
    uint32_t p = xs[0] | (xs[1] << 4) | (xs[2] << 8) | (xs[3] << 12) | (xs[4] << 16);
    uint32_t q = xs[5] | (xs[6] << 4) | (xs[7] << 8) | (xs[8] << 12);
    return hash32(hash32(p) ^ q);
  }
};

// Main
void mainCase() {
  board_t ls;
  cin >> ls;

  board_t goal;
  iota(ALL(goal), 1);

  // BFS
  deque<board_t> q;
  unordered_map<board_t, int, BoardHash> dists;
  // map<board_t, int> dists; // TLE with tree

  q.push_back(ls);
  dists[ls] = 0;
  while (!q.empty()) {
    auto p = q.front(); q.pop_front();
    int dd = dists[p] + 1;
    if (p == goal) { break; }

    FOR(i, 0, 6) {
      auto pp = p;
      swap(pp[i], pp[i + 3]);
      if (dists.find(pp) == dists.end()) {
        dists[pp] = dd;
        q.push_back(pp);
      }
    }
    for (auto i : {1, 4, 7}) {
      for (auto j : {1, -1}) {
        auto pp = p;
        swap(pp[i], pp[i + j]);
        if (dists.find(pp) == dists.end()) {
          dists[pp] = dd;
          q.push_back(pp);
        }
      }
    }
  }

  int res = dists[goal];
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
python misc/run.py cses/additional_problems/task1670/main.cpp --check

%%%% begin
9 8 7
6 5 4
3 2 1
%%%%
16
%%%% end

%%%% begin
2 1 3
7 5 9
8 4 6
%%%%
4
%%%% end
*/