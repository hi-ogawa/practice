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
  int n, m; // [2, 100]
  cin >> n >> m;
  vector<vector<int>> ls(n, vector<int>(m));
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      char x;
      cin >> x;
      ls[i][j] = x - '0';
    }
  }

  vector<array<int, 6>> res;

  auto update = [&](const array<int, 6>& diff) {
    ls[diff[0]][diff[1]] ^= 1;
    ls[diff[2]][diff[3]] ^= 1;
    ls[diff[4]][diff[5]] ^= 1;
    res.push_back(diff);
  };

  #define P0 i + 0, j + 0
  #define P1 i + 0, j + 1
  #define P2 i + 1, j + 0
  #define P3 i + 1, j + 1

  // Solve four
  auto solve4 = [&](int i, int j) {
    int x0 = ls[i + 0][j + 0];
    int x1 = ls[i + 0][j + 1];
    int x2 = ls[i + 1][j + 0];
    int x3 = ls[i + 1][j + 1];
    int s = x0 + x1 + x2 + x3;
    if (s == 0) { return; }
    if (s == 4) {
      update({P0, P1, P2});
      update({P1, P2, P3});
      update({P2, P3, P0});
      update({P3, P0, P1});
      return;
    }
    if (s == 1) {
      if (x0) {
        update({P0, P1, P2});
        update({P0, P2, P3});
        update({P0, P3, P1});
      }
      if (x1) {
        update({P1, P2, P3});
        update({P1, P3, P0});
        update({P1, P0, P2});
      }
      if (x2) {
        update({P2, P3, P0});
        update({P2, P0, P1});
        update({P2, P1, P3});
      }
      if (x3) {
        update({P3, P0, P1});
        update({P3, P1, P2});
        update({P3, P2, P0});
      }
    }
    if (s == 3) {
      if (!x0) { update({P1, P2, P3}); }
      if (!x1) { update({P2, P3, P0}); }
      if (!x2) { update({P3, P0, P1}); }
      if (!x3) { update({P0, P1, P2}); }
    }
    if (s == 2) {
      if (x0) {
        if (x1) {
          update({P0, P2, P3});
          update({P1, P2, P3});
        }
        if (x2) {
          update({P0, P1, P3});
          update({P2, P1, P3});
        }
        if (x3) {
          update({P0, P1, P2});
          update({P3, P1, P2});
        }
        return;
      }
      if (x1) {
        if (x2) {
          update({P1, P0, P3});
          update({P2, P0, P3});
        }
        if (x3) {
          update({P1, P0, P2});
          update({P3, P0, P2});
        }
        return;
      }
      if (x2) {
        if (x3) {
          update({P2, P0, P1});
          update({P3, P0, P1});
        }
        return;
      }
    }
  };

  FOR(i, 0, n - 1) {
    FOR(j, 0, m - 1) {
      // Fix four
      if (i == n - 2 && j == m - 2) {
        solve4(i, j);
        continue;
      }
      // Fix two
      if (i == n - 2) {
        if (ls[i][j] && ls[i + 1][j]) {
          update({i, j, i + 1, j, i + 1, j + 1});
          continue;
        }
        if (ls[i][j]) {
          update({i, j, i, j + 1, i + 1, j + 1});
          continue;
        }
        if (ls[i + 1][j]) {
          update({i + 1, j, i, j + 1, i + 1, j + 1});
          continue;
        }
        continue;
      }
      // Fix two
      if (j == m - 2) {
        if (ls[i][j] && ls[i][j + 1]) {
          update({i, j, i + 1, j, i, j + 1});
          continue;
        }
        if (ls[i][j]) {
          update({i, j, i + 1, j, i + 1, j + 1});
          continue;
        }
        if (ls[i][j + 1]) {
          update({i + 1, j, i, j + 1, i + 1, j + 1});
          continue;
        }
        continue;
      }
      // Fix one
      if (ls[i][j]) {
        update({i, j, i + 1, j, i, j + 1});
      }
    }
  }
  dbg2(ls);
  dbg(res);

  int k = res.size();
  assert(k <= n * m);
  cout << k << "\n";
  FOR(i, 0, k) {
    FOR(j, 0, 6) {
      cout << (res[i][j] + 1) << " \n"[j == 5];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1440/c/main.cpp

%%%% begin
5
2 2
10
11
3 3
011
101
110
4 4
1111
0110
0110
1111
5 5
01011
11001
00010
11011
10000
2 3
011
101
%%%%
1
1 1 2 1 2 2
2
2 1 3 1 3 2
1 2 1 3 2 3
4
1 1 1 2 2 2
1 3 1 4 2 3
3 2 4 1 4 2
3 3 4 3 4 4
4
1 2 2 1 2 2
1 4 1 5 2 5
4 1 4 2 5 1
4 4 4 5 3 4
2
1 3 2 2 2 3
1 2 2 1 2 2
%%%% end
*/
