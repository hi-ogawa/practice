// AFTER CONTEST, TLE

// NOTE: clearly this strategy is N^3 thus TLE.

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
constexpr ll kModulo = 998244353;

void mainCase() {
  int n, s;
  cin >> n >> s;
  vector<int> ls(n, 0);
  cin >> ls;
  // DD(ls);

  // DP for subset sum (usual version as a reference)
  // {
  //   vector<vector<ll>> dp(n + 1, vector<ll>(s + 1, 0));
  //   dp[0][0] = 1;
  //   RANGE(i, 1, n + 1) {
  //     RANGE(j, 0, s + 1) {
  //       dp[i][j] += dp[i - 1][j];
  //       int a = ls[i - 1];
  //       if (j - a >= 0) {
  //         dp[i][j] += dp[i - 1][j - a];
  //       }
  //     }
  //   }
  //   DD(dp);
  // }

  // DP for subset sum
  // incrementally row-by-row
  // also keeping track of how many numbers are used to realize "j"
  //   dp[j][k] = |{W | |W| = k, ∑_{i ∈ W} Ai = j }|
  //            = <number of ways to make sum = j using exactly k values>
  vector<map<int, ll>> dp(s + 1, map<int, ll>());
  dp[0][0] = 1;
  RANGE(i, 0, n) {
    int a = ls[i];
    for (int j = s; j >= a; j--) {
      for (auto [k, l] : dp[j - a]) {
        dp[j][k + 1] += l;
        dp[j][k + 1] %= kModulo;
      }
    }
  }
  // DD(dp);

  // Usual mod precomputation
  auto mul = [](ll x, ll y) { return (x * y) % kModulo; };
  vector<ll> two_exp(n + 1, 0);
  two_exp[0] = 1;
  RANGE(i, 0, n) {
    two_exp[i + 1] = mul(2, two_exp[i]);
  }
  // DD(two_exp);

  ll res = 0;
  for (auto [k, l] : dp[s]) {
    res += mul(l, two_exp[n - k]);
    res %= kModulo;
  }
  cout << res << endl;
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc169/f/main.cpp --check

%%%% begin
3 4
2 2 4
%%%%
6
%%%% end


%%%% begin
5 8
9 9 9 9 9
%%%%
0
%%%% end


%%%% begin
10 10
3 1 4 1 5 9 2 6 5 3
%%%%
3296
%%%% end
*/
