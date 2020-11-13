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
  vector<array<int, 4>> ls(4); // [-10^4, 10^4]
  cin >> ls;

  // Enumerate 4^4 from (0, 0, 0, 0) to (3, 3, 3, 3)

  auto nextDigits = [](vector<int>& ds, int base) -> bool {
    int c = 1;
    for (auto& d : ds) {
      d += c;
      c = d / base;
      d %= base;
    }
    return c == 0;
  };

  auto rotate = [](array<int, 4> xs, int n) -> array<int, 2> {
    auto [x, y, a, b] = xs;
    int dx = x - a;
    int dy = y - b;
    FOR(_, 0, n) {
      tie(dx, dy) = make_tuple(-dy, dx);
    }
    return {a + dx, b + dy};
  };

  auto isSquare = [](vector<array<int, 2>>& ps) -> bool {
    // Fix origin
    auto [x0, y0] = ps[0];
    for (auto& [x, y] : ps) {
      x -= x0; y -= y0;
    }

    // Enumerate 3!
    array<int, 3> qs = {1, 2, 3};
    bool ok = 0;
    do {
      auto [x1, y1] = ps[qs[0]];
      auto [x2, y2] = ps[qs[1]];
      auto [x3, y3] = ps[qs[2]];
      bool ok1 = x1 + x2 == x3 && y1 + y2 == y3; // Parralellogram
      bool ok2 = x1 * x2 + y1 * y2 == 0; // Orthogonal
      bool ok3 = x1 * x1 + y1 * y1 == x2 * x2 + y2 * y2; // Equal sides
      bool ok4 = x1 * x1 + y1 * y1 > 0; // Non degenerate
      if (ok1 && ok2 && ok3 && ok4) {
        ok = 1;
        break;
      }
    } while (next_permutation(ALL(qs)));

    return ok;
  };

  const int kInf = 1e9;
  int res = kInf;

  vector<int> rs(4);
  vector<array<int, 2>> ps(4);
  do {
    FOR(i, 0, 4) {
      ps[i] = rotate(ls[i], rs[i]);
    }
    bool ok = isSquare(ps);
    if (ok) {
      int t = accumulate(ALL(rs), 0);
      res = min(res, t);
    }
  } while (nextDigits(rs, 4));

  if (res == kInf) { res = -1; }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/474C/main.cpp

%%%% begin
1
1 1 0 0
-1 1 0 0
-1 1 0 0
1 -1 0 0
%%%%
1
%%%% end

%%%% begin
4
1 1 0 0
-1 1 0 0
-1 1 0 0
1 -1 0 0
1 1 0 0
-2 1 0 0
-1 1 0 0
1 -1 0 0
1 1 0 0
-1 1 0 0
-1 1 0 0
-1 1 0 0
2 2 0 1
-1 0 0 -2
3 0 0 -2
-1 1 -2 0
%%%%
1
-1
3
3
%%%% end
*/
