// AFTER EDITORIAL, AC

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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n; // [2, 700]
  cin >> n;
  vector<int> ls(n); // [2, 10^9], distinct, increasing
  cin >> ls;

  auto factorize = [&](int x) -> vector<int> {
    vector<int> res;
    for (int p = 2; p * p <= x; p++) {
      if (x % p) { continue; }
      while (x % p == 0) { x /= p; }
      res.push_back(p);
    }
    if (x > 1) { res.push_back(x); }
    return res;
  };

  vector<vector<int>> factors(n);
  FOR(i, 0, n) {
    // Length at most 10 since 2.3.5...p(10) > 10^9
    factors[i] = factorize(ls[i]);
  }
  dbg(factors);

  // dp(i, j, 0) = 1 <=> ls[i:j] can be rooted to ls[i]
  // dp(i, j, 1) = 1 <=> ls[i:j] can be rooted to ls[j]
  vector<vector<array<int, 2>>> dp(n, vector<array<int, 2>>(n));

  FOR(i, 0, n) {
    dp[i][i] = {1, 1};
  }
  FOR(l, 2, n + 1) {
    FOR(i, 0, n - l + 1) {
      int j = i + l;
      FOR(k, i + 1, j) {
        if (dp[i + 1][k][1] && dp[k][j - 1][0] && gcd(ls[i], ls[k]) > 1) {
          dp[i][j - 1][0] = 1;
          break;
        }
      }
      FOR(k, i, j - 1) {
        if (dp[i][k][1] && dp[k][j - 2][0] && gcd(ls[k], ls[j - 1]) > 1) {
          dp[i][j - 1][1] = 1;
          break;
        }
      }
    }
  }

  bool res = 0;
  FOR(i, 0, n) {
    if (dp[0][i][1] && dp[i][n - 1][0]) {
      res = 1;
      break;
    }
  }
  cout << (res ? "Yes" : "No") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1025D/main_v2.cpp

%%%% begin
6
3 6 9 18 36 108
%%%%
Yes
%%%% end

%%%% begin
2
7 17
%%%%
No
%%%% end

%%%% begin
9
4 8 10 12 15 18 33 44 81
%%%%
Yes
%%%% end
*/
