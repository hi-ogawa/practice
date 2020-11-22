// AFTER EDITORIAL, WIP

// NOTE: "meet in the middle" by splitting diagonally

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

  int mid = (n + m - 2) / 2;

  using map_impl = map<ll, int>;

  vector<vector<map_impl>> dp1(n, vector<map_impl>(m));
  vector<vector<map_impl>> dp2(n, vector<map_impl>(m));
  dp1[0][0][ls[0][0]] = 1;
  dp2[n - 1][m - 1][ls[n - 1][m - 1]] = 1;

  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (i + j > mid) { break; }
      auto y = ls[i][j];
      if (i) {
        for (auto [x, cnt] : dp1[i - 1][j]) {
          dp1[i][j][x ^ y] += cnt;
        }
      }
      if (j) {
        for (auto [x, cnt] : dp1[i][j - 1]) {
          dp1[i][j][x ^ y] += cnt;
        }
      }
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      if (i + j < mid) { break; }
      auto y = ls[i][j];
      if (i < n - 1) {
        for (auto [x, cnt] : dp2[i + 1][j]) {
          dp2[i][j][x ^ y] += cnt;
        }
      }
      if (j < m - 1) {
        for (auto [x, cnt] : dp2[i][j + 1]) {
          dp2[i][j][x ^ y] += cnt;
        }
      }
    }
  }
  dbg2(dp1);
  dbg2(dp2);

  ll res = 0;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (i + j == mid) {
        auto& mp1 = dp1[i][j];
        auto& mp2 = dp2[i][j];
        auto y = ls[i][j];
        for (auto [x, cnt] : mp1) {
          res += (ll)cnt * mp2[x ^ y ^ k];
        }
      }
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
python misc/run.py codeforces/problemset/1006F/main_v3.cpp

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
