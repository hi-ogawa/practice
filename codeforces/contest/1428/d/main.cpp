// WIP, WA

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
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ls(n); // [0, 3]
  cin >> ls;

  array<vector<int>, 4> src, dst;
  FOR(i, 0, n) {
    src[ls[i]].push_back(i);
  }
  dst = src;

  int row = n - 1;
  vector<array<int, 2>> res;
  map<int, int> res_map;

  auto solve = [&]() -> bool {
    FOR(i, 1, 4) { reverse(ALL(src[i])); }

    // Handle "1"
    for (auto i : src[1]) {
      res.push_back({row, i});
      res_map[i] = row;
      row--;
    }

    // TODO: "2" cannot always take right most "1" available (e.g. when "2 1 3 1")

    // Handle "2" -> "1"
    for (auto i : src[2]) {
      if (dst[1].empty()) { return 0; }
      int j = dst[1].back(); dst[1].pop_back();
      if (j <= i) { return 0; }
      assert(res_map.count(j));
      int r = res_map[j];
      res.push_back({r, i});
      res_map[i] = r;
    }

    // Handle "3" -> "1", "2", "3"
    set<int> dst_rest;
    for (auto i : dst[1]) { dst_rest.insert(i); }
    for (auto i : dst[2]) { dst_rest.insert(i); }

    for (auto i : src[3]) {
      if (dst_rest.empty()) { return 0; }
      int j = *dst_rest.rbegin(); dst_rest.erase(j);
      if (j <= i) { return 0; }
      if (row < 0) { return 0; }
      res.push_back({row, i});
      res.push_back({row, j});
      row--;
      dst_rest.insert(i);
    }

    return 1;
  };

  bool ok = solve();
  if (!ok) { cout << -1 << "\n"; return; }

  cout << res.size() << "\n";
  for (auto [x, y] : res) {
    x++; y++;
    cout << x << " " << y << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1428/d/main.cpp

%%%% begin
4
2 1 3 1
%%%%
???
%%%% end

%%%% begin
6
2 0 3 0 1 1
%%%%
5
2 1
2 5
3 3
3 6
5 6
%%%% end

%%%% begin
1
0
%%%%
0
%%%% end

%%%% begin
6
3 2 2 2 1 1
%%%%
-1
%%%% end
*/
