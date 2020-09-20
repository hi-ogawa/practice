// AC

// NOTE: similar to https://atcoder.jp/contests/abc171/tasks/abc171_f

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

template<ll M>
struct ModInt {
  using mint = ModInt;
  static constexpr ll modulo = M;
  ll v;
  ModInt() : v{0} {}
  template<typename T> ModInt(T y) : v{static_cast<ll>(y)} {}
  template<typename T> operator T() { return static_cast<T>(v); }
  friend istream& operator>>(istream& i, mint& self) { return i >> self.v; }
  friend ostream& operator<<(ostream& o, const mint& self) { return o << self.v; }

  mint& operator+=(const mint& o) { v += o.v; while (v >= M) { v -= M; }; return *this; }
  mint& operator-=(const mint& o) { return *this += mint(M - o.v); }
  mint& operator*=(const mint& o) { v = (v * o.v) % M; return *this; }
  mint& operator/=(const mint& o) { return *this *= o.inv(); }
  friend mint operator+(const mint& x, const mint& y) { return mint(x) += y; }
  friend mint operator-(const mint& x, const mint& y) { return mint(x) -= y; }
  friend mint operator*(const mint& x, const mint& y) { return mint(x) *= y; }
  friend mint operator/(const mint& x, const mint& y) { return mint(x) /= y; }

  mint inv() const { return pow(M - 2); } // assume M is prime
  mint pow(ll e) const {
    mint x = *this;
    mint res = 1;
    while (e > 0) {
      if (e & 1) { res *= x; }
      e >>= 1; x *= x;
    }
    return res;
  }

  static inline vector<mint> facts, inv_facts;
  static void makeFactorials(int n) {
    if (!facts.empty()) { return; }
    facts.resize(n + 1);
    inv_facts.resize(n + 1);
    facts[0] = inv_facts[0] = 1;
    for (int k = 1; k <= n; k++) {
      facts[k] = facts[k - 1] * mint(k);
      inv_facts[k] = inv_facts[k - 1] / mint(k);
    }
  }
  static mint fact(int n) { return facts[n]; }
  static mint invFact(int n) { return inv_facts[n]; }
  static mint binom(int n, int k) { return fact(n) * invFact(n - k) * invFact(k); }

  static inline vector<mint> invs;
  static void makeInverses(int n) {
    if (!invs.empty()) { return; }
    invs.resize(n + 1);
    for (int k = 1; k <= n; k++) {
      invs[k] = mint(k).inv();
    }
  }
};

using mint = ModInt<(ll)1e9 + 7>;

// Main
void mainCase() {
  int m, n;
  cin >> m >> n;

  int m_lim = 1e6;

  mint res = 0;
  int algo = 2;

  if (algo == 0) {
    mint::makeFactorials(m_lim);

    FOR(k, n, m + 1) {
      res +=
        mint::binom(k - 1, n - 1) *
        mint(n - 1).pow(k - n) *
        mint(n).pow(m - k);
    }
  }

  if (algo == 1) {
    // Incrementally update each term of 1st algorithm
    // Also, use precomputed inverses for known ranges.
    mint::makeInverses(m_lim);

    mint t = mint(n).pow(m - n);
    res += t;
    FOR(k, n, m) {
      t *= mint(k) * mint::invs[k - n + 1] * mint(n - 1) * mint::invs[n];
      res += t;
    }
  }

  if (algo == 2) {
    // Only "Pow factor" incrementally
    mint::makeFactorials(m_lim);

    mint t = mint(n).pow(m - n);
    mint inv_n = mint(n).inv();
    FOR(k, n, m + 1) {
      res += mint::binom(k - 1, n - 1) * t;
      t *= mint(n - 1) * inv_n;
    }
  }

  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py hackerrank/challenges/longest-increasing-subsequence-arrays/main.cpp --check

%%%% begin
1
500000 100000
%%%%
771987018
%%%% end

%%%% begin
2
4 2
4 3
%%%%
11
9
%%%% end
*/
