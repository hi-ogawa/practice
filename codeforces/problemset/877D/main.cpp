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

template<class T> using V = vector<T>;

// Main
void mainCase() {
  int n, m, k; // [1, 1000]
  cin >> n >> m >> k;
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;
  int i0, j0, i1, j1;
  cin >> i0 >> j0 >> i1 >> j1;
  i0--; j0--; i1--; j1--;

  const array<int, 2> kDirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  const ll kInf = 1e18;

  V<V<array<ll, 4>>> dists(n, V<array<ll, 4>>(m, {kInf, kInf, kInf, kInf}));

  // Optimization for naive "set<array<ll, 4>> heap; // (distance, i, j, z)"
  auto compare = [&](auto x, auto y) {
    auto [xi, xj, xz] = x;
    auto [yi, yj, yz] = y;
    return dists[xi][xj][xz] < dists[yi][yj][yz];
  };
  multiset<array<int, 3>, decltype(compare)> heap(compare); // (i, j, z)

  FOR(z, 0, 4) {
    dists[i0][j0][z] = 0;
    heap.insert({i0, j0, z});
  }

  while (!heap.empty()) {
    auto [i, j, z] = *heap.begin(); heap.erase(heap.begin());
    auto d = dists[i][j][z];
    // Move one step
    FOR(_, 0, 1) { // trick to use "continue"
      auto [di, dj] = kDirs[z];
      int ii = i + di, jj = j + dj;
      if (!(0 <= ii && ii < n && 0 <= jj && jj < m)) { continue; }
      if (board[ii][jj] == '#') { continue; }
      auto d_next = d + 1;
      auto& dd = dists[ii][jj][z];
      if (d_next >= dd) { continue; }
      heap.erase({ii, jj, z});
      dd = d_next;
      heap.insert({ii, jj, z});
    }
    // Change direction
    FOR(zz, 0, 4) {
      if (zz == z) { continue; }
      // Round to multiple of "k"
      auto d_next = ((d + (k - 1)) / k) * k;
      auto& dd = dists[i][j][zz];
      if (d_next >= dd) { continue; }
      heap.erase({i, j, zz});
      dd = d_next;
      heap.insert({i, j, zz});
    }
  }
  dbg2(dists);

  auto res = *min_element(ALL(dists[i1][j1]));
  dbg(res);

  if (res == kInf) {
    res = -1;
  } else {
    res = (res + (k - 1)) / k;
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/877D/main.cpp

%%%% begin
3 4 4
....
###.
....
1 1 3 1
%%%%
3
%%%% end

%%%% begin
3 4 1
....
###.
....
1 1 3 1
%%%%
8
%%%% end

%%%% begin
2 2 1
.#
#.
1 1 2 2
%%%%
-1
%%%% end
*/
