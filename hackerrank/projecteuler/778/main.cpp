// WA

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

// High dimentional vector
template<class T>
T NdVector(T value) { return value; }

template<class ...Ts>
decltype(auto) NdVector(size_t n, Ts ...rest) {
  auto inner = NdVector(rest...);
  return vector<decltype(inner)>(n, inner);
}

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

constexpr ll modulo = 1e9 + 9;
using mint = ModInt<modulo>;

// integer power
ll ipow(ll base, ll exp) {
  ll x = base;
  ll y = 1;
  while (exp > 0) {
    if (exp & 1) {
      y *= x;
    }
    x *= base;
    exp >>= 1;
  }
  return y;
}

// Main
void mainCase() {
  ll r, m; // [0, 10^6]
  cin >> r >> m;

  // For simplicity, deal with [0, m) range
  m++;

  // Digit length
  int n = to_string(m).size();

  // Digit statistics for each position of the numbers [0, m)
  //   stats(k, d)
  vector<array<ll, 10>> stats(n);
  for (int k = 0; k < n; k++) {
    ll ten_k = ipow(10, k);
    ll ten_k_one = ipow(10, k + 1);
    ll bonus0 = (m / ten_k_one) * ten_k;
    ll bonus1 = ten_k;
    ll bonus2 = m % ten_k;
    int d_lim = (m % ten_k_one) / ten_k;
    for (int d = 0; d < 10; d++) {
      stats[k][d] += bonus0;
      if (d < d_lim) {
        stats[k][d] += bonus1;
      }
      if (d == d_lim) {
        stats[k][d] += bonus2;
      }
    }
  }

  // Digit statistics for each position of freshman's product
  //   res_stats(k, r, d) = #{ ... }
  auto res_stats = NdVector(n, r + 1, array<mint, 10>({}));

  for (int k = 0; k < n; k++) {
    auto& dp = res_stats[k];

    for (int d = 0; d < 10; d++) {
      dp[1][d] = stats[k][d];
    }

    for (int i = 1; i < r; i++) {
      for (int d1 = 0; d1 < 10; d1++) {
        for (int d2 = 0; d2 < 10; d2++) {
            dp[i + 1][(d1 * d2) % 10] += dp[1][d1] * dp[i][d2];
        }
      }
    }
  }

  // Take sum from each position
  mint res = 0;
  for (int k = 0; k < n; k++) {
    for (int d = 0; d < 10; d++) {
      res += res_stats[k][r][d] * d * ipow(10, k);
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py hackerrank/projecteuler/778/main.cpp

%%%% begin
2 7
%%%%
204
%%%% end

%%%% begin
23 76
%%%%
5870548
%%%% end

%%%% begin
234567 765432
%%%%
2906171
%%%% end
*/
