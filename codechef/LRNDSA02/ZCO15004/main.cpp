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

void mainCase() {
  int n;
  cin >> n;
  vector<pair<int, int>> ls(n, {0, 0});
  cin >> ls;
  sort(ALL(ls)); // x_i <= x_i+1
  // DD(ls);

  //
  // Enumerate maximal two patterns of rectangles
  //
  int x_lim = 100000;
  int y_lim = 500;

  //
  // Pattern1: A = (x_i+1 - x_i) * y_lim
  //
  int max1 = 0;
  RANGE(i, 0, n - 1) {
    int a = (ls[i + 1].first - ls[i].first) * y_lim;
    max1 = max(max1, a);
  }
  max1 = max(max1, ls[0].first * y_lim); // first segment
  max1 = max(max1, (x_lim - ls[n - 1].first) * y_lim); // last segment
  // DD(max1);

  //
  // Pattern2: A = (R_i + L_i) * y_i  where R_i, L_i is "left/right-stopper" for x_i
  //

  // First we collect "stoppers" for each x_i
  vector<int> rights(n, -1);
  {
    vector<tuple<int, int, int>> ts(0, {0, 0, 0}); // x, y, i
    RANGE(i, 0, n) {
      int x, y;
      tie(x, y) = ls[i];
      while (!ts.empty() && get<1>(ts.back()) > y) {
        int j = get<2>(ts.back());
        rights[j] = i;
        ts.pop_back();
      }
      ts.push_back({x, y, i});
    }
  }

  vector<int> lefts(n, -1);
  {
    vector<tuple<int, int, int>> ts(0, {0, 0, 0}); // x, y, i
    for (int i = n - 1; i >= 0; i--) {
      int x, y;
      tie(x, y) = ls[i];
      while (!ts.empty() && get<1>(ts.back()) > y) {
        int j = get<2>(ts.back());
        lefts[j] = i;
        ts.pop_back();
      }
      ts.push_back({x, y, i});
    }
  }
  // DD(rights);
  // DD(lefts);

  // Get areas from stoppers
  int max2 = 0;
  RANGE(i, 0, n) {
    int j1 = rights[i];
    int j2 = lefts[i];
    int xr = j1 >= 0 ? ls[j1].first : x_lim;
    int xl = j2 >= 0 ? ls[j2].first : 0;
    int y = ls[i].second;
    int a = (xr - xl) * y;
    max2 = max(max2, a);
    // DD(tie(i, xl, xr, y, a));
  }
  // DD(max2);

  ll res = max(max1, max2);
  cout << res << endl;
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA02/ZCO15004/main.cpp --check

%%%% begin
5
1 4
2 3
3 2
5 1
5 2
%%%%
49997500
%%%% end

*/
