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

  static inline vector<mint> fact;
  static void makeFactorials(int n) {
    fact.assign(n + 1, 1);
    for (int i = 2; i <= n; i++) {
      fact[i] = fact[i - 1] * i;
    }
  }
};

const ll modulo = 998244353;
using mint = ModInt<modulo>;

// Main
void mainCase() {
  int n; // [1, 3 x 10^5]
  cin >> n;
  vector<array<int, 2>> ls(n);
  cin >> ls;

  map<array<int, 2>, int> cnts;
  map<int, int> cnts1, cnts2;
  FOR(i, 0, n) {
    cnts[ls[i]]++;
    cnts1[ls[i][0]]++;
    cnts2[ls[i][1]]++;
  }
  dbg(cnts, cnts1, cnts2);

  //
  // PROP.
  //   By inclusion-exclusion principle
  //     Answer = #{any} - #{1st incr} - #{2nd incr} + #{both incr}
  //

  mint::makeFactorials(n);

  auto countIncr = [&](auto& cnts) -> mint {
    mint res = 1;
    for (auto [k, v] : cnts) { res *= mint::fact[v]; }
    return res;
  };

  bool ok12 = 1;
  sort(ALL(ls));
  FOR(i, 0, n - 1) {
    if (ls[i][1] > ls[i + 1][1]) {
      ok12 = 0;
      break;
    }
  }

  mint c = mint::fact[n];
  mint c1 = countIncr(cnts1);
  mint c2 = countIncr(cnts2);
  mint c12 = ok12 ? countIncr(cnts) : 0;

  dbg(c, c1, c2, c12);
  mint res = c - c1 - c2 + c12;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1207D/main.cpp

%%%% begin
3
1 1
2 2
3 1
%%%%
3
%%%% end

%%%% begin
4
2 3
2 2
2 1
2 4
%%%%
0
%%%% end

%%%% begin
3
1 1
1 1
2 3
%%%%
4
%%%% end
*/
