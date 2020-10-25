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
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ls(n); // [0, 3]
  cin >> ls;

  //
  // Try to pair "src" and "dst" (note that one element can be both "src" and "dst")
  //   "1"
  //
  //   "2" -> "1"
  //
  //   "3" -> "1"
  //       -> "2"
  //       -> '3
  //

  vector<array<int, 2>> events; // (x, 0/1/2)
  FOR(i, 0, n) {
    events.push_back({i, ls[i]});
  }
  sort(ALL(events));
  reverse(ALL(events));

  int row = n - 1;
  map<int, vector<int>> res;
  array<vector<int>, 4> dst;
  bool ok = 1;

  for (auto [x, t] : events) {
    dbg(x, t);
    if (t == 1) {
      if (row < 0) { ok = 0; break; }
      res[x].push_back(row);
      row--;
      dst[1].push_back(x);
    }

    if (t == 2) {
      // Find 1 on the right
      if (dst[1].empty()) { ok = 0; break; }
      int x2 = dst[1].back(); dst[1].pop_back();
      int r = res[x2].back();
      res[x].push_back(r);
      dst[2].push_back(x);
    }

    if (t == 3) {
      // Find 1/2/3 on the right
      int x2 = -1;
      for (auto i : {2, 3, 1}) {
        if (!dst[i].empty()) {
          x2 = dst[i].back(); dst[i].pop_back();
          break;
        }
      }
      if (x2 == -1) { ok = 0; break; }
      if (row < 0) { ok = 0; break; }
      res[x].push_back(row);
      res[x2].push_back(row);
      row--;
      dst[3].push_back(x);
    }
  }
  if (!ok) { cout << -1 << "\n"; return; }

  int k = 0;
  for (auto& [x, ys] : res) {
    k += ys.size();
  }
  cout << k << "\n";
  for (auto& [x, ys] : res) {
    for (auto y : ys) {
      cout << (y + 1) << " " << (x + 1) << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1428/d/main_v2.cpp

%%%% begin
4
2 1 3 1
%%%%
4
2 1
2 2
3 3
4 4
3 4
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
