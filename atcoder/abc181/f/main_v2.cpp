// AFTER EDITORIAL, AC

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

// DSU
struct Dsu {
  vector<int> ps;
  Dsu(int n) { ps.resize(n); iota(ALL(ps), 0); }
  int find(int a) {
    if (a == ps[a]) { return a; }
    return ps[a] = find(ps[a]);
  }
  void merge(int dst, int src) {
    ps[find(src)] = find(dst);
  }
};

using Real = double;
const Real kEps = 1e-7;

// Main
void mainCase() {
  int n; // [1, 100]
  cin >> n;
  vector<array<Real, 2>> ls(n); // (-100, 100), distinct
  cin >> ls;

  const Real lim = 100;

  // Define graph vertices and lower/upper boundaries
  int k = 3 * n + 2;
  int v0 = 3 * n;
  int v1 = 3 * n + 1;
  vector<array<Real, 2>> ps(k);
  FOR(i, 0, n) {
    auto [x, y] = ls[i];
    ps[i] = {x, y};
    ps[i + n] = {x, -lim}; // lower boudnary
    ps[i + 2 * n] = {x, +lim}; // upper boudnary
  }
  ps[v0] = {-lim, -lim};
  ps[v1] = {-lim, +lim};

  // f(z) = 1 \iff ball size z can pass through
  auto evaluate = [&](Real z) -> bool {
    // Define edges
    Dsu dsu(k);
    FOR(i, 0, k) {
      FOR(j, i + 1, k) {
        auto [x1, y1] = ps[i];
        auto [x2, y2] = ps[j];
        auto dx = x1 - x2, dy = y1 - y2;
        if (dx * dx + dy * dy < z * z) {
          dsu.merge(i, j);
        }
      }
    }
    FOR(i, 0, n) {
      dsu.merge(v0, i + n); // lower boundary
      dsu.merge(v1, i + 2 * n); // upper boundary
    }

    // Check if lower and upper boundaries are disconnected
    return dsu.find(v0) != dsu.find(v1);
  };

  // max { x | f(x) = 1 }
  auto search = [&]() -> Real {
    Real x0 = 0, x1 = 200; // [x0, x1)
    while (x1 - x0 > kEps) {
      Real x = (x0 + x1) / 2;
      if (evaluate(x)) {
        x0 = x;
      } else {
        x1 = x;
      }
    }
    return x0;
  };

  auto res = search();
  cout << fixed << setprecision(numeric_limits<Real>::digits10 + 1) << (res / 2) << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc181/f/main.cpp

%%%% begin
2
0 -40
0 40
%%%%
40
%%%% end

%%%% begin
4
0 -10
99 10
0 91
99 -91
%%%%
50.5
%%%% end

%%%% begin
10
-90 40
20 -30
0 -90
10 -70
80 70
-90 30
-20 -80
10 90
50 30
60 -70
%%%%
33.541019662496845446
%%%% end

%%%% begin
10
65 -90
-34 -2
62 99
42 -13
47 -84
84 87
16 -78
56 35
90 8
90 19
%%%%
35.003571246374276203
%%%% end
*/
