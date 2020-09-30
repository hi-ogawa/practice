// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = begin(x); it != end(x); it++) { if (it != begin(x)) { o << ", "; } o << *it; } o << "}"; return o; }
}

#ifdef DEBUG
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

template<class T> using V = vector<T>;
template<class T> using VV = V<V<T>>;
template<class T> using VVV = V<V<V<T>>>;

// Main
void mainCase() {
  int n; // [1, 500]
  cin >> n;
  string s;
  cin >> s;

  int k = 26; // a..z
  // k = 5; // debug
  vector<int> ls(n);
  FOR(i, 0, n) { ls[i] = s[i] - 'a'; }
  dbg(ls);

  // dp(i, j, t) = min cost to clear "s[i:j]" with last pick character "t"
  int kInf = 1e3;
  // kInf = 10; // debug
  VVV<int> dp(n, VV<int>(n + 1, V<int>(k, kInf)));

  FOR(i, 0, n) {
    dp[i][i + 1][ls[i]] = 1;
  }

  FOR(l, 2, n + 1) {
    FOR(i, 0, n - l + 1) {
      int j = i + l;
      FOR(p, i, j) {
        int t = ls[p];
        int c = 1;
        if (i < p) {
          c += min(dp[i][p][t] - 1, *min_element(ALL(dp[i][p])));
        }
        if (p + 1 < j) {
          c += min(dp[p + 1][j][t] - 1, *min_element(ALL(dp[p + 1][j])));
        }
        dp[i][j][t] = min(dp[i][j][t], c);
      }
    }
  }
  dbg2(dp);

  int res = *min_element(ALL(dp[0][n]));
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1132F/main_v2.cpp --check

%%%% begin
4
abba
%%%%
2
%%%% end

%%%% begin
5
abaca
%%%%
3
%%%% end

%%%% begin
8
abcddcba
%%%%
4
%%%% end
*/
