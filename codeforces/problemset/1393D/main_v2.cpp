// AC

// NOTE: try reducing vector copy, but then code is messy...

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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
  vector<vector<char>> board(n, vector<char>(m)); // lowercase
  cin >> board;

  //
  // Find maximal triangle size (separately four directions by rotating borad)
  //   x
  //   xx
  //   ...
  //   x....x
  //
  auto solve = [&](const vector<vector<char>>& board) -> vector<vector<int>> {
    int n = board.size();
    int m = board[0].size();

    // Horizontal segments for each row
    vector<vector<array<int, 2>>> rows_segs(n);
    FOR(i, 0, n) {
      auto& segs = rows_segs[i];
      FOR(j, 0, m) {
        if (j == 0 || board[i][j - 1] != board[i][j]) {
          segs.push_back({j, -1});
        }
        segs.back()[1] = j + 1;
      }
    }

    vector<vector<int>> res(n, vector<int>(m));
    FOR(j, 0, m) {
      FOR(i, 0, n) {
        if (i == 0 || board[i - 1][j] != board[i][j]) {
          res[i][j] = 1;
          continue;
        }
        auto& segs = rows_segs[i];
        auto it = upper_bound(ALL(segs), array<int, 2>({j + 1, 0}));
        assert(it != segs.begin());
        auto [j0, j1] = *prev(it);
        res[i][j] = min(j1 - j, res[i - 1][j] + 1);
      }
    }
    return res;
  };

  // Reuse "solve" by rotating board
  auto rotate = [&](const auto& board, auto& res) {
    int n = board.size(), m = board[0].size();
    FOR(j, 0, m) {
      FOR(i, 0, n) {
        res[j][i] = board[n - 1 - i][j];
      }
    }
  };

  array<vector<vector<int>>, 4> res;
  vector<vector<char>> board2(m, vector<char>(n));

  res[0] = solve(board);

  rotate(board, board2);
  res[1] = solve(board2);

  rotate(board2, board);
  res[2] = solve(board);

  rotate(board, board2);
  res[3] = solve(board2);

  auto resx = res[0];
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      resx[i][j] = min(resx[i][j], res[1][j][n - 1 - i]);
    }
  }
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      resx[i][j] = min(resx[i][j], res[2][n - 1 - i][m - 1 - j]);
    }
  }
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      resx[i][j] = min(resx[i][j], res[3][m - 1 - j][i]);
    }
  }

  int resy = 0;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      resy += resx[i][j];
    }
  }
  cout << resy << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1393D/main_v2.cpp

%%%% begin
3 3
aaa
aaa
aaa
%%%%
10
%%%% end

%%%% begin
3 4
abab
baba
abab
%%%%
12
%%%% end

%%%% begin
5 5
zbacg
baaac
aaaaa
eaaad
weadd
%%%%
31
%%%% end
*/
