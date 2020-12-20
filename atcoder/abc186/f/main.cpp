// WA

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
  int n, m, k; // [1, 2 x 10^5]
  cin >> n >> m >> k;
  vector<array<int, 2>> ls(k);
  cin >> ls;

  // Dummy block for convinience
  ls.push_back({n + 1, 1});
  ls.push_back({1, m + 1});

  // Count reachable cells with doubly counting for two ways
  int x_max = n + 1;
  int y_max = m + 1;
  for (auto [x, y] : ls) {
    if (y == 1) { x_max = min(x_max, x); }
    if (x == 1) { y_max = min(y_max, y); }
  }
  dbg(x_max, y_max);

  ll cnt_x = 0, cnt_y = 0;
  sort(ALL(ls));
  FOR(x, 1, x_max) {
    auto it = lower_bound(ALL(ls), array<int, 2>({x, 0}));
    assert(it != ls.end());
    auto [x0, y0] = *it;
    cnt_x += (x0 == x) ? (y0 - 1) : m;
  }

  auto compare = [](auto x, auto y) { return tie(x[1], x[0]) < tie(y[1], y[0]); };
  sort(ALL(ls), compare);
  FOR(y, 1, y_max) {
    auto it = lower_bound(ALL(ls), array<int, 2>({0, y}), compare);
    assert(it != ls.end());
    auto [x0, y0] = *it;
    cnt_y += (y0 == y) ? (x0 - 1) : n;
  }
  dbg(cnt_x, cnt_y);

  // Take care double count (which is the area of the "stair case" geometry)
  // TODO: this is incorrect (see 1st test case)
  sort(ALL(ls));
  vector<array<int, 2>> ps;
  ps.push_back({1, m + 1});
  for (auto [x, y] : ls) {
    auto [x0, y0] = ps.back();
    assert(x0 <= x);
    if (x0 == x) {
      if (y0 > y) {
        ps.pop_back();
        ps.push_back({x, y});
      }
      continue;
    }
    // x0 < x
    if (y0 <= y) { continue; }
    ps.push_back({x, y});
  }
  dbg(ps);

  ll double_cnt = 0;
  FOR(i, 0, ps.size() - 1) {
    auto [x1, y1] = ps[i];
    auto [x2, y2] = ps[i + 1];
    double_cnt += (ll)(x2 - x1) * (y1 - 1);
  }

  ll res = cnt_x + cnt_y - double_cnt;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc186/f/main.cpp

%%%% begin
3 3 1
2 2
%%%%
8
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
