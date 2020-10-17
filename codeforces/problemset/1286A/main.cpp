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
  int n; // [1, 100]
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  if (n == 1) {
    cout << 0 << "\n";
    return;
  }

  // All unknown
  if (count(ALL(ls), 0) == n) {
    cout << 1 << "\n";
    return;
  }

  // Count Remaining even/odd
  array<int, 2> cnts = {n / 2, (n + 1) / 2};
  FOR(i, 0, n) {
    // Set -1, 0, 1 for simplicity later
    if (ls[i] == 0) { ls[i] = -1; continue; }
    ls[i] = ls[i] % 2;
    cnts[ls[i]]--;
  }
  dbg(ls, cnts);

  // Initial cost
  int res1 = 0;
  FOR(i, 0, n - 1) {
    if (ls[i] == 0 && ls[i + 1] == 1) { res1++; }
    if (ls[i] == 1 && ls[i + 1] == 0) { res1++; }
  }

  //
  // Unknown segments of each types with optimal cost
  //   E(...)E  => 0 or 2
  //   E(...)O  => 1
  //   O(...)E  => 1
  //   O(...)O  => 0 or 2
  //   E(...)   => 0 or 1
  //   O(...)   => 0 or 1
  //    (...)E  => 0 or 1
  //    (...)O  => 0 or 1
  //
  // So, we only need to optimize "0 or 2" and "0 or 1"
  //

  // Find consecutive segments
  vector<array<int, 2>> segs;
  FOR(i, 0, n) {
    if (i == 0 || ls[i] != ls[i - 1]) { segs.push_back({i, -1}); }
    segs.back()[1] = i + 1;
  }

  // Rest of the costs
  int res2 = 0;
  array<vector<int>, 2> segs1, segs2;

  for (auto [l, r] : segs) {
    if (ls[l] >= 0) { continue; }
    if (l == 0) {
      res2 += 1;
      segs1[ls[r]].push_back(r - l);
      continue;
    }
    if (r == n) {
      res2 += 1;
      segs1[ls[l - 1]].push_back(r - l);
      continue;
    }
    if (ls[l - 1] == ls[r]) {
      res2 += 2;
      segs2[ls[l - 1]].push_back(r - l);
      continue;
    }
    // ls[l - 1] != ls[r]
    res2 += 1;
  }

  // DP for optimization (1 -> 0 or 2 -> 0)
  // NOTE: didn't need dp since always ls1.size() = 0 or 1 ...
  auto runDP = [&](const vector<int>& ls1, const vector<int>& ls2, int c) {
    vector<int> dp(c + 1, -1);
    dp[0] = 0;
    FOR(i, 0, (int)ls1.size()) {
      int x = ls1[i];
      for (int j = c - x; j >= 0; j--) {
        if (dp[j] == -1) { continue; }
        dp[j + x] = max(dp[j + x], dp[j] + 1);
      }
    }
    FOR(i, 0, (int)ls2.size()) {
      int x = ls2[i];
      for (int j = c - x; j >= 0; j--) {
        if (dp[j] == -1) { continue; }
        dp[j + x] = max(dp[j + x], dp[j] + 2);
      }
    }
    int res = 0;
    FOR(j, 0, c + 1) { res = max(res, dp[j]); }
    dbg(ls1, ls2, c, res);
    return res;
  };

  int dp1 = runDP(segs1[0], segs2[0], cnts[0]);
  int dp2 = runDP(segs1[1], segs2[1], cnts[1]);
  res2 -= dp1;
  res2 -= dp2;
  dbg(res1, res2, dp1, dp2);

  int res = res1 + res2;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1286A/main.cpp

%%%% begin
20
7 0 9 0 5 0 15 0 0 1 17 0 11 19 0 0 3 0 13 0
%%%%
15
%%%% end

%%%% begin
5
0 5 0 2 3
%%%%
2
%%%% end

%%%% begin
7
1 0 0 5 0 0 2
%%%%
1
%%%% end
*/
