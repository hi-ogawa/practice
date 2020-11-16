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

// Modulo integer
template<ll Modulo>
struct ModInt {
  using mint = ModInt;
  static constexpr ll modulo = Modulo;
  uint32_t v;
  ModInt() : v{0} {}
  template<class T, class = enable_if_t<is_integral_v<T>>>
  ModInt(T x) { ll y = (ll)x % modulo; if (y < 0) { y += modulo; } v = y; }
  friend istream& operator>>(istream& istr,       mint& self) { return istr >> self.v; }
  friend ostream& operator<<(ostream& ostr, const mint& self) { return ostr << self.v; }
  mint& operator+=(const mint& y) { v += y.v; while (v >= modulo) { v -= modulo; }; return *this; }
  mint& operator-=(const mint& y) { return *this += (modulo - y.v); }
  mint& operator*=(const mint& y) { v = (ll)v * y.v % modulo; return *this; }
  mint& operator/=(const mint& y) { return *this *= y.inv(); }
  friend mint operator+(const mint& x, const mint& y) { return mint(x) += y; }
  friend mint operator-(const mint& x, const mint& y) { return mint(x) -= y; }
  friend mint operator*(const mint& x, const mint& y) { return mint(x) *= y; }
  friend mint operator/(const mint& x, const mint& y) { return mint(x) /= y; }
  friend bool operator==(const mint& x, const mint& y) { return x.v == y.v; }
  friend bool operator!=(const mint& x, const mint& y) { return x.v != y.v; }
  mint operator-() const { return mint() - *this; }
  mint inv() const { return pow(modulo - 2); }
  mint pow(ll e) const {
    mint x = *this, res = 1;
    while (e > 0) {
      if (e & 1) { res *= x; }
      e >>= 1; x *= x;
    }
    return res;
  }
};

const ll modulo = 1e9 + 7;
using mint = ModInt<modulo>;

// Fenwick tree for sum
struct FenwickTree {
  int n_;
  vector<mint> data_;
  FenwickTree(int n) { n_ = n; data_.resize(n); }
  void incr(int i, mint v) {
    while (i < n_) {
      data_[i] += v;
      i = (i | (i + 1));
    }
  }
  mint reduce(int r) { // [0, r)
    int i = r - 1;
    mint res = 0;
    while (i >= 0) {
      res += data_[i];
      i = (i & (i + 1)) - 1;
    }
    return res;
  }
  mint reduce(int l, int r) { // [l, r)
    return reduce(r) - reduce(l);
  }
};

// Main
void mainCase() {
  int n, m; // [2, 2000]
  cin >> n >> m;
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;

  // Block per row/col/diagonal
  vector<vector<int>> rows(n), cols(m), diags(n + m - 1);
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == '#') {
        rows[i].push_back(j);
        cols[j].push_back(i);
        diags[i - j + m - 1].push_back(i);
      }
    }
  }

  // A bunch of range sums
  vector<FenwickTree> dp_rows(n, FenwickTree(m));
  vector<FenwickTree> dp_cols(m, FenwickTree(n));
  vector<FenwickTree> dp_diags(n + m - 1, FenwickTree(n));

  dp_rows[0].incr(0, 1);
  dp_cols[0].incr(0, 1);
  dp_diags[0 + 0 + m - 1].incr(0, 1);

  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == '#') { continue; }
      mint t = 0;

      // Collect from closest blocks
      {
        int j0 = 0;
        auto it = upper_bound(ALL(rows[i]), j);
        if (it != rows[i].begin()) {
          j0 = *prev(it) + 1;
        }
        t += dp_rows[i].reduce(j0, j);
      }
      {
        int i0 = 0;
        auto it = upper_bound(ALL(cols[j]), i);
        if (it != cols[j].begin()) {
          i0 = *prev(it) + 1;
        }
        t += dp_cols[j].reduce(i0, i);
      }
      {
        int i0 = 0;
        auto it = upper_bound(ALL(diags[i - j + m - 1]), i);
        if (it != diags[i - j + m - 1].begin()) {
          i0 = *prev(it) + 1;
        }
        t += dp_diags[i - j + m - 1].reduce(i0, i);
      }

      // Update
      dp_rows[i].incr(j, t);
      dp_cols[j].incr(i, t);
      dp_diags[i - j + m - 1].incr(i, t);
    }
  }

  auto res = dp_rows[n - 1].reduce(m - 1, m);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc183/e/main.cpp

%%%% begin
3 3
...
.#.
...
%%%%
10
%%%% end

%%%% begin
4 4
...#
....
..#.
....
%%%%
84
%%%% end

%%%% begin
8 10
..........
..........
..........
..........
..........
..........
..........
..........
%%%%
13701937
%%%% end
*/
