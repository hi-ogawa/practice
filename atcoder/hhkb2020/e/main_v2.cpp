// AC

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

// Main
void mainCase() {
  int n, m; // [1, 2000]
  cin >> n >> m;
  vector<vector<char>> board(n, vector<char>(m));
  cin >> board;

  // Count influencing lamps
  vector<vector<int>> ls(n, vector<int>(m, 0));
  int cnt = 0;

  // Count tidy
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == '.') {
        cnt++;
        ls[i][j] = 1;
      }
    }
  }

  // Horizontal neighbor
  FOR(i, 0, n) {
    vector<array<int, 2>> segs;
    FOR(j, 0, m) {
      if (segs.empty() || board[i][j] != board[i][j - 1]) {
        segs.push_back({j, -1});
      }
      segs.back()[1] = j + 1;
    }
    for (auto [j0, j1] : segs) {
      if (board[i][j0] == '.') {
        FOR(jj, j0, j1) {
          ls[i][jj] += j1 - j0 - 1;
        }
      }
    }
  }

  // Vertical neighbor
  FOR(j, 0, m) {
    vector<array<int, 2>> segs;
    FOR(i, 0, n) {
      if (segs.empty() || board[i][j] != board[i - 1][j]) {
        segs.push_back({i, -1});
      }
      segs.back()[1] = i + 1;
    }
    for (auto [i0, i1] : segs) {
      if (board[i0][j] == '.') {
        FOR(ii, i0, i1) {
          ls[ii][j] += i1 - i0 - 1;
        }
      }
    }
  }
  dbg2(ls);

  // Distribution of tidy wrt influencing lamp count
  int k_lim = n + m;
  vector<int> cnts(k_lim); // distribution wrt
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (board[i][j] == '.') {
        assert(ls[i][j] < k_lim);
        cnts[ls[i][j]]++;
      }
    }
  }
  dbg(cnt, cnts);

  mint res = 0;
  FOR(k, 1, k_lim) {
    // 2^cnt (2^k - 1) / 2^k
    res += mint(2).pow(cnt - k) * (mint(2).pow(k) - 1) * cnts[k];
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/hhkb2020/e/main_v2.cpp

%%%% begin
3 3
...
...
...
%%%%
4464
%%%% end

%%%% begin
1 5
..#..
%%%%
48
%%%% end

%%%% begin
2 3
..#
#..
%%%%
52
%%%% end
*/
