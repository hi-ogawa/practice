// AFTER EDITORIAL, AC

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
};

const ll modulo = 1e9 + 7;
using mint = ModInt<modulo>;

// Main
void mainCase() {
  int d, n; // [0, 2000]
  cin >> d >> n;
  vector<int> ls(n); // [1, 2000]
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  // WLOG, vertices are ordered by ls[i] <= ls[]
  vector<int> order(n), inv_order(n);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return ls[x] < ls[y]; });
  FOR(i, 0, n) { inv_order[order[i]] = i; }
  sort(ALL(ls));

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    x = inv_order[x];
    y = inv_order[y];
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // Count good component ⊆ {i, i + 1, .., n}
  auto solve = [&](int i) -> mint {
    vector<mint> dp(n);
    function<void(int, int)> dfs = [&](int v, int vp) {
      dp[v] = 1;
      for (auto u : adj[v]) {
        if (u == vp) { continue; }
        if (u < i) { continue; }             // Only {i, i + 1, .., n}
        if (ls[u] > ls[i] + d) { continue; } // Only [ls[i], ls[i] + d]
        dfs(u, v);
        dp[v] *= (dp[u] + 1);
      }
    };
    dfs(i, -1);
    return dp[i];
  };

  mint res = 0;
  FOR(i, 0, n) { res += solve(i); }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/486D/main.cpp

%%%% begin
1 4
2 1 3 2
1 2
1 3
3 4
%%%%
8
%%%% end

%%%% begin
0 3
1 2 3
1 2
2 3
%%%%
3
%%%% end

%%%% begin
4 8
7 8 7 5 4 6 4 10
1 6
1 2
5 8
1 3
3 5
6 7
3 4
%%%%
41
%%%% end
*/
