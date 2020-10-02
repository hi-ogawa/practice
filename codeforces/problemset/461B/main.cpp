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

// Modulo
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

using mint = ModInt<(ll)1e9 + 7>;

// Main
void mainCase() {
  int n; // [2, 10^5]
  cin >> n;
  vector<vector<int>> adj(n);
  FOR(i, 0, n - 1) {
    int v = i + 1, u;
    cin >> u;
    adj[v].push_back(u);
    adj[u].push_back(v);
  }
  vector<int> ls(n);
  cin >> ls;

  // dp(0, v) = #{ ways to cut v-subtree s.t. without "1" in v-component}
  // dp(1, v) = #{ ways to cut v-subtree s.t. with    "1" in v-component}
  vector<array<mint, 2>> dp(n, {1, 1});
  function<void(int, int)> dfs = [&](int v, int vp) {
    mint cnt_no_one = 1;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v);
      // Already zero or cut this edge if there's "1"
      cnt_no_one *= (dp[u][0] + dp[u][1]);
    }
    mint cnt_single_one = 0;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      // Pick "1" from u-subtree
      cnt_single_one += cnt_no_one * dp[u][1] / (dp[u][0] + dp[u][1]);
    }
    if (ls[v] == 0) {
      dp[v][0] = cnt_no_one;
      dp[v][1] = cnt_single_one;
    }
    if (ls[v] == 1) {
      dp[v][0] = 0; // no ways without "1"
      dp[v][1] = cnt_no_one;
    }
  };
  dfs(0, 0);

  auto res = dp[0][1];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/461B/main.cpp --check

%%%% begin
3
0 0
0 1 1
%%%%
2
%%%% end

%%%% begin
6
0 1 1 0 4
1 1 0 0 1 0
%%%%
1
%%%% end

%%%% begin
10
0 1 2 1 4 4 4 0 8
0 0 0 1 0 1 1 0 0 1
%%%%
27
%%%% end
*/
