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
  int n; // [3, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;

  // Keep order to restore partitions
  vector<int> order(n);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return ls[x] < ls[y]; });
  auto order_inv = order;
  FOR(i, 0, n) {
    order_inv[order[i]] = i;
  }
  sort(ALL(ls));

  //
  // PROP.
  //   f(i + 3) = min_{j <= i} f(j) + x(i + 3) - x(j + 1)
  //

  vector<array<ll, 2>> dp(n);
  set<array<ll, 2>> heap;
  heap.insert({-ls[0], -1});
  FOR(i, 0, n) {
    if (i >= 5) {
      heap.insert({dp[i - 3][0] - ls[i - 2], i - 3});
    }
    auto [t, j] = *heap.begin();
    dp[i] = {ls[i] + t, j};
  }
  dbg(dp);

  auto res1 = dp[n - 1][0];

  vector<int> res2(n);
  int i1 = n - 1;
  int cnt = 0;
  while (i1 != -1) {
    int i0 = dp[i1][1];
    FOR(i, i0 + 1, i1 + 1) {
      res2[i] = cnt;
    }
    i1 = i0;
    cnt++;
  }

  cout << res1 << " " << cnt << "\n";
  FOR(i, 0, n) {
    cout << (res2[order_inv[i]] + 1) << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1256E/main_v2.cpp

%%%% begin
5
1 1 3 4 2
%%%%
3 1
1 1 1 1 1
%%%% end

%%%% begin
6
1 5 12 13 2 15
%%%%
7 2
2 2 1 1 2 1
%%%% end

%%%% begin
10
1 2 5 129 185 581 1041 1909 1580 8150
%%%%
7486 3
3 3 3 2 2 2 2 1 1 1
%%%% end
*/
