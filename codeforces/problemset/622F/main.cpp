// AFTER EDITORIAL, AC

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
  template<class T> ModInt(T x) { ll y = (ll)x % modulo; if (y < 0) { y += modulo; } v = y; }
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

  static inline array<vector<mint>, 2> facts; // facts[inv][n]
  static void makeFactorials(int n) {
    facts[0].resize(n + 1, 1);
    facts[1].resize(n + 1, 1);
    for (int i = 2; i <= n; i++) {
      facts[0][i] = facts[0][i - 1] * i;
    }
    facts[1][n] = facts[0][n].inv();
    for (int i = n - 1; i >= 2; i--) {
      facts[1][i] = facts[1][i + 1] * (i + 1);
    }
  }
};

constexpr ll modulo = 1e9 + 7;
using mint = ModInt<modulo>;

mint solve(const vector<mint>& ys, int x) {
  int n = ys.size() - 1;

  // xs1[i] = x(x-1)(x-2)...(x-(i-1))
  // xs2[i] = (x-n)(x-(n-1))...(x-(i+1))
  vector<mint> xs1(n + 1), xs2(n + 1);
  xs1[0] = xs2[n] = mint(1);
  FOR(i, 1, n + 1) {
    xs1[i] = xs1[i - 1] * (x - (i - 1));
  }
  for (int i = n - 1; i >= 0; i--) {
    xs2[i] = xs2[i + 1] * (x - (i + 1));
  }

  // Precompute factorial inverses
  mint::makeFactorials(n);

  mint res = 0;
  FOR(i, 0, n + 1) {
    mint t = ys[i] * xs1[i] * xs2[i] * mint::facts[1][i] * mint::facts[1][n - i];
    if ((n - i) % 2) { t *= -1; }
    res += t;
  }
  return res;
}

// Main
void mainCase() {
  int n, k; // n \in [1, 10^9], k \in [0, 10^6]
  cin >> n >> k;

  // f(x) = 1^k + 2^k + ... + x^k : (k + 1)-deg polynomial (cf. Euler-Maclaurin formula)

  // Interpolation points f(0), f(1), .., f(k), f(k+1)
  vector<mint> fs(k + 2);
  FOR(x, 1, k + 2) {
    fs[x] = fs[x - 1] + mint(x).pow(k);
  }
  dbg(fs);

  // Evaluate f(n) = f(0)L0(n) + f(1)L1(n) + ... f(k+1)Lk+1(n)
  //   where L0(x), L1(x), : Lagrange poly basis for points (0, 1, .., k, k+1)
  mint res = solve(fs, n);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/622F/main.cpp

%%%% begin
4 1
%%%%
10
%%%% end

%%%% begin
4 2
%%%%
30
%%%% end

%%%% begin
4 3
%%%%
100
%%%% end

%%%% begin
4 0
%%%%
4
%%%% end
*/
