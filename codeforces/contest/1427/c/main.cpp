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
  int r, n_orig; // r \in [1, 500], n \in [1, 10^5]
  cin >> r >> n_orig;
  vector<array<int, 3>> ls_orig(n_orig); // t \in [1, 10^6] (Distance at most "2r")
  cin >> ls_orig;

  // Filter out unreachable
  vector<array<int, 3>> ls;
  for (auto [t, x, y] : ls_orig) {
    if (x - 1 + y - 1 <= t) {
      ls.push_back({t, x, y});
    }
  }
  int n = ls.size();
  if (n == 0) { cout << 0 << "\n"; return; }

  // DP
  vector<int> dp(n), dp_cm(n); /// cum max
  FOR(i, 0, n) {
    auto [t, x, y] = ls[i];

    array<int, 3> query = {t - 2 * r, 0, 0};
    auto it = lower_bound(ALL(ls), query, [](auto lhs, auto rhs) { return lhs[0] < rhs[0]; });
    int i0 = distance(ls.begin(), it);

    int s = 1;
    if (i0 > 0) { s = dp_cm[i0 - 1] + 1; }

    // Brute force at most "2r"
    FOR(j, i0, i) {
      auto [tj, xj, yj] = ls[j];
      if (abs(x - xj) + abs(y - yj) <= t - tj) {
        s = max(s, dp[j] + 1);
      }
    }

    dp[i] = s;
    dp_cm[i] = max(i ? dp_cm[i - 1] : 0, dp[i]);
  }

  int res = dp_cm[n - 1];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest-global-round-11/c/main.cpp

%%%% begin
10 1
11 6 8
%%%%
0
%%%% end

%%%% begin
6 9
1 2 6
7 5 1
8 5 5
10 3 1
12 4 4
13 6 2
17 6 6
20 1 4
21 5 4
%%%%
4
%%%% end

%%%% begin
10 4
1 2 1
5 10 9
13 8 8
15 9 9
%%%%
1
%%%% end

%%%% begin
500 10
69 477 122
73 186 235
341 101 145
372 77 497
390 117 440
494 471 37
522 300 498
682 149 379
821 486 359
855 157 386
%%%%
3
%%%% end
*/
