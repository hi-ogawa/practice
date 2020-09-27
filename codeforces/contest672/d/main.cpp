// AFTER EDITORIAL, AC

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

template<ll Modulo>
struct ModInt {
  using mint = ModInt;
  static constexpr ll modulo = Modulo;
  ll v;
  ModInt() : v{0} {}
  template<class T> ModInt(T x) : v{static_cast<ll>(x)} {}
  template<class T> operator T() { return static_cast<T>(v); }
  friend ostream& operator<<(ostream& ostr, const mint& self) { return ostr << self.v; }

  mint& operator+=(const mint& y) { v += y.v; while (v >= modulo) { v -= modulo; }; return *this; }
  mint& operator-=(const mint& y) { return *this += (modulo - y.v); }
  mint& operator*=(const mint& y) { v = ((v * y.v) % modulo); return *this; }
  mint& operator/=(const mint& y) { return *this *= y.inv(); }
  friend mint operator+(const mint& x, const mint& y) { return mint(x) += y; }
  friend mint operator-(const mint& x, const mint& y) { return mint(x) -= y; }
  friend mint operator*(const mint& x, const mint& y) { return mint(x) *= y; }
  friend mint operator/(const mint& x, const mint& y) { return mint(x) /= y; }
  mint inv() const { return pow(modulo - 2); }
  mint pow(ll e) const {
    mint x = *this, res = 1;
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
    FOR(i, 1, n + 1) {
      facts[i] = facts[i - 1] * mint(i);
      inv_facts[i] = inv_facts[i - 1] / mint(i);
    }
  }
  static mint binom(int n, int k) {
    return facts[n] * inv_facts[n - k] * inv_facts[k];
  }
};

using mint = ModInt<998244353>;

// Main
void mainCase() {
  int n, k; // [1, 3 x 10^5]
  cin >> n >> k;
  vector<array<int, 2>> ls(n); // [1, 10^9]
  cin >> ls;

  vector<array<int, 2>> events; // (x, in/out)
  FOR(i, 0, n) {
    auto [l, r] = ls[i];
    events.push_back({l, 0});
    events.push_back({r, 1});
  }
  sort(ALL(events));

  // Precompute factorial/binom
  mint::makeFactorials(n);

  mint res = 0;
  int cnt = 0;
  for (auto [x, t] : events) {
    if (t == 0) {
      cnt++;
      if (cnt >= k) {
        res += mint::binom(cnt - 1, k - 1);
      }
    }
    if (t == 1) {
      cnt--;
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
python misc/run.py codeforces/contest672/d/main.cpp --check

%%%% begin
7 3
1 7
3 8
4 5
6 7
1 3
5 10
8 9
%%%%
9
%%%% end

%%%% begin
3 1
1 1
2 2
3 3
%%%%
3
%%%% end

%%%% begin
3 2
1 1
2 2
3 3
%%%%
0
%%%% end

%%%% begin
3 3
1 3
2 3
3 3
%%%%
1
%%%% end

%%%% begin
5 2
1 3
2 4
3 5
4 6
5 7
%%%%
7
%%%% end
*/
