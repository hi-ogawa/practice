// CONTEST, AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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

const ll modulo = 998244353;
using mint = ModInt<modulo>;

// Main
void mainCase() {
  int n; // [2, 2 x 10^5]
  cin >> n;
  int k; // [1, 300]
  cin >> k;
  vector<mint> ls(n); // [1, 10^8]
  cin >> ls;

  int k2 = 2 * k;
  vector<vector<mint>> pows(k2 + 1, vector<mint>(n));
  pows[1] = ls;
  FOR(e, 2, k2 + 1) {
    FOR(i, 0, n) {
      pows[e][i] = pows[e - 1][i] * ls[i];
    }
  }

  vector<mint> sum_pows(k2 + 1);
  sum_pows[0] = n;
  FOR(e, 1, k2 + 1) {
    mint t = 0;
    FOR(i, 0, n) { t += pows[e][i]; }
    sum_pows[e] = t;
  }
  dbg(sum_pows);

  //
  // mul_sums(e1, e2) = ∑_{i ≠ j} ai^e1 aj^e2
  //
  // NOTE:
  // (∑ ai^e1) (∑ ai^e2) =
  //    (∑ ai^{e1 + e2})
  //    + 2 (∑_{i ≠ j} ai^e1 aj^e2)
  //

  vector<vector<mint>> mul_sums(k + 1, vector<mint>(k + 1));
  FOR(e1, 0, k + 1) {
    FOR(e2, 0, k + 1) {
      mint t = (sum_pows[e1] * sum_pows[e2] - sum_pows[e1 + e2]) / 2;
      mul_sums[e1][e2] = mul_sums[e2][e1] = t;
    }
  }
  dbg2(mul_sums);

  // ∑_{i ≠ j} (ai + aj)^x
  // = ∑_{i ≠ j} ∑_{e} binom(x, e) ai^e aj^{x - e}
  // = ∑_{e1 + e2 = e} binom(x, e1)
  //     ∑_{i ≠ j} ai^e1 aj^e2

  mint::makeFactorials(k);

  vector<mint> res(k + 1);
  FOR(x, 1, k + 1) {
    mint t = 0;
    FOR(e1, 0, x + 1) {
      int e2 = x - e1;
      t += mint::binom(x, e1) * mul_sums[e1][e2];
    }
    res[x] = t;
  }

  FOR(i, 1, k + 1) {
    cout << res[i] << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/arc106/d/main.cpp

%%%% begin
3 3
1 2 3
%%%%
12
50
216
%%%% end
*/
