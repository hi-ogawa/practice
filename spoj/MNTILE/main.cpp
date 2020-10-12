// WIP

// TODO: This clearly exceeds "source limit 300B"

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
  int n, m; // n + m \in [0, 22]
  cin >> n >> m;

  // WLOG n <= m (thus n <= 11)
  if (n > m) { swap(n, m); }
  if (n == 0) { cout << 0 << "\n"; return; }

  int n_mask = (1 << n) - 1;

  // Check nth bit
  auto nth = [](int s, int n) -> bool { return (s >> n) & 1; };

  // Valid 2x1 block patterns in single column
  vector<int> patterns;
  FOR(s, 0, 1 << n) {
    vector<array<int, 2>> segs;
    FOR(i, 0, n) {
      if (i == 0 || nth(s, i) != nth(s, i - 1)) {
        segs.push_back({i, -1});
      }
      segs.back()[1] = i + 1;
    }
    bool ok = 1;
    for (auto [l, r] : segs) {
      if (nth(s, l) && ((r - l) % 2 == 1)) {
        ok = 0; break;
      }
    }
    if (ok) { patterns.push_back(s); }
  }

  // Debug
  vector<bitset<8>> patterns_debug(ALL(patterns));
  dbg2(patterns_debug);

  // DP
  vector<ll> dp(1 << n);
  auto dp_prev = dp;

  // First column by 2x1 blocks
  for (auto s : patterns) { dp[s] = 1; }

  FOR(i, 0, m - 1) {
    // Extend to next column by 1x2 blocks
    dp_prev = dp;
    FOR(s, 0, 1 << n) {
      dp[n_mask & ~s] = dp_prev[s]; // negation
    }

    // Fill this column by 2x1 blocks
    dp_prev = dp;
    FOR(s, 0, 1 << n) {
      for (auto sp : patterns) {
        if (sp == 0) { continue; }
        if ((s & sp) == 0) { // disjoint
          dp[s | sp] += dp_prev[s];
        }
      }
    }
  }

  ll res = dp[(1 << n) - 1];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 276]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py spoj/MNTILE/main.cpp

%%%% begin
1
8 8
%%%%
12988816
%%%% end

%%%% begin
6
1 2
2 3
3 4
4 5
5 6
6 7
%%%%
1
3
11
95
1183
31529
%%%% end
*/
