// CONTEST, WA

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
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<array<int, 2>> ls(n); // [1, 10^9], increasing
  FOR(i, 0, 2) {
    FOR(j, 0, n) {
      cin >> ls[j][i];
    }
  }
  dbg(ls);

  const int kInf = 1e9 + 1;

  // Find safely destroyed intervals
  vector<array<int, 2>> segs, _segs;
  for (auto [a, b] : ls) {
    if (b < a) {
      _segs.push_back({a - b, a});
    }
  }
  sort(ALL(_segs));
  dbg(_segs);
  for (auto [x0, x1] : _segs) {
    if (segs.empty() || segs.back()[1] + 1 < x0) {
      segs.push_back({x0, -1});
    }
    auto& x2 = segs.back()[1];
    x2 = max(x2, x1);
  }
  dbg(segs);

  // Costs to make robot destroyed
  vector<int> cs(n);
  FOR(i, 0, n) {
    auto [a, b] = ls[i];
    // Check if inside of "safely destroyed" interval
    array<int, 2> q = {a, kInf};
    auto it = upper_bound(ALL(segs), q);
    if (it != segs.begin()) {
      auto [x0, x1] = *prev(it);
      if (x0 <= a && a <= x1) {
        continue;
      }
    }
    // Can be destroyed by moving one ball up
    cs[i] = 1;
  }
  dbg(cs);

  // DP from small ones
  vector<ll> dp(n + 1);
  FOR(i, 0, n) {
    auto [a, b] = ls[i];
    ll t = 0;
    if (b < a) {
      // Won't reach "0"
      t = dp[i];
    } else {
      // Become destroyer or not
      t = min((ll)b - a + 1, dp[i] + cs[i]);
    }
    dp[i + 1] = t;
  }

  auto res = dp[n];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/agc049/c/main.cpp

%%%% begin
3
1 2 3
1 2 1
%%%%
1
%%%% end

%%%% begin
4
1 3 5 7
3 1 4 1
%%%%
0
%%%% end
*/
