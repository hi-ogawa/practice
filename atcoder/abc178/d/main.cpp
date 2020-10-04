// TLE

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

// Modulo
template<ll Modulo>
struct ModInt {
  using mint = ModInt;
  static constexpr ll modulo = Modulo;
  uint32_t v;
  ModInt() : v{0} {}
  template<class T> ModInt(T x) {
    ll y = (ll)x % modulo;
    if (y < 0) { y += modulo; }
    v = y;
  }
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
  mint inv() const { return pow(modulo - 2); }
  mint pow(ll e) const {
    mint x = *this, res = 1;
    while (e > 0) {
      if (e & 1) { res *= x; }
      e >>= 1; x *= x;
    }
    return res;
  }


  static inline array<vector<mint>, 2> facts;
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
  };
  static mint binom(int n, int k) {
    return facts[0][n] * facts[1][n - k] * facts[1][k];
  }
};

using mint = ModInt<(ll)1e9 + 7>;

// Main
void mainCase() {
  int s; // [1, 2000]
  cin >> s;

  mint::makeFactorials(s + 1);

  // dp(c, s) = #{ ways to make "sum = s" with "count = c" }
  vector<map<int, mint>> dp(s + 1);
  dp[0][0] = 1;
  auto dp_prev = dp;
  FOR(x, 3, s + 1) {
    FOR(j, 0, s - x + 1) {
      FOR(m, 1, (s - j) / x + 1) {
        for (auto [c, d] : dp_prev[j]) {
          dp[j + m * x][m + c] += mint::binom(m + c, m) * d;
        }
      }
    }
    dp_prev = dp;
  }
  dbg(dp[s]);

  mint res = 0;
  for (auto [c, d] : dp[s]) {
    res += d;
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc178/d/main.cpp --check

%%%% begin
7
%%%%
3
%%%% end

%%%% begin
2
%%%%
0
%%%% end

%%%% begin
1729
%%%%
294867501
%%%% end
*/
