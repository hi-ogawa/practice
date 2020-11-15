// CONTEST, AC

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

// Count within [10..0, n]
ll solveDP(ll n) {
  if (n == 0) { return 0; }

  vector<int> ds;
  while (n > 0) {
    ds.push_back(n % 10);
    n /= 10;
  }
  reverse(ALL(ds));
  int k = ds.size();
  vector<array<ll, 2>> dp(k, {-1, -1});

  // p : (reversed) digit positioin
  // b : bounded by x[p] or not
  function<ll(int p, int b)> dpRec = [&](int p, int b) -> ll {
    if (p == k) { return 1; }
    if (dp[p][b] != -1) { return dp[p][b]; }
    ll res = 0;
    FOR(d, 0, (b ? ds[p] : 9) + 1) {
      if ((p + 1) % 2 != d % 2) { continue; }
      int bb = b && (d == ds[p]);
      res += dpRec(p + 1, bb);
    }
    return dp[p][b] = res;
  };

  return dpRec(0, true);
}

// Main
void mainCase() {
  ll l, r; // [1, 10^18]
  cin >> l >> r;

  auto pow = [&](ll x, ll e) -> ll {
    ll y = 1;
    while (e > 0) {
      if (e & 1) { y *= x; }
      e >>= 1; x *= x;
    }
    return y;
  };

  // Count within [1, n]
  auto solve = [&](ll n) -> ll {
    int k = to_string(n).size();
    ll res = 0;

    // For length {1, .., k-1}
    FOR(l, 1, k) {
      res += solveDP(pow(10, l) - 1);
    }
    // For length k
    res += solveDP(n);

    return res;
  };

  ll res = solve(r) - solve(l - 1);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) {
    cout << "Case #" << (i + 1) << ": ";
    mainCase();
  }
  return 0;
}


/*
python misc/run.py google/kickstart-2020-h/2/main.cpp

%%%% begin
1
5 15
%%%%
Case #1: 6
%%%% end

%%%% begin
3
5 15
120 125
779 783
%%%%
Case #1: 6
Case #2: 3
Case #3: 2
%%%% end
*/
