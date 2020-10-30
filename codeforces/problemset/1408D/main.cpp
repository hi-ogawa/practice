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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, m; // [1, 2000]
  cin >> n >> m;
  vector<array<int, 2>> ls1(n), ls2(m); // [0, 10^6]
  cin >> ls1 >> ls2;

  // Translate "search lights" wrt each "robbers" as origin
  vector<array<int, 2>> ls;
  for (auto [x1, y1] : ls1) {
    for (auto [x2, y2] : ls2) {
      int x = x2 - x1 + 1, y = y2 - y1 + 1;
      if (x > 0 && y > 0) {
        ls.push_back({x, y});
      }
    }
  }

  // Take intersection of "safe regions", which would look like a staircase:
  //
  //   --x
  //     |
  //     .--x
  //        |
  //        .------x
  //               |
  //               .----x
  //  (0,0)             |
  //
  sort(ALL(ls));
  vector<array<int, 2>> st;
  for (auto [x, y] : ls) {
    while (!st.empty() && st.back()[1] <= y) {
      st.pop_back();
    }
    st.push_back({x, y});
  }
  dbg(st);

  if (st.empty()) { cout << 0 << "\n"; return; }

  // Find distance to "safe regions"
  int res = 1e9;
  int k = st.size();
  res = min(res, st[0][1]);
  res = min(res, st[k - 1][0]);
  FOR(i, 0, k - 1) {
    // (Manhattan) distance to concave part of a staircase
    auto [x1, y1] = st[i];
    auto [x2, y2] = st[i + 1];
    res = min(res, x1 + y2);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1408D/main.cpp

%%%% begin
1 1
0 0
2 3
%%%%
3
%%%% end

%%%% begin
2 3
1 6
6 1
10 1
1 10
7 7
%%%%
4
%%%% end

%%%% begin
1 2
0 0
0 0
0 0
%%%%
1
%%%% end

%%%% begin
7 3
0 8
3 8
2 7
0 10
5 5
7 0
3 5
6 6
3 11
11 5
%%%%
6
%%%% end
*/
