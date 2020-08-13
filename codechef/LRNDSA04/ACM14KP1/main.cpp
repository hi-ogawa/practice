// AFTER EDITORIAL, WIP, WA

// TODO: theory seems fine, maybe some typo?

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
template<class T, size_t N>  istream& operator>>(istream& i, array<T, N>& x)  { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T, size_t N>  ostream& operator<<(ostream& o, const array<T, N>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Misc
#define DEFINE_ARRAY_BIN_OP(NAME, OP) \
  template<class T, size_t N>                                                           \
  array<T, N> a ## NAME(const array<T, N>& x, const array<T, N>& y) {                   \
    array<T, N> z; for (size_t i = 0; i < N; i++) { z[i] = x[i] OP y[i]; } return z;    \
  }                                                                                     \
  template<class T, size_t N>                                                           \
  array<T, N> a ## NAME ## s(const array<T, N>& x, T y) {                               \
    array<T, N> z; for (size_t i = 0; i < N; i++) { z[i] = x[i] OP y; } return z;       \
  }                                                                                     \
  template<class T, size_t N>                                                           \
  array<T, N> a ## NAME ## eq(array<T, N>& x, const array<T, N>& y) {                   \
    for (size_t i = 0; i < N; i++) { x[i] = x[i] OP y[i]; } return x;                   \
  }                                                                                     \
  template<class T, size_t N>                                                           \
  array<T, N> a ## NAME ## eqs(array<T, N>& x, T y) {                                   \
    for (size_t i = 0; i < N; i++) { x[i] = x[i] OP y; } return x;                      \
  }                                                                                     \

DEFINE_ARRAY_BIN_OP(add, +)
DEFINE_ARRAY_BIN_OP(sub, -)
DEFINE_ARRAY_BIN_OP(mul, *)
DEFINE_ARRAY_BIN_OP(div, /)

using point = array<double, 2>;
double point_distance(const point& x, const point& y) {
  auto z = asub(x, y);
  z = amul(z, z);
  return sqrt(z[0] + z[1]);
}

constexpr double eps = 1e-10;

// Main
tuple<array<int, 3>, double> solveRec(int i0, int i1, vector<array<double, 2>>& ls) {
  int n = i1 - i0;
  //
  // Brute force small case
  //
  if (n <= 5) {
    array<int, 3> res = {};
    double res_d = 1e30;
    FOR(i, i0, i1) {
      FOR(j, i + 1, i1) {
        auto d1 = point_distance(ls[i], ls[j]);
        FOR(k, j + 1, i1) {
          auto d2 = point_distance(ls[j], ls[k]);
          auto d3 = point_distance(ls[k], ls[i]);
          auto d = d1 + d2 + d3;
          if (d < res_d) {
            res = {i, j, k};
            res_d = d;
          }
        }
      }
    }
    return {res, res_d};
  }

  //
  // Mean and variance
  //
  point acc = {};
  point acc2 = {};
  FOR(i, i0, i1) {
    aaddeq(acc, ls[i]);
    aaddeq(acc2, amul(ls[i], ls[i]));
  }
  point mean = adivs(acc, (double)n);
  point var = asub(adivs(acc2, (double)n), amul(mean, mean));
  // DD(tie(mean, var));

  //
  // Split axis of larger variance
  //
  int axis0 = var[0] >= var[1] ? 0 : 1;
  int axis1 = 1 - axis0;
  auto it0 = ls.begin() + i0;
  auto it1 = ls.begin() + i1;
  sort(it0, it1, [&](auto x, auto y) { return x[axis0] < y[axis0]; });

  //
  // Recursive call
  //
  int imid = (i0 + i1) / 2;
  array<int, 3> res0, res1;
  double res_d0, res_d1;
  tie(res0, res_d0) = solveRec(i0, imid, ls);
  tie(res1, res_d1) = solveRec(imid, i1, ls);
  // DD(tie(res0, res_d0, res1, res_d1));

  //
  // Merge results
  //
  array<int, 3> res = res_d0 < res_d1 ? res0 : res1;
  double res_d = min(res_d0, res_d1);

  // 1. Cull points far from the split boundary
  double boundary = (ls[imid][axis0] + ls[imid - 1][axis0]) / 2;
  int ib0 = i0;
  for(; ib0 < imid; ib0++) {
    if (boundary - ls[ib0][axis0] <= res_d / 2 + eps) { break; }
  }
  int ib1 = imid;
  for(; ib1 < i1; ib1++) {
    if (ls[ib1][axis0] - boundary > res_d / 2 + eps) { break; }
  }
  auto itb0 = ls.begin() + ib0;
  auto itb1 = ls.begin() + ib1;
  auto itmid = ls.begin() + imid;
  // DD(ls);
  // DD(tie(res_d, boundary));
  // DD(tie(i0, ib0, imid, ib1, i1));

  // 2. Sort by non-split axis
  sort(itb0, itmid, [&](auto x, auto y) { return x[axis1] < y[axis1]; });
  sort(itmid, itb1, [&](auto x, auto y) { return x[axis1] < y[axis1]; });

  // Enumerate [ib0, imid) x 1 and [imid, ib1) x 2
  {
    int j0 = imid;
    int j1 = imid;
    FOR(i, ib0, imid) {
      // Narrowed down to [y - res_d/2, y + res_d/2]
      double y = ls[i][axis1];
      while (j0 < ib1 && ls[j0][axis1] <  y - res_d / 2 + eps) { j0++; }
      while (j1 < ib1 && ls[j1][axis1] <= y + res_d / 2 + eps) { j1++; }
      // DD(ls);
      // DD(tie(i, j0, j1));

      // Brute force
      FOR(j, j0, j1) {
        auto d1 = point_distance(ls[i], ls[j]);
        if (d1 > res_d / 2 + eps) { continue; }

        FOR(k, j + 1, j1) {
          auto d2 = point_distance(ls[j], ls[k]);
          auto d3 = point_distance(ls[k], ls[i]);
          auto d = d1 + d2 + d3;
          if (d < res_d) {
            res = {i, j, k};
            res_d = d;
          }
        }
      }
    }
  }

  // Enumerate [ib0, imid) x 2 and [imid, ib1) x 1
  {
    int j0 = ib0;
    int j1 = ib0;
    FOR(i, imid, ib1) {
      // Narrowed down to [y - res_d/2, y + res_d/2]
      double y = ls[i][axis1];
      while (j0 < imid && ls[j0][axis1] <  y - res_d / 2 + eps) { j0++; }
      while (j1 < imid && ls[j1][axis1] <= y + res_d / 2 + eps) { j1++; }

      // Brute force
      FOR(j, j0, j1) {
        auto d1 = point_distance(ls[i], ls[j]);
        if (d1 > res_d / 2 + eps) { continue; }

        FOR(k, j + 1, j1) {
          auto d2 = point_distance(ls[j], ls[k]);
          auto d3 = point_distance(ls[k], ls[i]);
          auto d = d1 + d2 + d3;
          if (d < res_d) {
            res = {i, j, k};
            res_d = d;
          }
        }
      }
    }
  }

  return {res, res_d};
}

void mainCase() {
  int n; // n <= 10^5
  cin >> n;

  vector<array<double, 2>> ls(n, {0, 0}); // <= 10^4
  cin >> ls;
  // DD(ls);

  array<int, 3> res;
  double res_d;
  tie(res, res_d) = solveRec(0, n, ls);
  // DD(tie(ls, res, res_d));

  cout << setprecision(std::numeric_limits<double>::max_digits10) << res_d << endl;
}

int main() {
  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  FOR(i, 0, t) { cout << "Case " << (i + 1) << ": "; mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/LRNDSA04/ACM14KP1/main.cpp --check

%%%% begin
2
3
0.0 0.0
1.0 0.0
1.0 1.0
3
0.0 0.0
1.0 0.0
2.0 0.0
%%%%
Case 1: 3.4142135623730949
Case 2: 4
%%%% end

%%%% begin
1
12
1.0 1.0
3.0 1.0
4.0 1.0
6.0 1.0
1.0 3.0
3.0 3.0
4.0 3.0
6.0 3.0
1.0 4.0
3.0 4.0
4.0 4.0
6.0 4.0
1.0 6.0
3.0 6.0
4.0 6.0
6.0 6.0
%%%%
Case 1: 3.4142135623730949
%%%% end

%%%% begin
1
8
1.0 0.0
3.0 0.0
4.0 0.0
6.0 0.0
1.0 1.0
3.0 1.0
4.0 1.0
6.0 1.0
%%%%
Case 1: 3.4142135623730949
%%%% end

%%%% begin
1
6
0.0 0.0
1.0 0.0
2.0 0.0
0.0 1.0
1.0 1.0
2.0 1.0
%%%%
Case 1: 3.4142135623730949
%%%% end

%%%% begin
1
4
0.0 0.0
2.0 2.0
2.0 0.0
1.0 1.0
%%%%
Case 1: 4.8284271247
%%%% end
*/
