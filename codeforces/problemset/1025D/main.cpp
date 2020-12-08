// TLE

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

  // dp(i, j) = possible prime factors at the root of BST for ls[i:j]
  vector<vector<set<int>>> dp(n, vector<set<int>>(n + 1));
  FOR(i, 0, n) {
    dp[i][i + 1] = {ALL(factors[i])};
  }

  // NOTE: n^3 |factors| ~ 700^3 10 = 3 10^9, so clearly TLE
  FOR(l, 2, n + 1) {
    FOR(i, 0, n - l + 1) {
      int j = i + l;
      FOR(k, i, j) {
        bool ok = 0;
        for (auto p : factors[k]) {
          ok = 1;
          if (i < k)     { ok = ok && dp[i][k].count(p);}
          if (k < j - 1) { ok = ok && dp[k + 1][j].count(p);}
          if (ok) { break; }
        }
        if (!ok) { continue; }
        for (auto p : factors[k]) {
          dp[i][j].insert(p);
        }
      }
    }
  }
  dbg2(dp);

  bool res = !dp[0][n].empty();
  cout << (res ? "Yes" : "No") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1025D/main.cpp

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
