// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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

  // Factorial, binomial
  static inline vector<mint> facts[2];
  static void makeFactorials(int n) {
    facts[0].assign(n + 1, 1);
    facts[1].assign(n + 1, 1);
    for (int i = 2; i <= n; i++) {
      facts[0][i] = facts[0][i - 1] * i;
    }
    facts[1][n] = facts[0][n].inv();
    for (int i = n - 1; i >= 2; i--) {
      facts[1][i] = facts[1][i + 1] * (i + 1);
    }
  }
  static mint binom(int n, int k) {
    if (n < k) { return 0; }
    return facts[0][n] * facts[1][n - k] * facts[1][k];
  }
};

const ll modulo = 998244353; // = 1 + 2^23 x 7 x 17
using mint = ModInt<modulo>;

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  string xs; // {'0', '1'}
  cin >> xs;
  dbg(xs);

  // Operations
  //  ...011...  <=>  ...110...

  // Normal form after pushing all "11" to the left
  //  1....10...010....010....010....0

  // The special case below is simply is comb(k + m, k)
  //   1......10.....0
  //   <- 2k -><- m ->

  // And the similar argument applies to the general case,
  // considering each block of 1...1 separately.

  // Count '0'
  int cnt0 = count(ALL(xs), '0');

  // Count '1' separately for each block
  vector<int> cnts1;
  FOR(i, 0, n) {
    if (xs[i] == '0') { continue; }
    if (i == 0 || xs[i - 1] == '0') {
      cnts1.push_back(0);
    }
    cnts1.back()++;
  }

  dbg(cnt0, cnts1);

  int m = cnt0;
  int k = 0;
  for (auto cnt: cnts1) {
    // Effectively "free-moving" parts are an half of all
    k += cnt / 2;
  }
  dbg(k, m);
  mint::makeFactorials(k + m);
  cout << mint::binom(k + m, m) << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 10^3]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1546/d/main.cpp

%%%% begin
6
4
0110
6
011011
5
01010
20
10001111110110111000
20
00110110100110111101
20
11101111011000100010
%%%%
3
6
1
1287
1287
715
%%%% end
*/
