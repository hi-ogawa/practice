// WA

// NOTE: 1st test case is small counter example.

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
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;

  array<int, 2> v_beg;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == 'X') {
        v_beg = {i, j};
        break;
      }
    }
  }

  constexpr tuple<char, int, int> kDirs[] = {
      {'D',  1,  0},
      {'L',  0, -1},
      {'R',  0,  1},
      {'U', -1,  0}};

  int ok = 0;
  for (auto [_t, di, dj] : kDirs) {
    int ii = v_beg[0] + di, jj = v_beg[1] + dj;
    if (0 <= ii && ii < n && 0 <= jj && jj < m) {
      if (board[ii][jj] != '*') { ok = 1; break; } // at least can move one
    }
  }
  ok &= (k % 2 == 0); // parity check
  if (!ok) { cout << "IMPOSSIBLE" << endl; return; }

  // Optimal greedy choice for first k / 2 steps, then go back by "reverse"
  string path;
  int i = v_beg[0], j = v_beg[1];
  FOR(l, 0, k / 2) {
    for (auto [t, di, dj] : kDirs) {
      int ii = i + di, jj = j + dj;
      if (0 <= ii && ii < n && 0 <= jj && jj < m) {
        if (board[ii][jj] != '*') {
          path += t;
          i = ii; j = jj;
          break;
        }
      }
    }
    dbgv(i, j, path);
    assert((int)path.size() == l + 1);
  }

  string res;
  res += path;
  map<char, char> flip = {{'D', 'U'}, {'U', 'D'}, {'L', 'R'}, {'R', 'L'}};
  reverse(ALL(path));
  for (auto c : path) { res += flip[c]; }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/769C/main.cpp --check

%%%% begin
4 3 10
.X.
.*.
...
*..
%%%%
LDDRDRUUUL
%%%% end

%%%% begin
2 3 2
.**
X..
%%%%
RL
%%%% end

%%%% begin
5 6 14
..***.
*...X.
..*...
..*.**
....*.
%%%%
DLDDLLLRRRUURU
%%%% end

%%%% begin
3 3 4
***
*X*
***
%%%%
IMPOSSIBLE
%%%% end

*/
