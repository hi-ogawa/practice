// AC

// NOTE: we can just divide the final result by factorial without caring double counting during DP.

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

// NOTE: Need fraction to remove double count
using Real = long double;

// Main
void mainCase() {
  ll n; // [1, 10^18]
  cin >> n;
  ll m; // [1, 100]
  cin >> m;

  // To digits
  vector<int> ls;
  while (n > 0) {
    ls.push_back(n % 10);
    n /= 10;
  }
  int k = ls.size();
  dbg(ls);

  // Modulo of 10^i
  vector<int> qs(k);
  qs[0] = 1 % m;
  FOR(i, 1, k) {
    qs[i] = (qs[i - 1] * 10) % m;
  }
  dbg(qs);

  // dp(S, j) = ....
  vector<vector<Real>> dp(1 << k, vector<Real>(m));
  dp[0][0] = 1;
  FOR(s, 0, 1 << k) {
    // Double count factor for each digits
    array<ll, 10> cnts = {};
    FOR(d, 0, 10) {
      FOR(i, 0, k) {
        cnts[d] += (ls[i] == d && (s & (1 << i)));
      }
    }

    // Usual DP
    int pc = __builtin_popcount(s);
    FOR(j, 0, m) {
      FOR(i, 0, k) {
        if (s & (1 << i)) { continue; }
        int d = ls[i];
        if (pc == k - 1 && d == 0) { continue; } // Leading zero not allowed
        int s2 = s | (1 << i);
        int j2 = (j + d * qs[pc]) % m;
        dp[s2][j2] += dp[s][j] / (cnts[d] + 1); // Remove double count when we "push"
      }
    }
  }
  dbg2(dp);

  auto res = dp[(1 << k) - 1][0];
  cout << (ll)round(res) << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/401D/main_v3.cpp

%%%% begin
104 2
%%%%
3
%%%% end

%%%% begin
223 4
%%%%
1
%%%% end

%%%% begin
7067678 8
%%%%
47
%%%% end
*/
