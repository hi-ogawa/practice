// AC

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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// DSU
struct Dsu {
  vector<int> data_;
  Dsu(int n) { data_.resize(n); iota(ALL(data_), 0); }
  int find(int i) {
    if (i == data_[i]) { return i; }
    return data_[i] = find(data_[i]);
  }
  void merge(int dst, int src) {
    data_[find(src)] = find(dst);
  }
};

// Main
void mainCase() {
  ll n, m; // <= 10^3
  cin >> n >> m;

  vector<vector<char>> board(n, vector<char>(m, '?'));
  cin >> board;
  // DD2(board);

  auto encode = [&](int i, int j) -> int { return i * m + j; };

  Dsu dsu(encode(n, m));
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == '#') { continue; }
      if (i + 1 < n && board[i + 1][j] != '#') {
        dsu.merge(encode(i, j), encode(i + 1, j));
      }
      if (j + 1 < m && board[i][j + 1] != '#') {
        dsu.merge(encode(i, j), encode(i, j + 1));
      }
    }
  }
  // DD(dsu.data_);

  map<int, int> compos;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == '#') { continue; }
      compos[dsu.find(encode(i, j))]++;
    }
  }
  // DD(compos);

  ll res = compos.size();
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
python misc/run.py cses/graph_algorithms/task1192/main.cpp --check

%%%% begin
5 8
########
#..#...#
####.#.#
#..#...#
########
%%%%
3
%%%% end
*/
