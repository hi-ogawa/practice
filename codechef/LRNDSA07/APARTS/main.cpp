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
  ll n, m; // <= 10^3
  cin >> n >> m;

  vector<vector<ll>> ls(n, vector<ll>(m, 0)); // <= n.m
  cin >> ls;
  // DD(ls);

  vector<vector<bool>> res(n, vector<bool>(m, 1));

  auto dp = ls;
  RANGE(i, 1, n) {
    RANGE(j, 0, m) {
      ll tmp = dp[i - 1][j];
      if (j - 1 >= 0) { tmp = max(tmp, dp[i - 1][j - 1]); }
      if (j + 1 <  m) { tmp = max(tmp, dp[i - 1][j + 1]); }
      res[i][j] = tmp < ls[i][j];
      dp[i][j] = max(ls[i][j], tmp);
    }
  }

  // Output
  RANGE(i, 0, n) {
    RANGE(j, 0, m) {
      cout << res[i][j];
    }
    cout << endl;
  }
}

int main() {
  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA07/APARTS/main.cpp --check

%%%% begin
1
3 4
1 3 7 10
9 2 4 11
8 12 5 6
%%%%
1111
1001
0100
%%%% end
*/
