// AFTER CONTEST, WIP

// NOTE: A bit of refactoring after contest

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
template<class T, size_t N>  istream& operator>>(istream& i, array<T, N>& x)  { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T, size_t N>  ostream& operator<<(ostream& o, const array<T, N>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, m, k; // n, m <= 3000, k <= 10^5
  cin >> n >> m >> k;

  map<ll, map<ll, ll>> vs;
  FOR(i, 0, k) {
    ll x, y, v;
    cin >> x >> y >> v;
    x--; y--; // zero-based
    vs[x][y] = v;
  }
  // DD(vs);

  auto getMax = [](auto& x) { return *max_element(ALL(x)); };

  vector<array<ll, 4>> dp(m, array<ll, 4>({0, 0, 0, 0}));
  auto dp_prev = dp;
  FOR(i, 0, n) {
    if (i) {
      dp[0][0] = getMax(dp_prev[0]);
    }
    if (vs[i].count(0)) {
      dp[0][1] = dp[0][0] + vs[i][0];
    }
    FOR(j, 1, m) {
      dp[j] = dp[j - 1];
      if (i) {
        dp[j][0] = max(dp[j][0], getMax(dp_prev[j]));
      }
      if (vs[i].count(j)) {
        FOR(p, 1, 4) {
          dp[j][p] = max(dp[j - 1][p], dp[j - 1][p - 1] + vs[i][j]);
        }
        if (i) {
          dp[j][1] = max(dp[j][1], getMax(dp_prev[j]) + vs[i][j]);
        }
      }
    }
    dp_prev = dp;
    DD(dp);
  }

  ll res = getMax(dp[m - 1]);
  cout << res << endl;
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc175/e/main_v2.cpp --check

%%%% begin
2 5 5
1 1 3
2 4 20
1 2 1
1 3 4
1 4 2
%%%%
29
%%%% end
*/
