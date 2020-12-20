// WIP

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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
  int n, m, k;
  cin >> n >> m >> k;
  vector<array<int, 2>> ls(k);
  cin >> ls;

  ls.push_back({n + 1, 1});
  ls.push_back({1, m + 1});

  int x_max = n + 1;
  int y_max = m + 1;
  for (auto [x, y] : ls) {
    if (y == 1) { x_max = min(x_max, x); }
    if (x == 1) { y_max = min(y_max, y); }
  }

  vector<vector<int>> board(n + 1, vector<int>(m + 1));

  sort(ALL(ls));
  FOR(x, 1, x_max) {
    auto it = lower_bound(ALL(ls), array<int, 2>({x, 0}));
    assert(it != ls.end());
    auto [x0, y0] = *it;
    FOR(y, 1, (x0 == x) ? y0 : (m + 1)) {
      board[x][y] = 1;
    }
  }

  auto compare = [](auto x, auto y) { return tie(x[1], x[0]) < tie(y[1], y[0]); };
  sort(ALL(ls), compare);
  FOR(y, 1, y_max) {
    auto it = lower_bound(ALL(ls), array<int, 2>({0, y}), compare);
    assert(it != ls.end());
    auto [x0, y0] = *it;
    FOR(x, 1, (y0 == y) ? x0 : (n + 1)) {
      board[x][y] = 1;
    }
  }

  ll res = 0;
  FOR(i, 1, n + 1) {
    FOR(j, 1, m + 1) {
      res += board[i][j];
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc186/f/brute.cpp

%%%% begin
4 3 3
2 2
3 3
3 1
%%%%
5
%%%% end

%%%% begin
4 3 2
2 2
3 3
%%%%
10
%%%% end

%%%% begin
5 4 4
3 2
3 4
4 2
5 2
%%%%
14
%%%% end

%%%% begin
200000 200000 0
%%%%
40000000000
%%%% end
*/
