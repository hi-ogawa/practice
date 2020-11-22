
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

// Main
void mainCase() {
  int n, m; // [1, 20]
  ll k; // [0, 10^18]
  cin >> n >> m >> k;
  vector<vector<ll>> ls(n, vector<ll>(m)); // [0, 10^18]
  cin >> ls;

  // Cum XOR of each row
  vector<vector<ll>> xs(n, vector<ll>(m + 1));
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      xs[i][j + 1] = xs[i][j] ^ ls[i][j];
    }
  }

  using map_impl = map<ll, ll>;

  //
  // PROP.
  //    #{non zero entries} is at most binom(n + m - 1, n - 1)
  //

  vector<map_impl> dp(m + 1), dp_zero(m + 1), dp_prev;
  dp[1][0] = 1;
  FOR(i, 0, n) {
    dp_prev = dp;
    dp = dp_zero;
    FOR(j, 1, m + 1) {
      FOR(j2, 1, j + 1) {
        for (auto [x, cnt] : dp_prev[j2]) {
          dp[j][x ^ xs[i][j] ^ xs[i][j2 - 1]] += cnt;
        }
      }
    }
    dbg2(dp);
  }

  auto res = dp[m][k];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1006F/main.cpp

%%%% begin
3 3 11
2 1 5
7 10 0
12 6 4
%%%%
3
%%%% end

%%%% begin
3 4 2
1 3 3 3
0 3 3 2
3 0 1 1
%%%%
5
%%%% end

%%%% begin
3 4 1000000000000000000
1 3 3 3
0 3 3 2
3 0 1 1
%%%%
0
%%%% end
*/
