// AFTER EDITORIAL, AC

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

// Order statistics tree (cf. https://codeforces.com/blog/entry/11080 by adamant)
#include <ext/pb_ds/assoc_container.hpp>
template<class Key, class Compare = less<Key>>
using ordered_set = __gnu_pbds::tree<
  Key, __gnu_pbds::null_type, Compare,
  __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

// Main
void mainCase() {
  int n, m, k; // [1, 2 x 10^5]
  cin >> n >> m >> k;
  vector<array<int, 2>> ls(k);
  cin >> ls;

  // Dummy blocks for convenience
  FOR(x, 1, n + 1) { ls.push_back({x, m + 1}); }
  FOR(y, 1, m + 1) { ls.push_back({n + 1, y}); }

  // First block at initial row/column
  int x_max = n + 1;
  int y_max = m + 1;
  for (auto [x, y] : ls) {
    if (y == 1) { x_max = min(x_max, x); }
    if (x == 1) { y_max = min(y_max, y); }
  }
  dbg(x_max, y_max);

  // Mapping for x -> y and y -> x
  vector<vector<int>> x2ys(n + 2), y2xs(m + 2);
  for (auto [x, y] : ls) {
    x2ys[x].push_back(y);
    y2xs[y].push_back(x);
  }
  for (auto& v : x2ys) { sort(ALL(v)); }
  for (auto& v : y2xs) { sort(ALL(v)); }

  // Count reachable cells with doubly counting for two ways
  ll cnt_x = 0;
  ll cnt_y = 0;
  FOR(x, 1, x_max) { cnt_x += (x2ys[x][0] - 1); }
  FOR(y, 1, y_max) { cnt_y += (y2xs[y][0]-  1); }
  dbg(cnt_x, cnt_y);

  // Take care double count
  vector<array<int, 3>> events; // (x, count-or-erase, y)
  FOR(y, 1, y_max) { events.push_back({y2xs[y][0], 0, y}); }
  FOR(x, 1, x_max) { events.push_back({x, 1, x2ys[x][0]}); }
  sort(ALL(events));

  ordered_set<int> ys;
  FOR(y, 1, y_max) { ys.insert(y); }

  ll double_cnt = 0;
  for (auto [x, t, y] : events) {
    if (t == 0) { // erase
      assert(ys.find(y) != ys.end());
      ys.erase(y);
    }
    if (t == 1) { // count
      double_cnt += ys.order_of_key(y);
    }
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
python misc/run.py atcoder/abc186/f/main_v2.cpp

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
