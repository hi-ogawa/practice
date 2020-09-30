// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; bool b = 0; apply([&](auto&&... y){ ((o << (b ? ", " : "") << y, b = 1), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; bool b = 0; for (auto& y : x) { o << (b ? ", " : "") << y; b = 1; } return o << "}"; }
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
  template<class T> ModInt(T x) {
    ll y = (ll)x % modulo;
    if (y < 0) { y += modulo; }
    v = y;
  }
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
};

// Mobius function
vector<int> makeMobius(int n) {
  vector<int> mu(n + 1, 1);
  vector<bool> sieve(n + 1, 1);
  for (int p = 2; p <= n; p++) {
    if (!sieve[p]) { continue; }
    for (int x = p; x <= n; x += p) {
      sieve[x] = 0;
      mu[x] *= -1;
      if (x % (p * p) == 0) { mu[x] = 0; }
    }
  }
  return mu;
}

// Main
void mainCase() {
  int n, k;
  cin >> n >> k;

  //
  // PROP.
  //   Define
  //     f(x) = #{ (ai)_i s.t. ∀i. x | ai }
  //     h(x) = #{ (ai)_i s.t. x = gcd((ai)_i) }
  //   then, by inclusion-exclusion princile,
  //     h(x) = ∑_{x | y} μ(y/x) f(y)
  //          = ∑_z μ(z) f(xz)
  //
  // PROP.
  //     Answer = ∑_{x} x h(x)
  //            = ∑_{x,y} x μ(y) f(xy)
  //            = ∑_{y} μ(y) ∑_{x} x f(xy)
  //

  using mint = ModInt<(ll)1e9 + 7>;

  // Compute f(x)
  vector<mint> fs(k + 1);
  FOR(x, 1, k + 1) {
    fs[x] = mint(k / x).pow(n);
  }

  // Compute μ(x)
  auto mu = makeMobius(k);
  dbg(mu);

  // Compute answer
  mint res = 0;
  FOR(y, 1, k + 1) {
    FOR(x, 1, k + 1) {
      if (x * y > k) { break; }
      res += mu[y] * x * fs[x * y];
    }
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc162/e/main.cpp --check


%%%% begin
3 2
%%%%
9
%%%% end

%%%% begin
3 200
%%%%
10813692
%%%% end

%%%% begin
100000 100000
%%%%
742202979
%%%% end
*/
