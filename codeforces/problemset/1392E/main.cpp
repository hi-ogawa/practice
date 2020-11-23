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

// Main
void mainCase() {
  int n; // [2, 25]
  cin >> n;

  // Manhattan diagonal trick
  vector<vector<ll>> board(n, vector<ll>(n)); // 2^(2n - 1) ~ 2^49 < 10^16
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      if (i % 2 == 0) {
        board[i][j] = 1LL << (i + j);
      }
    }
  }

  FOR(i, 0, n) {
    FOR(j, 0, n) {
      cout << board[i][j] << " \n"[j == n - 1];
    }
  }
  cout << endl;

  auto solve = [&](ll x) -> vector<array<int, 2>> {
    vector<array<int, 2>> res;
    int row = 0;
    FOR(b, 0, 2 * n - 1) {
      // Go next row if bit is flipped
      if (b > 0 && (((x >> b) ^ (x >> (b - 1))) & 1)) {
        row++;
      }
      res.push_back({row, b - row});
    }
    return res;
  };

  int nq;
  cin >> nq;
  FOR(_, 0, nq) {
    ll x;
    cin >> x;
    auto res = solve(x);
    for (auto [i, j] : res) {
      i++; j++;
      cout << i << " " << j << "\n";
    }
    cout << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
}

/*
python misc/run.py codeforces/problemset/1392E/main.cpp

%%%% begin
4




3
23







26







27
%%%%
1 2 3 6
4 6 2 10
9 0 7 3
2 8 8 2


1 1
1 2
1 3
2 3
2 4
3 4
4 4

1 1
2 1
3 1
3 2
3 3
3 4
4 4

1 1
1 2
1 3
1 4
2 4
3 4
4 4
%%%% end
*/
