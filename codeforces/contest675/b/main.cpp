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
  int n, m; // [1, 100]
  cin >> n >> m;
  vector<vector<int>> ls(n, vector<int>(m)); // [0, 10^9]
  cin >> ls;

  // Take median of each mirroring posision
  ll res = 0;
  FOR(i, 0, n / 2) {
    FOR(j, 0, m / 2) {
      int ii = n - 1 - i, jj = m - 1 - j;
      array<int, 4> xs = {ls[i][j], ls[i][jj], ls[ii][j], ls[ii][jj]};
      sort(ALL(xs));
      res += abs(xs[0] - xs[1]);
      res += abs(xs[2] - xs[1]);
      res += abs(xs[3] - xs[1]);
    }
  }

  // Handle odd parts
  if (n % 2 == 1) {
    int i = n / 2;
    FOR(j, 0, m / 2) {
      res += abs(ls[i][j] - ls[i][m - 1 - j]);
    }
  }

  if (m % 2 == 1) {
    int j = m / 2;
    FOR(i, 0, n / 2) {
      res += abs(ls[i][j] - ls[n - 1 - i][j]);
    }
  }

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest675/b/main.cpp --check

%%%% begin
2
4 2
4 2
2 4
4 2
2 4
3 4
1 2 3 4
5 6 7 8
9 10 11 18
%%%%
8
42
%%%% end
*/
