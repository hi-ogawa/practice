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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

const int kInf = 1e9;

// Bellman-Ford algorithm
tuple<bool, vector<int>> solveBellmanFord(vector<vector<int>>& adj, int root) {
  int n = adj.size();

  vector<int> dists(n, kInf);
  dists[root] = 0;

  bool neg_cycle = 0;
  FOR(k, 0, n) {
    FOR(i, 0, n) {
      FOR(j, 0, n) {
        int d = dists[i] + adj[i][j];
        if (d < dists[j]) {
          dists[j] = d;
          if (k == n - 1) { neg_cycle = 1; }
        }
      }
    }
  }

  return {neg_cycle, move(dists)};
}

// Main
void mainCase() {
  int n; // [1, 100]
  cin >> n;
  vector<vector<int>> ls(n, vector<int>(n)); // [0, 9 * 4], solvable
  cin >> ls;

  // First solve fixed scalar part
  vector<vector<int>> s = ls;
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      if (i > 0) { s[i][j] -= s[i - 1][j]; }
      if (j > 0) { s[i][j] -= s[i][j - 1]; }
      if (i > 0 && j > 0) { s[i][j] -= s[i - 1][j - 1]; }
    }
  }
  dbg2(s);

  //
  // Brute force a = 1 .. 9
  //
  //  a  c1 c2 ...
  //  r1
  //  r2
  /// ..
  //
  //
  // Rewrite variables by
  //   x(i)    = ± ri (minus if i odd)
  //   x(i+n)  = ± ci (minus if i even)
  //
  // Inequality constriaints (r1, .., c1, ..) become e.g.
  //
  //   0 ≤ x(i) ≤ 9
  //   0 ≤ s(i, j) - x(i) + x(j + n) ≤ 9
  //   ...
  //

  int nv = 2 * n + 1;
  int root = 2 * n;
  vector<vector<int>> adj(nv, vector<int>(nv, kInf));
  vector<vector<int>> t = s;

  auto defineConstraints = [&](int a) {
    // Update scalar part
    FOR(i, 0, n) {
      FOR(j, 0, n) {
        t[i][j] = s[i][j] + (((i + j) % 2) ? 1 : -1) * a;
      }
    }

    // Define inequality constraint
    FOR(i, 0, n) {
      // 0 ≤ x ≤ 9  <=> x - 0 ≤ 9
      //                0 - x ≤ 0
      // -9 ≤ x ≤ 0  <=> x - 0 ≤ 0
      //                 0 - x ≤ 9
      if (i % 2) {
        adj[root][i] = 0;
        adj[i][root] = 9;
        adj[root][i + n] = 9;
        adj[i + n][root] = 0;
      } else {
        adj[root][i] = 9;
        adj[i][root] = 0;
        adj[root][i + n] = 0;
        adj[i + n][root] = 9;
      }
      FOR(j, 0, n) {
        if ((i + j) % 2) {
          // 0 ≤ s(i, j) + x(i) - x(j+n) ≤ 9
          // <=>
          //   x(i) - x(j+n) ≤ 9 - s(i, j)
          //   x(j+n) - x(i) ≤ s(i, j)
          adj[j + n][i] = 9 - t[i][j];
          adj[i][j + n] = t[i][j];
        } else {
          // 0 ≤ s(i, j) - x(i) + x(j+n) ≤ 9
          // <=>
          //   x(j+n) - x(i) ≤ 9 - s(i, j)
          //   x(i) - x(j+n) ≤ s(i, j)
          adj[i][j + n] = 9 - t[i][j];
          adj[j + n][i] = t[i][j];
        }
      }
    }
  };

  // Brute force the value of the left-top corner
  int res_a = -1;
  vector<int> dists;
  FOR(a, 0, 10) {
    defineConstraints(a);
    bool neg_cycle = 0;
    tie(neg_cycle, dists) = solveBellmanFord(adj, root);
    if (!neg_cycle) { res_a = a; break; }
  }
  dbg(res_a);
  dbg(dists);
  assert(res_a != -1);

  vector<vector<int>> res(n + 1, vector<int>(n + 1));
  res[0][0] = res_a;
  FOR(i, 0, n) {
    res[i + 1][0] = dists[i]     * ((i % 2) ? -1 : 1);
    res[0][i + 1] = dists[i + n] * ((i % 2) ? 1 : -1);
  }
  FOR(i, 1, n + 1) {
    FOR(j, 1, n + 1) {
      res[i][j] = ls[i - 1][j - 1] - res[i - 1][j - 1] - res[i][j - 1] - res[i - 1][j];
    }
  }

  FOR(i, 0, n + 1) {
    FOR(j, 0, n + 1) {
      cout << res[i][j];
    }
    cout << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/DEC20/DGMATRIX/main_v2.cpp

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
