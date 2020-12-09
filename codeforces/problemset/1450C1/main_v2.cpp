// WA

// NOTE: this doesn't take care "O" triples...

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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n; // [1, 300]
  cin >> n;
  vector<vector<char>> ls(n, vector<char>(n));
  cin >> ls;

  int num_crosses = 0;
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      num_crosses += (ls[i][j] == 'X');
    }
  }

  // Collect triplets
  using triple_t = array<array<int, 2>, 3>;
  vector<triple_t> triples;

  // - row wise
  FOR(i, 0, n) {
    FOR(j, 2, n) {
      int c = ls[i][j];
      if (c == '.') { continue; }
      if (c == ls[i][j - 1] && c == ls[i][j - 2]) {
        triples.push_back({{{i, j - 2}, {i, j - 1}, {i, j}}});
      }
    }
  }
  // - column wise
  FOR(i, 2, n) {
    FOR(j, 0, n) {
      int c = ls[i][j];
      if (c == '.') { continue; }
      if (c == ls[i - 1][j] && c == ls[i - 2][j]) {
        triples.push_back({{{i - 2, j}, {i - 1, j}, {i, j}}});
      }
    }
  }
  dbg2(triples);

  // Flip from cells with many triplets
  int m = triples.size();
  vector<vector<set<int>>> cell_to_triples(n, vector<set<int>>(n));
  FOR(t, 0, m) {
    for (auto [i, j] : triples[t]) {
      cell_to_triples[i][j].insert(t);
    }
  }
  set<tuple<int, array<int, 2>>> heap;
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      if (cell_to_triples[i][j].empty()) { continue; }
      heap.insert({cell_to_triples[i][j].size(), {i, j}});
    }
  }

  int num_flips = 0;
  while (!heap.empty()) {
    dbg(heap);
    auto [cnt, ij] = *--heap.end(); heap.erase(--heap.end());
    assert(cnt > 0);
    auto [i, j] = ij;
    ls[i][j] = 'O';
    num_flips++;

    FOR(ii, i - 2, i + 3) {
      if (!(0 <= ii && ii < n)) { continue; }
      heap.erase({cell_to_triples[ii][j].size(), {ii, j}});
    }
    FOR(jj, j - 2, j + 3) {
      if (!(0 <= jj && jj < n)) { continue; }
      heap.erase({cell_to_triples[i][jj].size(), {i, jj}});
    }

    for (auto t : cell_to_triples[i][j]) {
      for (auto [ii, jj] : triples[t]) {
        if (i == ii && j == jj) { continue; }
        cell_to_triples[ii][jj].erase(t);
      }
    }
    cell_to_triples[i][j].clear();

    FOR(ii, i - 2, i + 3) {
      if (!(0 <= ii && ii < n)) { continue; }
      if (cell_to_triples[ii][j].empty()) { continue; }
      heap.insert({cell_to_triples[ii][j].size(), {ii, j}});
    }
    FOR(jj, j - 2, j + 3) {
      if (!(0 <= jj && jj < n)) { continue; }
      if (cell_to_triples[i][jj].empty()) { continue; }
      heap.insert({cell_to_triples[i][jj].size(), {i, jj}});
    }
  }
  assert(3 * num_flips <= num_crosses);

  FOR(i, 0, n) {
    FOR(j, 0, n) {
      cout << ls[i][j];
    }
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1450C1/main_v2.cpp

%%%% begin
3
3
.X.
XXX
.X.
6
XX.XXX
XXXXXX
XXX.XX
XXXXXX
XX.X.X
XXXXXX
5
XXX.X
.X..X
XXX.X
..X..
..X..
%%%%
.X.
XOX
.X.
XX.XXO
XOXXOX
OXX.XX
XOOXXO
XX.X.X
OXXOXX
XOX.X
.X..X
XXO.O
..X..
..X..
%%%% end
*/
