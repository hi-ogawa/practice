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

using Real = double;

// Main
void mainCase() {
  int k; // [1, 100]
  cin >> k;

  const int n = 8;

  // Final position probability from (i0, j0)
  auto getFinalPosition = [&](int i0, int j0) -> vector<vector<Real>> {
    vector<vector<Real>> ps(n, vector<Real>(n)), ps_prev, ps_zero;
    ps_zero = ps;
    ps[i0][j0] = 1;
    const array<int, 2> kDirs[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    FOR(_, 0, k) {
      // Simulate directly
      ps_prev = ps;
      ps = ps_zero;
      FOR(i, 0, n) {
        FOR(j, 0, n) {
          int denom = 4;
          if (i == 0 || i == n - 1) { denom--; }
          if (j == 0 || j == n - 1) { denom--; }
          for (auto [di, dj] : kDirs) {
            int ii = i + di, jj = j + dj;
            if (0 <= ii && ii < n && 0 <= jj && jj < n) {
              ps[ii][jj] += ps_prev[i][j] / denom;
            }
          }
        }
      }
    }
    return ps;
  };

  // Probability of square becoming empty
  vector<vector<Real>> qs(n, vector<Real>(n, 1));
  FOR(i0, 0, n) {
    FOR(j0, 0, n) {
      auto ps = getFinalPosition(i0, j0);
      FOR(i, 0, n) {
        FOR(j, 0, n) {
          qs[i][j] *= (1 - ps[i][j]);
        }
      }
    }
  }

  Real res = 0;
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      res += qs[i][j];
    }
  }
  cout << fixed << setprecision(6) << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/mathematics/task1726/main.cpp

%%%% begin
10
%%%%
23.120740
%%%% end
*/
