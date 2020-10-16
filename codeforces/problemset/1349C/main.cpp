
// NOTE: Misread the problem in a very obvious way...

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
  int n, m, nq; // n, m \in [1, 10^3], nq \in [10^5]
  cin >> n >> m >> nq;
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;
  vector<array<ll, 3>> qs(nq);
  cin >> qs;

  array<int, 2> cnts = {};
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      cnts[board[i][j] - '0']++;
    }
  }

  // All same color
  if (cnts[0] == 0) {
    FOR(i, 0, nq) { cout << 1 << "\n"; }
    return;
  }
  if (cnts[1] == 0) {
    FOR(i, 0, nq) { cout << 0 << "\n"; }
    return;
  }

  // Otherwise, state is determined by "parity" and "pre-period"
  const int kInf = 1e9;
  vector<vector<int>> dists(n, vector<int>(m, kInf));

  const array<int, 2> kDirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  // From each "b", find Manhattan distance to "neg b"
  auto solve = [&](char b) {
    set<array<int, 3>> heap; // (distance, i, j)
    FOR(i, 0, n) {
      FOR(j, 0, m) {
        if (board[i][j] == b) {
          for (auto [di, dj] : kDirs) {
            int ii = i + di, jj = j + dj;
            if (0 <= ii && ii < n && 0 <= jj && jj < m) {
              if (board[ii][jj] != b) {
                dists[i][j] = 0;
              }
            }
          }
          heap.insert({dists[i][j], i, j});
        }
      }
    }
    while (!heap.empty()) {
      auto [d, i, j] = *heap.begin(); heap.erase(heap.begin());
      for (auto [di, dj] : kDirs) {
        int ii = i + di, jj = j + dj;
        if (0 <= ii && ii < n && 0 <= jj && jj < m) {
          if (board[ii][jj] != b) { continue; }
          if (d + 1 >= dists[ii][jj]) { continue; }
          heap.erase({dists[ii][jj], ii, jj});
          heap.insert({dists[ii][jj] = d + 1, ii, jj});
        }
      }
    }
  };
  solve('0');
  solve('1');
  dbg2(dists);

  for (auto [i, j, p] : qs) {
    i--; j--;
    ll s1 = p - dists[i][j]; // Subtract pre-period
    ll s2 = board[i][j] - '0'; // Initial parity
    bool res = (s1 + s2) % 2;
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1349C/main.cpp

%%%% begin
4 5 0
00000
00000
00111
00111
%%%%
%%%% end

%%%% begin
3 3 3
000
111
000
1 1 1
2 2 2
3 3 3
%%%%
1
1
1
%%%% end

%%%% begin
5 2 2
01
10
01
10
01
1 1 4
5 1 4
%%%%
0
0
%%%% end

%%%% begin
5 5 3
01011
10110
01101
11010
10101
1 1 4
1 2 3
5 5 3
%%%%
1
0
1
%%%% end

%%%% begin
1 1 3
0
1 1 1
1 1 2
1 1 3
%%%%
0
0
0
%%%% end
*/
