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
  int n, m; // [1, 10^6], [1, 8]
  cin >> n >> m;
  vector<vector<int>> ls(n, vector<int>(m));
  cin >> ls;

  // f(x) = true  \iff  ∃i,j max(ls[i], ls[j]) >= (x, x, .., x)
  auto evaluate = [&](int x) -> tuple<bool, int, int> {
    // Search 2^m segments as bitmask
    vector<int> segs((1 << m), -1);
    FOR(i, 0, n) {
      int mask = 0;
      FOR(j, 0, m) {
        if (ls[i][j] >= x) {
          mask |= (1 << j);
        }
      }
      segs[mask] = i;
    }

    // Find max(mask0, mask1) = (1, 1, .., 1)
    FOR(m0, 0, 1 << m) {
      if (segs[m0] == -1) { continue; }
      FOR(m1, m0, 1 << m) {
        if (segs[m1] == -1) { continue; }
        if ((m0 | m1) == ((1 << m) - 1)) {
          return {1, segs[m0], segs[m1]};
        }
      }
    }
    return {0, -1, -1};
  };

  // max { x | f(x) = true }
  auto search = [&]() -> int {
    int x0 = 0, x1 = 1 << 30; // [x0, x1)
    while (x0 + 1 < x1) {
      int x = (x0 + x1) / 2;
      auto [ok, _i, _j] = evaluate(x);
      if (ok) {
        x0 = x;
      } else {
        x1 = x;
      }
    }
    return x0;
  };

  if (DEBUG) {
    dbg2(ls);
    FOR(x, 0, 5) { dbgv(x, evaluate(x)); }
  }

  int res = search();
  auto [_res, i, j] = evaluate(res);
  cout << (i + 1) << " " << (j + 1) << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1288D/main.cpp --check

%%%% begin
6 5
5 0 3 1 2
1 8 9 1 3
1 2 3 4 5
9 1 0 3 7
2 3 0 6 3
6 4 1 7 0
%%%%
1 5
%%%% end
*/
