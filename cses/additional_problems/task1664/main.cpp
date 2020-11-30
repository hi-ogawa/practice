// AC

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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<array<int, 2>> ls(n), qs(nq); // [1, 10^6]
  cin >> ls >> qs;

  // Filter out useless segments
  sort(ALL(ls), [](auto x, auto y) { return make_tuple(x[1], -x[0]) < make_tuple(y[1], -y[0]); });

  vector<array<int, 2>> ls_tmp;
  ls_tmp.push_back({0, 0}); // Add fake left most segment to make binary lifting simpler
  int l_max = 0;
  for (auto [l, r] : ls) {
    if (l_max < l) {
      l_max = l;
      ls_tmp.push_back({l, r});
    }
  }
  ls = ls_tmp;
  n = ls.size();
  dbg(ls);

  // Construct "optimal chains"
  vector<int> parents(n);
  FOR(i, 0, n) {
    auto [l, r] = ls[i];
    auto it = upper_bound(ALL(ls), array<int, 2>({0, l}), [](auto x, auto y) { return x[1] < y[1]; });
    if (it != ls.begin()) {
      int j = distance(ls.begin(), prev(it));
      parents[i] = j;
    }
  }
  dbg(parents);

  // Binary lifting
  int b_lim = 32 - __builtin_clz(n);
  vector<vector<int>> table(b_lim, vector<int>(n));
  table[0] = parents;
  FOR(b, 1, b_lim) {
    FOR(i, 0, n) {
      table[b][i] = table[b - 1][table[b - 1][i]];
    }
  }
  dbg2(table);

  // Find optimal chain within [ql, qr]
  auto solve = [&](int ql, int qr) -> int {
    // Find right most segment
    auto it = upper_bound(ALL(ls), array<int, 2>({0, qr}), [](auto x, auto y) { return x[1] < y[1]; });
    if (it == ls.begin()) { return 0; }

    int x = distance(ls.begin(), prev(it));
    if (ls[x][0] < ql) { return 0; }
    dbg(ql, qr, x, ls[x]);

    // Binary lift until reaching boundary
    int res = 1;
    int b = b_lim - 1;
    while (b >= 0) {
      int y = table[b][x];
      if (ls[y][0] < ql) { b--; continue; }
      x = y;
      res += (1 << b);
    }
    return res;
  };

  for (auto [ql, qr] : qs) {
    auto res = solve(ql, qr);
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1664/main.cpp

%%%% begin
4 3
2 5
6 10
4 7
9 10
5 9
2 10
7 10
%%%%
0
2
1
%%%% end
*/
