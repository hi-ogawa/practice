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

array<ll, 3> solve(vector<vector<int>>& ls) {
  const array<array<int, 3>, 3> mex = {{
    {{1, 2, 1}},
    {{2, 0, 0}},
    {{1, 0, 0}}}};

  int n = ls.size(), m = ls[0].size();
  array<ll, 3> res = {};
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      if (i && j) {
        int x = ls[i - 1][j];
        int y = ls[i][j - 1];
        ls[i][j] = mex[x][y];
      }
      res[ls[i][j]]++;
    }
  }
  return res;
}

// Main
void mainCase() {
  int n; // [1, 5 x 10^5]
  cin >> n;

  // Brute-force all
  if (n <= 4) {
    vector<vector<int>> ls(n, vector<int>(n));
    cin >> ls[0][0];
    FOR(i, 1, n) {
      cin >> ls[0][i];
    }
    FOR(i, 1, n) {
      cin >> ls[i][0];
    }
    auto res = solve(ls);
    cout << res[0] << " " << res[1] << " " << res[2] << "\n";
    return;
  }

  // Brute-force only 4 x n and n x 4 blocks
  const int k = 4;
  vector<vector<int>> ls1(k, vector<int>(n));
  vector<vector<int>> ls2(n, vector<int>(k));

  cin >> ls1[0][0];
  FOR(j, 1, n) {
    cin >> ls1[0][j];
  }
  FOR(i, 1, n) {
    cin >> ls2[i][0];
  }
  FOR(i, 0, k) {
    ls2[0][i] = ls1[0][i];
    ls1[i][0] = ls2[i][0];
  }

  auto res1 = solve(ls1);
  auto res2 = solve(ls2);
  dbg2(ls1);
  dbg2(ls2);
  dbg(res1, res2);

  // Count duplicate diagonals
  array<ll, 3> res = {};
  res[ls1[3][3]] += n - k;
  FOR(j, k, n) {
    res[ls1[3][j]] += n - j - 1;
  }
  FOR(i, k, n) {
    res[ls2[i][3]] += n - i - 1;
  }

  FOR(i, 0, 3) {
    res[i] += res1[i];
    res[i] += res2[i];
  }
  FOR(i, 0, k) {
    FOR(j, 0, k) {
      res[ls1[i][j]]--;
    }
  }

  cout << res[0] << " " << res[1] << " " << res[2] << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/arc107/e/main.cpp

%%%% begin
8
0 1 2 1 2 2 2 0
0
0
2
1
0
0
2
%%%%
26 21 17
%%%% end

%%%% begin
4
1 2 0 2
0
0
0
%%%%
7 4 5
%%%% end
*/
