// AFTER CONTEST, AC

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
void mainCase() {
  ll l, s; // <= 10^5
  cin >> l >> s;

  // a, .., z, A, .., Z
  // 1, .., 26, 27, .., 52
  ll n = 52;
  if (l > n) {
    cout << 0 << endl;
    return;
  }

  vector<vector<ll>> dp(s + 1, vector<ll>(l + 1, 0));
  dp[0][0] = 1;
  RANGE(a, 1, n + 1) {
    for (int j = s - a; j >= 0; j--) {
      RANGE(k, 0, l) {
        dp[j + a][k + 1] += dp[j][k];
      }
    }
  }
  // DD(dp);

  cout << dp[s][l] << endl;
}

int main() {
  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    cout << "Case " << (i + 1) << ": ";
    mainCase();
  };
  return 0;
}

/*
python misc/run.py codechef/LRNDSA07/AUHASH/main.cpp --check

%%%% begin
1
2 10
%%%%
Case 1: 4
%%%% end

%%%% begin
1
100 10
%%%%
Case 1: 0
%%%% end

%%%% begin
3
2 10
27 100
5 19
%%%%
Case 1: 4
Case 2: 0
Case 3: 5
%%%% end
*/
