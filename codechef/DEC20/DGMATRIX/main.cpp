// WIP

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

using V = vector<int>;
using V2 = vector<vector<int>>;

// Main
void mainCase() {
  int n; // [1, 100]
  cin >> n;
  V2 y(n, V(n)); // [0, 9 * 4]
  cin >> y;
  dbg2(y);

  // y = Ax = A1 x1 + A2 x2
  // x1 = A1^(-1) (y - A2 x2)

  int m = n + 1;
  int k = 2 * n + 1; // m2 - n2

  V2 res(m, V(m));

  auto evaluate = [&](const V& v) -> int {
    // Copy boundary
    auto& x = res;
    FOR(i, 0, n) {
      x[i][n] = v[i];
      x[n][i] = v[i + n];
    }
    x[n][n] = v[2 * n];

    // Unique solution given boundary
    int comp = 0;
    for (int i = n - 1; i >= 0; i--) {
      for (int j = n - 1; j >= 0; j--) {
        int t = y[i][j] - x[i + 1][j] - x[i][j + 1] - x[i + 1][j + 1];
        if (t < 0) { comp = -1; break; }
        if (t > 10) { comp = 1; break; }
        x[i][j] = t;
      }
    }
    dbg(v, comp);
    dbg2(x);
    return comp;
  };

  auto add = [&](const V& x, const V& y, V& z) {
    int c = 0;
    FOR(i, 0, k + 1) {
      z[i] = x[i] + y[i] + c;
      c = z[i] / 10;
      z[i] %= 10;
    }
  };

  auto div2 = [&](V& x) {
    int c = 0;
    for (int i = k; i >= 0; i--) {
      x[i] += c * 10;
      c = x[i] % 2;
      x[i] /= 2;
    }
  };

  auto getMidpoint = [&](const V& x, const V& y, V& z) {
    add(x, y, z);
    div2(z);
  };

  // Binary search x2 ∈ [0, 9]^(2n+1) such that x1 ∈ [0, 9]^(n^2)
  auto search = [&]() {
    V xl(k + 1); // (0, 0, ..., 0)
    V xr(k + 1); // (1, 0, ..., 0)
    xr[k] = 1;
    V x(k + 1);
    FOR(_, 0, 10) {
      getMidpoint(xl, xr, x);
      dbg(xl, xr, x);
      int comp = evaluate(x);
      if (comp == 0) { break; }
      if (comp == +1) { xl = x; xl[0]++; }
      if (comp == -1) { xr = x; }
    }
  };

  search();
  dbg(res);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/DEC20/DGMATRIX/main.cpp

%%%% begin
2
12 16
24 28
%%%%
123
456
789
%%%% end
*/
