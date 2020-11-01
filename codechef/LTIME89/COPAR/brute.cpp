
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

// Euler sieve
tuple<vector<int>, vector<int>> makeEulerSieve(int n) {
  tuple<vector<int>, vector<int>> res;
  auto& [ps, lp] = res;
  lp.resize(n + 1);
  for (int x = 2; x <= n; x++) {
    if (lp[x] == 0) { lp[x] = x; ps.push_back(x); }
    for (auto p : ps) {
      if (x * p > n || p > lp[x]) { break; }
      lp[x * p] = p;
    }
  }
  return res;
}

// Main
void mainCase() {
  int n; // [2, 10^5]
  cin >> n;
  vector<int> ls(n); // [2, 10^5]
  cin >> ls;

  int res;
  FOR(i, 1, n + 1) {
    ll x = 1, y = 1;
    FOR(j, 0, i) {
      x *= ls[j];
    }
    FOR(j, i, n) {
      y *= ls[j];
    }
    if (gcd(x, y) == 1) {
      res = i;
      break;
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codechef/LTIME89/COPAR/main.cpp

%%%% begin
1
3
2 16 7
%%%%
2
%%%% end

%%%% begin
1
4
2 3 4 5
%%%%
3
%%%% end
*/
