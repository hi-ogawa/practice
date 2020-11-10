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
  int n, m; // [1, 1500]
  cin >> n >> m;
  int k1, k2; // [1, 5 x 10^5]
  cin >> k1 >> k2;
  vector<array<int, 2>> ls1(k1), ls2(k2);
  cin >> ls1 >> ls2;
  for (auto& [x, y] : ls1) { x--; y--; }
  for (auto& [x, y] : ls2) { x--; y--; }

  // Light positions per row/col
  vector<vector<int>> rows(n), cols(m);
  for (auto [i, j] : ls1) {
    rows[i].push_back(j);
    cols[j].push_back(i);
  }
  for (auto& xs : rows) { sort(ALL(xs)); }
  for (auto& xs : cols) { sort(ALL(xs)); }
  dbg2(rows);
  dbg2(cols);

  vector<vector<int>> board(n, vector<int>(m, 0)); // 1 if blocked
  vector<vector<int>> res(n, vector<int>(m));      // 1 if illuminated
  for (auto [i, j] : ls2) {
    board[i][j] = 1;
  }

  // Check horizontal/vertical separately

  // Horizontal segments
  FOR(i, 0, n) {
    vector<array<int, 2>> segs;
    FOR(j, 0, m) {
      if (j == 0 || board[i][j] != board[i][j - 1]) {
        segs.push_back({j, -1});
      }
      segs.back()[1] = j + 1;
    }
    for (auto [l, r] : segs) {
      if (board[i][l] == 1) { continue; }
      // Check if there's bulb in [l, r)
      auto& ps = rows[i];
      auto it = lower_bound(ALL(ps), l);
      if (it == ps.end() || *it >= r) { continue; }
      FOR(j, l, r) {
        res[i][j] = 1;
      }
    }
  }

  // Vertical segments
  FOR(j, 0, m) {
    vector<array<int, 2>> segs;
    FOR(i, 0, n) {
      if (i == 0 || board[i][j] != board[i - 1][j]) {
        segs.push_back({i, -1});
      }
      segs.back()[1] = i + 1;
    }
    for (auto [l, r] : segs) {
      if (board[l][j] == 1) { continue; }
      auto& ps = cols[j];
      auto it = lower_bound(ALL(ps), l);
      if (it == ps.end() || *it >= r) { continue; }
      FOR(i, l, r) {
        res[i][j] = 1;
      }
    }
  }

  dbg2(res);

  int res2 = 0;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      res2 += res[i][j];
    }
  }
  cout << res2 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc182/e/main.cpp

%%%% begin
3 3 2 1
1 1
2 3
2 2
%%%%
7
%%%% end

%%%% begin
4 4 3 3
1 2
1 3
3 4
2 3
2 4
3 2
%%%%
8
%%%% end

%%%% begin
5 5 5 1
1 1
2 2
3 3
4 4
5 5
4 2
%%%%
24
%%%% end
*/
