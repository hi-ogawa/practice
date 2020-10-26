// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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
  int k = 6;
  vector<int> xs(k); // [1, 10^9]
  cin >> xs;
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ys(n); // [1, 10^9]
  cin >> ys;

  // k x n points (n types with each k points)
  vector<array<int, 2>> ls; // (x, type)
  FOR(i, 0, k) {
    FOR(j, 0, n) {
      ls.push_back({ys[j] - xs[i], j});
    }
  }
  sort(ALL(ls));

  // Valid intervals (interval containing n types)
  vector<array<int, 2>> segs;
  int m = k * n;
  int i0 = 0, i1 = 0;
  int cnt_unique = 0;
  vector<int> cnts(n);
  while (i0 < m) {
    while (cnt_unique < n && i1 < m) {
      int t1 = ls[i1++][1];
      cnt_unique += (cnts[t1]++ == 0);
    }
    if (cnt_unique < n) { break; }
    segs.push_back({i0, i1});
    int t0 = ls[i0++][1];
    cnt_unique -= (--cnts[t0] == 0);
  }
  dbg(segs);

  int res = 1e9;
  for (auto [l, r] : segs) {
    int t = ls[r - 1][0] - ls[l][0];
    res = min(res, t);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1435/c/main_v2.cpp

%%%% begin
1 4 100 10 30 5
6
101 104 105 110 130 200
%%%%
0
%%%% end

%%%% begin
1 1 2 2 3 3
7
13 4 11 12 11 13 12
%%%%
7
%%%% end
*/
