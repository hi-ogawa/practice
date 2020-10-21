// AC

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
  int n; // [3, 200]
  cin >> n;
  vector<vector<char>> ls(n, vector<char>(n));
  cin >> ls;

  int x0 = ls[1][0] - '0';
  int x1 = ls[0][1] - '0';
  int y0 = ls[n - 1][n - 2] - '0';
  int y1 = ls[n - 2][n - 1] - '0';
  dbg(x0, x1, y0, y1);

  vector<array<int, 2>> res;
  auto solve = [&]() {
    if (x0 + x1 == 0) {
      if (y0 == 0) { res.push_back({n - 1, n - 2}); }
      if (y1 == 0) { res.push_back({n - 2, n - 1}); }
      return;
    }
    if (x0 + x1 == 2) {
      if (y0 == 1) { res.push_back({n - 1, n - 2}); }
      if (y1 == 1) { res.push_back({n - 2, n - 1}); }
      return;
    }
    if (y0 + y1 == 0) {
      if (x0 == 0) { res.push_back({1, 0}); }
      if (x1 == 0) { res.push_back({0, 1}); }
      return;
    }
    if (y0 + y1 == 2) {
      if (x0 == 1) { res.push_back({1, 0}); }
      if (x1 == 1) { res.push_back({0, 1}); }
      return;
    }
    if (x0 == 1) { res.push_back({1, 0}); }
    if (x1 == 1) { res.push_back({0, 1}); }
    if (y0 == 0) { res.push_back({n - 1, n - 2}); }
    if (y1 == 0) { res.push_back({n - 2, n - 1}); }
  };
  solve();
  dbg(res);

  cout << res.size() << "\n";
  for (auto [x, y] : res) {
    x++; y++;
    cout << x << " " << y << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1421/b/main.cpp

%%%% begin
3
4
S010
0001
1000
111F
3
S10
101
01F
5
S0101
00000
01111
11111
0001F
%%%%
1
3 4
2
1 2
2 1
0
%%%% end
*/
