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
  vector<array<int, 4>> qs(nq, {0});
  cin >> qs;

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

  for (auto [i1, j1, i2, j2] : qs) {
    i1--; j1--; i2--; j2--;
    ll x = tree.reduce(i2, j2);
    ll y = tree.reduce(i1 - 1, j2);
    ll z = tree.reduce(i2, j1 - 1);
    ll w = tree.reduce(i1 - 1, j1 - 1);
    // DD(tie(i1, j1, i2, j2));
    // DD(tie(x, y, z, w));
    ll res = x - y - z + w;
    cout << res << endl;
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
python misc/run.py cses/range_queries/task1652/main.cpp --check

%%%% begin
4 3
.*..
*.**
**..
****
2 2 3 4
3 1 3 1
1 1 2 2
%%%%
3
1
2
%%%% end
*/
