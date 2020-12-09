// WA

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

// Main
void mainCase() {
  int n; // [1, 300]
  cin >> n;
  vector<vector<char>> ls(n, vector<char>(n));
  cin >> ls;

  //
  // PROP. there are at least three when we flip one.
  //
  //      x         x
  //      x  =>     x
  //  ? ? x     ? ? o
  //
  //      ?         ?
  //      ?  =>     ?
  //  x x x     x x o
  //
  // NOTE: but this doesn't imply k/3 operation... (see 1st test case)
  //
  if (n >= 3) {
    FOR(i, 0, n) {
      FOR(j, 0, n) {
        int c = ls[i][j];
        if (c != 'X') { continue; }
        bool t1 = (j >= 2) && (c == ls[i][j - 1]) && (c == ls[i][j - 2]);
        bool t2 = (i >= 2) && (c == ls[i - 1][j]) && (c == ls[i - 2][j]);
        if (t1 || t2) { ls[i][j] = 'O'; }
      }
    }
  }

  FOR(i, 0, n) {
    FOR(j, 0, n) {
      cout << ls[i][j];
    }
    cout << "\n";
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
python misc/run.py codeforces/problemset/1450C1/main.cpp

%%%% begin
3
3
.X.
XXX
.X.
6
XX.XXX
XXXXXX
XXX.XX
XXXXXX
XX.X.X
XXXXXX
5
XXX.X
.X..X
XXX.X
..X..
..X..
%%%%
.X.
XOX
.X.
XX.XXO
XOXXOX
OXX.XX
XOOXXO
XX.X.X
OXXOXX
XOX.X
.X..X
XXO.O
..X..
..X..
%%%% end
*/
