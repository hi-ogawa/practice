// AC

// TODO: how to go without 128 bit integer?

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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

// 128 bit integer
using lll = __int128;

namespace std {
ostream& operator<<(ostream& ostr, __int128 x) {
  if (x == 0) { return ostr << 0; }
  bool neg = x < 0;
  if (neg) { x = -x; }
  string res;
  while (x > 0) {
    res += (x % 10) + '0';
    x /= 10;
  }
  reverse(ALL(res));
  return ostr << (neg ? "-" : "") << res;
}
}

// Main
void mainCase() {
  int n; // [1, 100]
  cin >> n;
  ll k; // [1, 10^12]
  cin >> k;
  string s; // lower case
  cin >> s;

  // Count subsequence (128 bit integer for handling up to 2^100)
  const int m = 1 << 8;
  vector<vector<lll>> cnts(m, vector<lll>(n + 1));
  vector<lll> dp(n + 1), dp_prev;
  dp[0] = 1;
  FOR(i, 0, n) {
    dp_prev = dp;
    auto x = s[i];
    FOR(j, 0, n) {
      dp[j + 1] = dp_prev[j] + dp_prev[j + 1] - cnts[x][j + 1];
      cnts[x][j + 1] = dp_prev[j];
    }
  }
  dbg(dp);

  bool ok = accumulate(ALL(dp), (lll)0) >= k;
  if (!ok) { cout << -1 << "\n"; return; }

  // Maximize sum of lengths
  ll res = 0;
  ll kk = k;
  for (int j = n; j >= 0; j--) {
    if (kk == 0) { break; }
    if (dp[j] > kk) {
      res += kk * j;
      break;
    }
    res += min((ll)dp[j], kk) * j;
    kk -= min((ll)dp[j], kk);
  }

  ll res2 = k * n - res;
  cout << res2 << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1183H/main.cpp

%%%% begin
4 5
asdf
%%%%
4
%%%% end

%%%% begin
5 6
aaaaa
%%%%
15
%%%% end

%%%% begin
5 7
aaaaa
%%%%
-1
%%%% end

%%%% begin
10 100
ajihiushda
%%%%
233
%%%% end
*/
