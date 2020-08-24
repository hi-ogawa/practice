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

// Fenwick tree for rectangle sum
struct FenwickTree {
  int n_, m_;
  vector<vector<ll>> data_;
  FenwickTree(int n, int m) { n_ = n; m_ = m; data_.assign(n, vector<ll>(m, 0)); }
  void incr(int qi, int qj, ll qv) {
    while (qi < n_) {
      int j = qj;
      while (j < m_) {
        data_[qi][j] += qv;
        j = (j | (j + 1));
      }
      qi = (qi | (qi + 1));
    }
  }
  ll reduce(int qi, int qj) {
    ll res = 0;
    while (qi >= 0) {
      int j = qj;
      while (j >= 0) {
        res += data_[qi][j];
        j = (j & (j + 1)) - 1;
      }
      qi = (qi & (qi + 1)) - 1;
    }
    return res;
  }
};

// Main
void mainCase() {
  int n, nq; // n <= 10^3, nq <= 10^6
  cin >> n >> nq;
  vector<vector<char>> board(n, vector<char>(n, '?'));
  cin >> board;
  vector<array<int, 5>> qs(nq, {0});
  FOR(i, 0, nq) {
    int t, a, b, c, d; a = b = c = d = -1;
    cin >> t;
    if (t == 1) { cin >> a >> b; }
    if (t == 2) { cin >> a >> b >> c >> d; }
    qs[i] = {t, a, b, c, d};
  }
  // DD(qs);

  FenwickTree tree(n, n);
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      if (board[i][j] == '*') {
        tree.incr(i, j, 1);
      }
    }
  }
  // DD2(board);
  // DD2(tree.data_);

  for (auto [t, a, b, c, d] : qs) {
    a--; b--; c--; d--;
    if (t == 1) {
      board[a][b] = board[a][b] == '*' ? '.' : '*';
      tree.incr(a, b, board[a][b] == '*' ? 1 : -1);
    }
    if (t == 2) {
      ll x = tree.reduce(c, d);
      ll y = tree.reduce(a - 1, d);
      ll z = tree.reduce(c, b - 1);
      ll w = tree.reduce(a - 1, b - 1);
      ll res = x - y - z + w;
      cout << res << endl;
    }
  }
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
python misc/run.py cses/range_queries/task1739/main.cpp --check

%%%% begin
4 3
.*..
*.**
**..
****
2 2 2 3 4
1 3 3
2 2 2 3 4
%%%%
3
4
%%%% end
*/
