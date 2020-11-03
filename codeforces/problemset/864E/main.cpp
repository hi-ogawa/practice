// AC

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
  int n; // [1, 100]
  cin >> n;
  vector<array<int, 3>> ls(n); // [1, 10], [1, 2000], [1, 20]
  cin >> ls;

  //
  // PROP.
  //   There exists optimal path taking the increasing order of "d" (i.e. subsequence of such order)
  //

  // Need to save order for the answer
  vector<int> order(n);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return ls[x][1] < ls[y][1]; });

  // Sort by "d"
  sort(ALL(ls), [](auto x, auto y) { return x[1] < y[1]; });

  int t_lim = 0;
  for (auto [t, d, p] : ls) {
    t_lim += t;
  }

  // dp(i, t) = max gain at time t considering vertices {1, .., i}
  vector<vector<int>> dp(n + 1, vector<int>(t_lim + 1)); // for backtracking later, we use 2 dimentions
  FOR(i, 0, n) {
    auto [t, d, p] = ls[i];
    FOR(j, 0, t_lim + 1) {
      int s = dp[i][j];
      if (j > 0) {
        s = max(s, dp[i + 1][j - 1]);
      }
      if (t <= j && j < d) {
        s = max(s, dp[i][j - t] + p);
      }
      dp[i + 1][j] = s;
    }
  }
  dbg2(dp);

  // Backtrack to restore optimal path
  int st_j = t_lim;
  int st_gain = dp[n][st_j];
  int res1 = st_gain;
  vector<int> res2;

  for (int i = n - 1; i >= 0; i--) {
    dbg(i, st_j, st_gain);
    if (dp[i][st_j] == st_gain) {
      continue;
    }
    while (st_j > 0 && dp[i + 1][st_j - 1] == st_gain) {
      st_j--;
    }
    auto [t, d, p] = ls[i];
    assert(st_gain == dp[i][st_j - t] + p);
    st_gain -= p;
    st_j -= t;
    res2.push_back(i);
  }
  dbg(res2);

  reverse(ALL(res2));
  for (auto& x : res2) {
    x = order[x];
  }

  cout << res1 << "\n";
  int k = res2.size();
  cout << k << "\n";
  FOR(i, 0, k) {
    cout << (res2[i] + 1) << " \n"[i == k - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/864E/main.cpp

%%%% begin
3
3 7 4
2 6 5
3 7 6
%%%%
11
2
2 3
%%%% end

%%%% begin
2
5 6 1
3 3 5
%%%%
1
1
1
%%%% end
*/
