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

// Compute once for all test cases
vector<vector<int>> ls;
vector<vector<int>> ls_cumsum;

void precompute() {
  int k = 5;
  int n = 100000;
  // int n = 100;
  vector<int> ks(n + 1, 0);

  // Sieve
  RANGE(p, 2, n + 1) {
    if (ks[p] > 0) { continue; }
    for(int q = p; q <= n; q += p) {
      ks[q]++;
    }
  }

  // Cumsum
  ls.assign(k + 1, vector<int>(n + 1, 0));
  RANGE(i, 0, n + 1) {
    if (ks[i] <= k) {
      ls[ks[i]][i] = 1;
    }
  }

  ls_cumsum.assign(k + 1, vector<int>(n + 1, 0));
  RANGE(i, 1, n + 1) {
    RANGE(j, 1, k + 1) {
      ls_cumsum[j][i] = ls_cumsum[j][i - 1] + ls[j][i];
    }
  }

  // DD(ls);
  // DD(ls_cumsum);
}

void mainCase() {
  ll a, b, k;
  cin >> a >> b >> k;
  // k <= 5
  // a, b <= 10^5

  ll res = ls_cumsum[k][b] - ls_cumsum[k][a - 1];
  cout << res << endl;
}

int main() {
  // Compute once for all test cases with given bound
  precompute();

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
python misc/run.py codechef/LRNDSA05/KPRIME/main.cpp --check

%%%% begin
4
2 5 1
4 10 2
14 15 2
2 20 3
%%%%
4
2
2
0
%%%% end
*/
