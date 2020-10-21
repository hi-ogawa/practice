// WIP

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Modulo op
constexpr ll modulo = 998244353;
ll madd(ll x, ll y) { return (x + y) % modulo; }
ll mmul(ll x, ll y) { return (x * y) % modulo; }
ll mexp(ll x, ll e) {
  ll res = 1;
  while (e > 0) {
    if (e & 1) { res = mmul(res, x); }
    x = mmul(x, x); e >>= 1;
  }
  return res;
}
ll minv(ll x) { return mexp(x, modulo - 2); }
ll mdiv(ll x, ll y) { return mmul(x, minv(y)); }

// Diagonal after Gaussian elimination
ll determinant(vector<vector<ll>>& a) {
  int n = a.size();
  ll res = 1;
  FOR(i, 0, n) {
    // Pivot
    int ip = i;
    FOR(ii, i + 1, n) {
      if (abs(a[ii][i]) > abs(a[ip][i])) {
        ip = ii;
      }
    }
    if (i != ip) {
      res *= -1;
      FOR(j, i, n) { swap(a[ip][j], a[i][j]); }
    }

    res = mmul(res, a[i][i]);
    if (res == 0) { break; }

    // Eliminate column by
    //   |  1      |
    //   |    1    |
    //   | -y   x  |
    //   |       1 |
    FOR(ii, i + 1, n) {
      res = mdiv(res, a[i][i]);
      ll x = a[i][i];
      ll y = a[ii][i];
      FOR(j, i, n) {
        a[ii][j] = - y * a[i][j] + x * a[ii][j];
      }
    }
  }
  dbg2(a);
  dbg(res);
  return res;
}

// Main
void mainCase() {
  ll n, m, k; // n <= 30, k <= 10^8
  cin >> n >> m >> k;
  vector<tuple<int, int>> edges(m, {0, 0});
  cin >> edges;

  vector<vector<ll>> lap(n, vector<ll>(n, 0)); // Laplacian
  for (auto [x, y] : edges) {
    x--; y--;
    lap[x][x]++;
    lap[y][y]++;
    lap[x][y]--;
    lap[y][x]--;
  }
  dbg2(lap);

  // Sub matrix in complement big graph
  ll nk = n * k;
  auto A = lap;
  auto A1 = lap; // A - "ones" (1 multiplicity of (n-1) nonzero eigen values)
  auto A2 = lap; // A + "ones" (k multiplicity of n nonzero eigen values)
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      if (i == j) {
        A[i][i] = nk - lap[i][i] - 1;
      } else {
        A[i][j] = (lap[i][j] == -1) ? 0 : -1;
      }
      A1[i][j] = A[i][j] - 1;
      A2[i][j] = A[i][j] + 1;
    }
  }

  vector<vector<ll>> C1(n - 1, vector<ll>(n - 1, 0));
  FOR(i, 0, n - 1) {
    FOR(j, 0, n - 1) {
      C1[i][j] = A1[i][j];
    }
  }
  dbg2(A);
  dbg2(C1);
  dbg2(A2);

  // Kirchhoff's matrix tree theorem
  ll e1 = mmul(n, determinant(C1)); // TODO: is this sketchy?
  ll e2 = determinant(A2);
  ll res = 1;
  res = mmul(res, e1);
  res = mmul(res, mexp(e2, k - 1));
  res = mdiv(res, nk);
  res = madd(res, modulo); // positive
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/problems/CSTREE/main.cpp --check

%%%% begin
1
3 0 1
%%%%
%%%% end

%%%% begin
1
3 3 2
1 2
1 3
2 3
%%%%
%%%% end

%%%% begin
5
3 0 1
3 3 2
1 2
1 3
2 3
3 3 1
1 2
1 3
2 3
6 9 20
1 3
2 3
4 3
5 3
6 3
1 4
2 4
4 5
4 6
30 4 5000
1 2
3 4
5 6
6 7
%%%%
3
81
0
13872131
797280964
%%%% end
*/
