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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, t; // n \in [1, 40], t \in [1, 10^9]
  cin >> n >> t;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;

  // Meet in the middle
  auto runDP = [&](int i0, int i1) -> set<int> {
    set<int> dp, dp_prev;
    dp.insert(0);
    FOR(i, i0, i1) {
      int x = ls[i];
      dp_prev = dp;
      for (auto y : dp_prev) {
        if (x + y > t) { continue; }
        dp.insert(x + y);
      }
    }
    return dp;
  };

  auto dp1 = runDP(0, n / 2);
  auto dp2 = runDP(n / 2, n);
  dbg(dp1, dp2);

  int res = 0;
  for (auto x : dp1) {
    auto it = dp2.upper_bound(t - x);
    if (it == dp2.begin()) { continue; }
    int y = *prev(it);
    res = max(res, x + y);
  }

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc184/f/main.cpp

%%%% begin
5 17
2 3 5 7 11
%%%%
17
%%%% end

%%%% begin
6 100
1 2 7 5 8 10
%%%%
33
%%%% end

%%%% begin
6 100
101 102 103 104 105 106
%%%%
0
%%%% end

%%%% begin
7 273599681
6706927 91566569 89131517 71069699 75200339 98298649 92857057
%%%%
273555143
%%%% end
*/
