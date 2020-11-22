// CONTEST, AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
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
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;

  const int k = 26;
  vector<vector<array<int, 2>>> warps(k);
  int i_beg, j_beg, i_end, j_end;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      auto c = board[i][j];
      if (c == 'S') {
        i_beg = i, j_beg = j;
      }
      if (c == 'G') {
        i_end = i, j_end = j;
      }
      int t = c - 'a';
      if (0 <= t && t < k) {
        warps[t].push_back({i, j});
      }
    }
  }
  dbg(i_beg, j_beg, i_end, j_end);
  dbg2(warps);

  // BFS
  const int kInf = 1e9;
  const array<int, 2> kDirs[4] = {{1, 0}, {-1, 0} , {0, 1}, {0, -1}};

  vector<vector<int>> dists(n, vector<int>(m, kInf));
  vector<bool> used_warps(k);
  deque<array<int, 2>> q; // (i, j)

  dists[i_beg][j_beg] = 0;
  q.push_back({i_beg, j_beg});

  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop_front();
    if (i == i_end && j == j_end) { break; }
    int d = dists[i][j];

    // To neighbors
    for (auto [di, dj] : kDirs) {
      int ii = i + di, jj = j + dj;
      if (!(0 <= ii && ii < n && 0 <= jj && jj < m)) { continue; }
      if (board[ii][jj] == '#') { continue; }
      if (dists[ii][jj] <= d + 1) { continue; }
      dists[ii][jj] = d + 1;
      q.push_back({ii, jj});
    }

    // To warp
    int t = board[i][j] - 'a';
    if (0 <= t && t < k) {
      if (used_warps[t]) { continue; }
      used_warps[t] = 1;
      for (auto [ii, jj] : warps[t]) {
        if (dists[ii][jj] <= d + 1) { continue; }
        dists[ii][jj] = d + 1;
        q.push_back({ii, jj});
      }
    }
  }
  dbg2(dists);

  auto res = dists[i_end][j_end];
  if (res == kInf) { res = -1; }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc184/e/main.cpp

%%%% begin
2 5
S.b.b
a.a.G
%%%%
4
%%%% end

%%%% begin
11 11
S##...#c...
...#d.#.#..
..........#
.#....#...#
#.....bc...
#.##......#
.......c..#
..#........
a..........
d..#...a...
.#........G
%%%%
14
%%%% end

%%%% begin
11 11
.#.#.e#a...
.b..##..#..
#....#.#..#
.#dd..#..#.
....#...#e.
c#.#a....#.
.....#..#.e
.#....#b.#.
.#...#..#..
......#c#G.
#..S...#...
%%%%
-1
%%%% end
*/
