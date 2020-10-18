// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, m; // [1, 2000]
  cin >> n >> m;
  int i0, j0;
  cin >> i0 >> j0;
  int x, y; // [1, 10^9]
  cin >> x >> y;
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;
  i0--; j0--;

  //
  // CLAIM.
  //   for path from (x, y) to (x', y'),
  //     #R - #L = x' - x
  //   i.e.
  //     #R = #L + (x' - x)
  //

  // Compute "L" distance
  const int kInf = 1e9 + 1;
  const array<int, 3> kMoves[] = {
      {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {1, 0, -1}}; // (weight, di, dj)

  vector<vector<int>> dists(n, vector<int>(m, kInf));
  set<array<int, 3>> heap; // (distance, i, j)
  heap.insert({dists[i0][j0] = 0, i0, j0});
  while (!heap.empty()) {
    auto [d, i, j] = *heap.begin(); heap.erase(heap.begin());
    if (d > x) { break; }
    for (auto [w, di, dj] : kMoves) {
      int ii = i + di, jj = j + dj;
      if (!(0 <= ii && ii < n && 0 <= jj && jj < m)) { continue; }
      if (board[ii][jj] == '*') { continue; }
      if (d + w >= dists[ii][jj]) { continue; }
      heap.erase({dists[ii][jj], ii, jj});
      heap.insert({dists[ii][jj] = d + w, ii, jj});
    }
  }
  dbg2(dists);

  int res = 0;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == '*') { continue; }
      int l = dists[i][j];
      int r = l + j - j0;
      res += (l <= x && r <= y);
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1063B/main.cpp

%%%% begin
4 5
3 2
1 2
.....
.***.
...**
*....
%%%%
10
%%%% end

%%%% begin
4 4
2 2
0 1
....
..*.
....
....
%%%%
7
%%%% end
*/
