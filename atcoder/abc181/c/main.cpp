// CONTEST, AC

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
  int n; // [3, 100]
  cin >> n;
  vector<array<int, 2>> ls(n); // [-1000, 1000], distinct
  cin >> ls;

  bool ok = 0;
  FOR(i, 0, n) {
    auto [x0, y0] = ls[i];
    // Count slopes from (x0, y0)
    map<array<int, 2>, int> cnts;
    FOR(j, 0, n) {
      if (i == j) { continue; }
      auto [x, y] = ls[j];
      // Normalize (1, 0) or (dx, dy > 0)
      int dx = x - x0, dy = y - y0;
      if (dy == 0) { dx = 1; }
      if (dy < 0) { dx *= -1, dy *= -1; }
      int g = gcd(dx, dy);
      dx /= g; dy /= g;
      cnts[{dx, dy}]++;
    }
    for (auto [k, v] : cnts) {
      if (v >= 2) {
        ok = 1;
        break;
      }
    }
    if (ok) { break; }
  }
  cout << (ok ? "Yes" : "No") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc181/c/main.cpp

%%%% begin
4
0 1
0 2
0 3
1 1
%%%%
Yes
%%%% end

%%%% begin
14
5 5
0 1
2 5
8 0
2 1
0 0
3 6
8 6
5 9
7 9
3 4
9 2
9 8
7 2
%%%%
No
%%%% end

%%%% begin
9
8 2
2 3
1 3
3 7
1 0
8 8
5 6
9 7
0 1
%%%%
Yes
%%%% end
*/
