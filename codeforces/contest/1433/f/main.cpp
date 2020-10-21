// CONTEST, AC

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

// Main
void mainCase() {
  int n1, n2, m; // [1, 70]
  cin >> n1 >> n2 >> m;
  vector<vector<int>> ls(n1, vector<int>(n2)); // [1, 70]
  cin >> ls;

  const int kInf = 1e9;
  int l = n2 / 2;

  // DP for possible sum
  auto dpForSum = [&](const vector<int>& xs) -> vector<int> {
    int bound = accumulate(ALL(xs), 0);
    vector<array<int, 2>> dp(bound + 1, {0, kInf}); // (ok, count)
    auto dp_prev = dp;
    dp[0] = {1, 0};
    for (auto x : xs) {
      dp_prev = dp;
      FOR(j, 0, bound + 1 - x) {
        auto [ok, c] = dp_prev[j];
        if (!ok) { continue; }
        dp[j + x] = {1, min(dp[j + x][1], c + 1)};
      }
    }
    vector<int> res(m, -1);
    FOR(j, 0, m) {
      for (int x = j; x <= bound; x += m) {
        if (dp[x][0] && dp[x][1] <= l) {
          res[j] = x;
        }
      }
    }
    return res;
  };

  // dp(i, j) = max score for ls[:i] s.t. modulo = j
  vector<int> dp(m, -1);
  auto dp_prev = dp;
  dp[0] = 0;
  FOR(i, 0, n1) {
    dp_prev = dp;
    auto dp_sum = dpForSum(ls[i]);
    FOR(j1, 0, m) {
      if (dp_sum[j1] == -1) { continue; }
      FOR(j2, 0, m) {
        if (dp_prev[j2] == -1) { continue; }
        int j = (j1 + j2) % m;
        dp[j] = max(dp[j], dp_sum[j1] + dp_prev[j2]);
      }
    }
  }

  int res = dp[0];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1433/f/main.cpp

%%%% begin
3 4 3
1 2 3 4
5 2 2 2
7 1 1 4
%%%%
24
%%%% end

%%%% begin
5 5 4
1 2 4 2 1
3 5 1 2 4
1 5 7 1 2
3 8 7 1 2
8 4 7 1 6
%%%%
56
%%%% end
*/
