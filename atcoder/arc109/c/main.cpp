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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, k; // [1, 100]
  cin >> n >> k;
  string s; // R, P, S, length = n
  cin >> s;

  auto getWinner = [](char l, char r) -> char {
    if (l == r) { return l; }
    if (l == 'R') {
      if (r == 'P') { return 'P'; }
      if (r == 'S') { return 'R'; }
    }
    if (l == 'P') {
      if (r == 'R') { return 'P'; }
      if (r == 'S') { return 'S'; }
    }
    if (l == 'S') {
      if (r == 'R') { return 'R'; }
      if (r == 'P') { return 'S'; }
    }
    assert(0);
  };

  vector<vector<char>> dp(k + 1, vector<char>(n));
  dp[0] = {ALL(s)};

  auto pow = [](int x, int e, int m) -> int {
    int y = 1;
    while (e > 0) {
      if (e & 1) { y = (y * x) % m; }
      e >>= 1; x = (x * x) % m;
    }
    return y;
  };

  FOR(i, 0, k) {
    int diff = pow(2, i, n);
    FOR(j, 0, n) {
      dp[i + 1][j] = getWinner(dp[i][j], dp[i][(j + diff) % n]);
    }
  }

  auto res = dp[k][0];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/arc109/c/main.cpp

%%%% begin
3 2
RPS
%%%%
P
%%%% end

%%%% begin
11 1
RPSSPRSPPRS
%%%%
P
%%%% end

%%%% begin
1 100
S
%%%%
S
%%%% end
*/
