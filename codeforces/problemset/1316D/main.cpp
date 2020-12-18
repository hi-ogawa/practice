// AC

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

// DSU
struct Dsu {
  vector<int> parents;
  Dsu(int n) {
    parents.resize(n);
    iota(ALL(parents), 0);
  }
  int find(int x) {
    if (x == parents[x]) { return x; }
    return parents[x] = find(parents[x]);
  }
  void merge(int x, int y) {
    parents[find(x)] = find(y);
  }
};

using ivec2 = array<int, 2>;
const ivec2 kDirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
map<ivec2, char> kDirToChar = {{{1, 0}, 'D'}, {{-1, 0}, 'U'}, {{0, 1}, 'R'}, {{0, -1}, 'L'}};

// Main
void mainCase() {
  int n; // [1, 10^3]
  cin >> n;
  vector<vector<ivec2>> board(n, vector<ivec2>(n));
  cin >> board;

  // Components of loop cells or blocked destinations

  auto enc = [&](int i, int j) -> int { return i * n + j; }; // Encode dsu index

  Dsu dsu(enc(n, n));

  FOR(i, 0, n) {
    FOR(j, 0, n) {
      for (auto [di, dj] : kDirs) {
        int ii = i + di, jj = j + dj;
        if (!(0 <= ii && ii < n && 0 <= jj && jj < n)) { continue; }
        if (board[i][j] == board[ii][jj]) {
          dsu.merge(enc(i, j), enc(ii, jj));
        }
      }
    }
  }

  map<int, vector<ivec2>> compos;
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      compos[dsu.find(enc(i, j))].push_back({i, j});
    }
  }
  dbg2(compos);

  bool ok = 1;
  vector<vector<ivec2>> loops, blocks;
  for (auto& [_k, vs] : compos) {
    auto [ci, cj] = board[vs[0][0]][vs[0][1]];
    if (ci == -1 && cj == -1) {
      // Loop cell component size >= 2
      if (vs.size() == 1) { ok = 0; break; }
      loops.push_back(vs);
    } else {
      // Block destination is within the component
      bool found = 0;
      for (auto ij : vs) {
        if (ij == ivec2({ci - 1, cj - 1})) { found = 1; break; }
      }
      if (!found) { ok = 0; break; }
      blocks.push_back(vs);
    }
  }
  cout << (ok ? "VALID" : "INVALID") << "\n";
  if (!ok) { return; }

  // BFS to determine directions
  vector<vector<char>> res(n, vector<char>(n));
  vector<vector<bool>> done(n, vector<bool>(n));

  auto bfs = [&](ivec2 root) {
    deque<ivec2> q;
    q.push_back(root);
    done[root[0]][root[1]] = 1;
    while (!q.empty()) {
      auto [i, j] = q.front(); q.pop_front();
      for (auto [di, dj] : kDirs) {
        int ii = i + di, jj = j + dj;
        if (!(0 <= ii && ii < n && 0 <= jj && jj < n)) { continue; }
        if (done[ii][jj]) { continue; }
        if (board[ii][jj] != board[i][j]) { continue; }
        done[ii][jj] = 1;
        res[ii][jj] = kDirToChar[{-di, -dj}];
        q.push_back({ii, jj});
      }
    }
  };

  // For blocked destinations
  for (auto& vs : blocks) {
    auto [i, j] = board[vs[0][0]][vs[0][1]];
    i--; j--;
    res[i][j] = 'X';
    bfs({i, j});
  }

  // For loop cells
  for (auto& vs : loops) {
    // Pick root and its neighbor to make loop
    auto [i, j] = vs[0];
    bool found = 0;
    for (auto [di, dj] : kDirs) {
      int ii = i + di, jj = j + dj;
      if (!(0 <= ii && ii < n && 0 <= jj && jj < n)) { continue; }
      if (done[ii][jj]) { continue; }
      if (board[ii][jj] != board[i][j]) { continue; }
      res[i][j] = kDirToChar[{di, dj}];
      found = 1;
      break;
    }
    assert(found);
    bfs({i, j});
  }

  FOR(i, 0, n) {
    FOR(j, 0, n) {
      cout << res[i][j];
    }
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1316D/main.cpp

%%%% begin
2
1 1 1 1
2 2 2 2
%%%%
VALID
XL
RX
%%%% end

%%%% begin
3
-1 -1 -1 -1 -1 -1
-1 -1 2 2 -1 -1
-1 -1 -1 -1 -1 -1
%%%%
VALID
RRD
UXD
ULL
%%%% end
*/
