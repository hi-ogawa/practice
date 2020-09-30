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

// Main
void mainCase() {
  int n; // [2, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [-10^9, 10^9]
  cin >> ls;

  // dp(x, k) = max sum when taking non adjacent "k" out of suffix "2k + x" (where x = +1/0/-1)
  const ll kInf = 1e18;
  vector<vector<ll>> _dp(3, vector<ll>(n, -kInf));

  function<ll(int, int, int)> dpRec = [&](int x, int k, int i) -> ll {
    if (k == 0) { return 0; }
    if (_dp[x + 1][k] != -kInf) { return _dp[x + 1][k]; }
    if (x == -1) {
      return _dp[x + 1][k] = dpRec(-1, k - 1, i + 2) + ls[i];
    }
    if (x == 0) {
      ll v0 = dpRec(-1, k, i + 1);
      ll v1 = dpRec(0, k - 1, i + 2) + ls[i];
      return _dp[x + 1][k] = max(v0, v1);
    }
    // x == 1
    ll v0 = dpRec(0, k, i + 1);
    ll v1 = dpRec(1, k - 1, i + 2) + ls[i];
    return _dp[x + 1][k] = max(v0, v1);
  };

  ll res = dpRec(n % 2, n / 2, 0);
  cout << res << endl;;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc162/f/main.cpp --check

%%%% begin
6
1 2 3 4 5 6
%%%%
12
%%%% end

%%%% begin
5
-1000 -100 -10 0 10
%%%%
0
%%%% end

%%%% begin
10
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
%%%%
5000000000
%%%% end

%%%% begin
27
18 -28 18 28 -45 90 -45 23 -53 60 28 -74 -71 35 -26 -62 49 -77 57 24 -70 -93 69 -99 59 57 -49
%%%%
295
%%%% end
*/
