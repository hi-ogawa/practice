// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
  int n, m; // n x m \in [1, 2 x 10^5]
  cin >> n >> m;
  vector<vector<int>> ls(n, vector<int>(m));
  cin >> ls;

  // "Cyclic distance" for j-th column
  auto solve = [&](int j) -> int {
    // target is [r, m + r, 2m + r, ..., (n-1)m + r]
    int r = j + 1;
    map<int, int> cnts; // cnts[rotation] = #{ i | ls[i][j] matches target after rotation }
    FOR(i, 0, n) {
      int x = ls[i][j] - r;
      if (0 <= x && x < m * n && x % m == 0) {
        cnts[(i - x / m + n) % n]++;
      }
    }
    dbg(j, r, cnts);
    int res = n;
    for (auto [k, v] : cnts) {
      res = min(res, k + (n - v));
    }
    return res;
  };

  // Sum "distance" for each column
  int res = 0;
  FOR(j, 0, m) { res += solve(j); }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1294E/main.cpp --check

%%%% begin
3 3
3 2 1
1 2 3
4 5 6
%%%%
6
%%%% end

%%%% begin
4 3
1 2 3
4 5 6
7 8 9
10 11 12
%%%%
0
%%%% end

%%%% begin
3 4
1 6 3 4
5 10 7 8
9 2 11 12
%%%%
2
%%%% end
*/
