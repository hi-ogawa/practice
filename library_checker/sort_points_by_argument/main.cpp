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
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<array<int, 2>> ls(n); // [-10^9, 10^9]
  cin >> ls;

  // Separate at y = 0
  vector<array<int, 2>> ls1, ls2, ls3, ls4;
  for (auto [x, y] : ls) {
    if (y == 0) { (x >= 0 ? ls2 : ls4).push_back({x, y}); }
    if (y < 0) { ls1.push_back({x, y}); }
    if (y > 0) { ls3.push_back({x, y}); }
  }

  // Sort by x1/y1 > x2/y2
  auto compare = [](auto lhs, auto rhs) {
    auto [x1, y1] = lhs;
    auto [x2, y2] = rhs;
    return (ll)x1 * y2 > (ll)x2 * y1;
  };
  sort(ALL(ls1), compare);
  sort(ALL(ls3), compare);

  for (auto& v : {ls1, ls2, ls3, ls4}) {
    for (auto [x, y] : v) {
      cout << x << " " << y << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/sort_points_by_argument/main.cpp

%%%% begin
8
1 0
0 0
-1 0
0 1
0 -1
1 1
2 2
-10 -1
%%%%
-10 -1
0 -1
1 0
0 0
1 1
2 2
0 1
-1 0
%%%% end
*/
