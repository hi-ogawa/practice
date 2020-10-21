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
  int n, m;
  cin >> n >> m;
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;

  // Segment of each row
  vector<array<int, 2>> segs(n, {-1, -1});
  bool ok1 = 1;
  FOR(i, 0, n) {
    vector<array<int, 2>> tmp;
    FOR(j, 0, m) {
      if ((j == 0 || board[i][j - 1] == '.') && board[i][j] == '#') {
        tmp.push_back({j, -1});
      }
      if (board[i][j] == '#' && (j == m - 1 || board[i][j + 1] == '.')) {
        tmp.back()[1] = j;
      }
    }
    if (tmp.size() == 0) { continue; }
    if (tmp.size() > 2) { ok1 = 0; break; }
    segs[i] = tmp[0];
  }
  dbg(segs);
  if (!ok1) { cout << -1 << endl; return; }

  // Connected components
  vector<vector<array<int, 2>>> compos;
  {
    int i = 0;
    while (i < n) {
      if (segs[i][0] == -1) { i++; continue; }
      auto& c = compos.emplace_back();
      auto [l, r] = segs[i];
      c.push_back({l, r});
      i++;
      while (i < n) {
        if (segs[i][0] == -1) { break; }
        auto [ll, rr] = segs[i];
        bool isect = (l <= ll && ll <= r) || (ll <= l && l <= rr);
        if (!isect) { break; }
        c.push_back({ll, rr});
        l = ll; r = rr;
        i++;
      }
    }
  }
  dbg(compos);

  // Check validity of decomposition
  // TODO: it's okay to have empty space on diagonal
  int k = compos.size();
  vector<array<int, 2>> widths(k);
  int kInf = 1 << 30;
  FOR(p, 0, k) {
    int i0 = kInf, j0 = -kInf;
    for (auto [i, j] : compos[p]) {
      i0 = min(i0, i);
      j0 = max(j0, j);
    }
    widths[p] = {i0, j0};
  }
  sort(ALL(widths));
  dbg(widths);

  bool ok3 = 1;
  FOR(p, 0, k - 1) {
    if (widths[p][1] >= widths[p + 1][1]) {
      ok3 = 0;
      break;
    }
  }
  if (!ok3) { cout << -1 << endl; return; }

  // Check validity of each component
  bool ok4 = 1;
  for (auto& c : compos) {
    bool t0 = 0, t1 = 0;
    FOR(p, 0, (int)c.size() - 1) {
      if (!t0 && c[p][0] < c[p + 1][0]) {
        t0 = 1;
      }
      if (!t1 && c[p][1] > c[p + 1][1]) {
        t1 = 1;
      }
      if (t0 && c[p][0] > c[p + 1][0]) {
        ok4 = 0; break;
      }
      if (t1 && c[p][0] < c[p + 1][0]) {
        ok4 = 0; break;
      }
    }
    if (!ok4) { break; }
  }
  if (!ok4) { cout << -1 << endl; return; }

  int res = k;
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
python misc/run.py codeforces/problemset/1344B/main.cpp --check

%%%% begin
2 2
. .
. .
%%%%
0
%%%% end

%%%% begin
3 3
.#.
###
##.
%%%%
1
%%%% end

%%%% begin
4 5
....#
####.
.###.
.#...
%%%%
2
%%%% end
*/
