// AC

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

const ll modulo = 998244353;
using mint = ModInt<modulo>;

// Main
void mainCase() {
  ll n, m, l, r; // [1, 10^9]
  cin >> n >> m >> l >> r;

  ll N = n * m;

  // #{evens}, #{odds} within [l, r]
  mint e = (r + 2) / 2 - (l + 1) / 2;
  mint o = (r + 1) / 2 - l / 2;

  //
  // PROP.
  //   When N : even
  //     (a_ij)_ij is valid \iff ∑ aij : even
  //
  //   When N : odd,
  //     (a_ij)_ij is always valid.
  //
  //   PROOF
  //     1. WLOG, by using 2nd operations, the differences of "a_ij" are at most 1.
  //     2. We can push such differences wherever we want. e.g.
  //           11...1100...00
  //           11.1100.....00
  //           ...
  //     3. In order to cancel out all of "1"s,
  //        if N : even, then clearly it's neccesarily/sufficient for such #{"1"s} to be even.
  //        if N : odd, then
  //          if #{"1"s} : even, then we can make all "0" as whe N : even.
  //          if #{"1"s} : odd, then #{"0"s} : even, thus we can make all "1" by even number of changes.
  //
  // PROP.
  //   If N : even
  //     Answer
  //       = ∑_{x: even} binom(N, x) . #{ways to choose "x" odds} . #{ways to choose "N - x" evens}
  //       = ∑_{x: even} binom(N, x) o^(x) e^(N - x)
  //       = ((e + o)^N + (e - o)^N) / 2
  //
  //   If N : odd
  //     Answer
  //       = ∑_{x} binom(N, x) o^(x) e^(N - x)
  //       = (e + o)^N
  //
  //

  dbg(N, e, o);
  mint res;
  if (N % 2) {
    res = (e + o).pow(N);
  } else {
    res = ((e + o).pow(N) + (e - o).pow(N)) / 2;
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1332E/main.cpp

%%%% begin
2 2 1 1
%%%%
1
%%%% end

%%%% begin
1 2 1 2
%%%%
2
%%%% end
*/
