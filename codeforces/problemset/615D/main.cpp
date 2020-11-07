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

const ll modulo = 1e9 + 7;
using mint = ModInt<modulo>;

// Main
void mainCase() {
  int m; // [1, 2 x 10^5]
  cin >> m;
  vector<int> ls(m); // [2, 2 x 10^5], prime
  cin >> ls;

  map<int, ll> _cnts;
  for (auto p : ls) { _cnts[p]++; }
  vector<pair<int, ll>> cnts(ALL(_cnts));
  int k = cnts.size();

  //
  // PROP.
  //   For n = ∏ p_i^e_i,
  //     f(n) = ∏_{d | n} d
  //          = ∏_{(f_i) ≤ (e_i)} p_i^f_i
  //          = (p1 x p1^2 x ... x p1^e1) . ∏_{d | (n / p1^e1)} d .
  //            ....
  //   Thus,
  //     ν(f(n), p1) = (1 + 2 + ... + e1) x #{divisors of n / p1^e1}
  //                 = (e1 (e1 + 1) / 2) x (∏_i (e_i + 1)) / (e1 + 1)
  //

  // Compute power of each factor
  vector<ll> divs_l(k), divs_r(k);
  vector<ll> pows(k);

  divs_l[0] = cnts[0].second + 1;
  FOR(i, 1, k) {
    auto [_p, e] = cnts[i];
    divs_l[i] = divs_l[i - 1] * (e + 1);
    divs_l[i] %= modulo - 1; // Fermat's little theorem
  }

  divs_r[k - 1] = cnts[k - 1].second + 1;
  for (int i = k - 2; i >= 0; i--) {
    auto [_p, e] = cnts[i];
    divs_r[i] = divs_r[i + 1] * (e + 1);
    divs_r[i] %= modulo - 1;
  }

  FOR(i, 0, k) {
    auto [_p, e] = cnts[i];
    ll x = ((e * (e + 1)) / 2);
    x %= modulo - 1;
    if (i > 0) {
      x *= divs_l[i - 1];
      x %= modulo - 1;
    }
    if (i < k - 1) {
      x *= divs_r[i + 1];
      x %= modulo - 1;
    }
    pows[i] = x;
  }
  dbg(cnts);
  dbg(pows);

  mint res = 1;
  FOR(i, 0, k) {
    auto [p, _e] = cnts[i];
    res *= mint(p).pow(pows[i]);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/615D/main.cpp

%%%% begin
2
2 3
%%%%
36
%%%% end

%%%% begin
3
2 3 2
%%%%
1728
%%%% end
*/
