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
};

const ll modulo = 1e9 + 7;
using mint = ModInt<modulo>;

// Z function
vector<int> makeZ(const string& s) {
  int n = s.size();
  vector<int> z(n);
  int l = 1, r = 1; // [l, r)
  FOR(i, 1, n) {
    if (i < r) { z[i] = min(z[i - l], r - i); }
    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) { z[i]++; }
    if (i + z[i] > r) { l = i; r = i + z[i]; }
  }
  return z;
}

// Main
void mainCase() {
  int n; // [1, 1000]
  cin >> n;
  string s; // uppercase
  cin >> s;
  int m = s.size(); // [1, 100]

  const mint k = 26; // A..Z

  //
  // DEF. (counting first occurence of prefix)
  //   g(0) = 1
  //   g(i) = k^i - ∑_{j < i and match(i - j)} g(j) k^(i - j - m)
  //

  // Check if s[d:] = s[:-d]
  auto z = makeZ(s);
  auto match = [&](int d) -> bool {
    if (d == 0 || d >= m) { return 1; }
    return z[d] == m - d;
  };
  dbg(z);

  vector<mint> g(n + 1);
  g[0] = 1;
  FOR(i, 1, n + 1) {
    g[i] = k.pow(i);
    FOR(j, 0, i) {
      int d = i - j;
      if (match(d)) {
        g[i] -= g[j] * k.pow(max(0, d - m));
      }
    }
  }
  dbg(g);

  mint res = 0;
  FOR(i, 0, n - m + 1) {
    auto t = g[i] * k.pow(n - m - i);
    dbg(i, t);
    res += t;
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/string_algorithms/task1112/main.cpp

%%%% begin
6
ABCDB
%%%%
52
%%%% end
*/
