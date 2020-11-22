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
  int a, b, c, d; // [1, 10^9]
  cin >> a >> b >> c >> d;

  int x = abs(a - c);
  int y = abs(b - d);
  if (x > y) { swap(x, y); }

  auto solve = [&]() -> int {
    if (x == y) {
      if (x == 0) { return 0; }
      return 1;
    }

    // x < y
    int z = y - x;
    int w = x + y;

    dbg(x, y, z, w);
    if (w <= 3) { return 1; }
    if (w <= 6) { return 2; }
    if (z <= 3) { return 2; }
    if (z % 2 == 0) { return 2; }
    return 3;
  };

  int res = solve();
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc184/c/main.cpp

%%%% begin
1 1
5 6
%%%%
2
%%%% end

%%%% begin
1 1
1 200001
%%%%
2
%%%% end

%%%% begin
2 3
998244353 998244853
%%%%
3
%%%% end

%%%% begin
1 1
1 1
%%%%
0
%%%% end
*/
