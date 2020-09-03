// AC

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

// Main
void mainCase() {
  ll n; // <= 2000
  cin >> n;
  vector<vector<ll>> board(n, vector<ll>(n));
  cin >> board;

  // Points for all diagonals
  vector<ll> ls1(n), ls2(n), ls3(n), ls4(n);
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      if (i + j < n)  { ls1[i] += board[i + j][j]; }
      if (i + j < n)  { ls2[i] += board[j][i + j]; }
      if (i - j >= 0) { ls3[i] += board[i - j][j]; }
      if (i - j + n - 1 < n) { ls4[i] += board[i - j + n - 1][j]; }
    }
  }
  dbg(ls1);
  dbg(ls2);
  dbg(ls3);
  dbg(ls4);

  // Optimize for each parity
  ll res1 = 0, res2 = 0;
  array<int, 2> res3 = {0, 0}, res4 = {1, 0};
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      ll p = i >= j ? ls1[i - j] : ls2[j - i];
      ll q = i + j < n ? ls3[i + j] : ls4[i + j - (n - 1)];
      ll tmp = p + q - board[i][j];
      if ((i + j) % 2 == 0) {
        if (tmp > res1) {
          res1 = tmp;
          res3 = {i, j};
        }
      } else {
        if (tmp > res2) {
          res2 = tmp;
          res4 = {i, j};
        }
      }
    }
  }
  dbgv(res1, res2, res3, res4);

  cout << (res1 + res2) << endl;
  cout << (res3[0] + 1) << " " << (res3[1] + 1) << " ";
  cout << (res4[0] + 1) << " " << (res4[1] + 1) << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py codeforces/problemset/463D/main.cpp --check

%%%% begin
2
0 0
0 0
%%%%
0
1 1 2 1
%%%% end

%%%% begin
4
1 1 1 1
2 1 1 0
1 1 1 0
1 0 0 1
%%%%
12
2 2 3 2
%%%% end
*/
