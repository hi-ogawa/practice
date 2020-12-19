// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
using ll = int64_t;
using ull = uint64_t;
// namespace std {
// template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
// template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
// template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
// template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
// template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
// istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
// template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
// ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
// }

#ifdef DEBUG
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase(int case_num) {
  int n; // [2, 100]
  cin >> n;
  vector<vector<char>> board(n, vector<char>(n)); // {0, +, -}
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      cin >> board[i][j];
    }
  }

  //
  // PROP.
  //   ri + cj = 0  <=>  ri - (-cj) = (-cj) - ri = 0
  //
  //   ri + cj > 0  <=>  (-cj) - ri <= -1
  //
  //   ri + cj < 0  <=>  ri - (-cj) <= -1
  //

  // Bellman-Ford to solve x_j - x_i <= a_{i,j}
  int nv = 2 * n + 1;
  int root = 2 * n;
  int bound = 1e4; // Arbitrary bound for x ∈ [-bound, +bound] (TODO: is this rigorous??)
  const int kInf = 1e9;

  vector<vector<int>> adj(nv, vector<int>(nv, kInf));
  FOR(i, 0, n) {
    adj[i][i] = adj[i + n][i + n] = 0;
    adj[root][i] = adj[root][i + n] = bound;
    adj[i][root] = adj[i + n][root] = bound;
    FOR(j, 0, n) {
      auto c = board[i][j];
      if (c == '0') { adj[i][j + n] = adj[j + n][i] = 0; }
      if (c == '+') { adj[i][j + n] = -1; }
      if (c == '-') { adj[j + n][i] = -1; }
    }
  }
  dbg2(adj);

  vector<int> dists(nv, kInf);
  dists[root] = 0;
  bool neg_cycle = 0;
  FOR(k, 0, nv) {
    FOR(i, 0, nv) {
      FOR(j, 0, nv){
        auto d = dists[i] + adj[i][j];
        if (d < dists[j]) {
          dists[j] = d;
          neg_cycle = (k == nv - 1);
        }
      }
    }
  }
  dbg(dists);
  dbg(neg_cycle);

  // Values can be offset by x as r + x and c - x
  vector<int> rs(n), cs(n);
  FOR(i, 0, n) {
    rs[i] = +dists[i];
    cs[i] = -dists[i + n];
  }

  // Cost when offset by x
  //   f(x) = ∑ |ri + x| + |ci - x|
  auto evaluate = [&](int x) -> int {
    int res = 0;
    FOR(i, 0, n) {
      res += abs(rs[i] + x) + abs(cs[i] - x);
    }
    return res;
  };

  // Ternary search
  auto search = [&]() -> int {
    int x0 = -bound, x1 = +bound; // [x0, x1)
    while (x0 + 2 < x1) {
      auto xl = x0 + (x1 - x0) / 3;
      auto xr = x0 + (x1 - x0) / 3 * 2;
      auto fl = evaluate(xl);
      auto fr = evaluate(xr);
      if (fl < fr) { x1 = xr; } else { x0 = xl; }
    }
    int res = evaluate(x0);
    FOR(x, x0 + 1, x1) {
      res = min(res, evaluate(x));
    }
    return res;
  };

  int res = neg_cycle ? -1 : search();
  cout << "Case " << case_num << ": " << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  for (int t = 1; ; t++) {
    string s;
    cin >> s;
    if (s == "-1") { break; }
    reverse(ALL(s));
    for (auto c : s) { cin.putback(c); }
    mainCase(t);
  }
  return 0;
}

/*
python misc/run.py onlinejudge/11671/main.cpp

%%%% begin
4
0+00
-+--
0+00
0+00
2
+0
00
-1
%%%%
Case 1: 3
Case 2: -1
%%%% end
*/
