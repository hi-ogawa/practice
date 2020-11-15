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

using Real = long double;

// Main
void mainCase() {
  int n; // [1, 100]
  cin >> n;
  vector<vector<char>> board(n, vector<char>(n));
  cin >> board;

  // Find reachability via Floyd-Warshall
  const int kInf = 1e8;
  vector<vector<int>> dists(n, vector<int>(n));
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      dists[i][j] = (i == j || board[i][j] == '1') ? 0 : kInf;
    }
  }
  FOR(k, 0, n) {
    FOR(i, 0, n) {
      FOR(j, 0, n) {
        dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);
      }
    }
  }

  // Count inverse reachables
  vector<int> cnts(n);
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      cnts[j] += (dists[i][j] < kInf);
    }
  }
  dbg(cnts);

  Real res = 0;
  FOR(i, 0, n) {
    // Each vertex contributes to an operation by this probability
    res += 1 / Real(cnts[i]);
  }
  dbg(res);

  cout << fixed << setprecision(numeric_limits<Real>::digits10 + 1) << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/agc049/a/main.cpp

%%%% begin
3
010
001
010
%%%%
1.66666666666666666667
%%%% end

%%%% begin
3
000
000
000
%%%%
3.00000000000000000000
%%%% end

%%%% begin
3
011
101
110
%%%%
1.00000000000000000000
%%%% end
*/
