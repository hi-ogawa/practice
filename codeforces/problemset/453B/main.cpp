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

vector<int> makePrimes(int n) {
  vector<bool> sieve(n, 1);
  FOR(p, 2, sqrt(n) + 1) {
    if (!sieve[p]) { continue; }
    for (int x = p * p; x <= n; x += p) {
      sieve[x] = 0;
    }
  }
  vector<int> res;
  FOR(p, 2, n + 1) {
    if (sieve[p]) {
      res.push_back(p);
    }
  }
  return res;
};

// Main
void mainCase() {
  int n; // [1, 100]
  cin >> n;
  vector<int> ls(n); // [1, 30]
  cin >> ls;

  int m = 60; // we don't need b >= 2a since |a - 1| is smaller.
  auto ps = makePrimes(m);
  int k = ps.size();
  assert(k == 17);

  vector<int> masks(m); // qs[b] = { prime factors of "b" }
  FOR(b, 1, m) {
    int mask = 0;
    FOR(i, 0, k) {
      if (b % ps[i] == 0) {
        mask |= (1 << i);
      }
    }
    masks[b] = mask;
  }

  // dp(i, mask) = optimal cost for matching "ls[:i]" by factors from "mask"
  const int kInf = 1e9;
  vector<vector<int>> dp(n + 1, vector<int>(1 << k));
  FOR(i, 0, n) {
    int a = ls[i];
    FOR(mask, 0, 1 << k) {
      int t = kInf;
      FOR(b, 1, m) {
        int b_mask = masks[b];
        if ((mask & b_mask) != b_mask) { continue; } // Check b_mask ⊆ mask
        int s = dp[i][mask ^ b_mask] + abs(a - b);
        t = min(t, s);
      }
      dp[i + 1][mask] = t;
    }
  }

  auto it = min_element(ALL(dp[n]));
  int opt_mask = distance(dp[n].begin(), it);
  dbg(*it); // optimal cost

  // Backtrack to construct matching
  vector<int> res(n);
  for (int i = n - 1; i >= 0; i--) {
    int a = ls[i];
    bool found = 0;
    FOR(b, 1, m) {
      int b_mask = masks[b];
      if ((opt_mask & b_mask) != b_mask) { continue; }
      int prev_mask = opt_mask ^ b_mask;
      if (dp[i + 1][opt_mask] == dp[i][prev_mask] + abs(a - b)) {
        res[i] = b;
        opt_mask = prev_mask;
        found = 1;
        break;
      }
    }
    assert(found);
  }

  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/453B/main.cpp

%%%% begin
5
1 1 1 1 1
%%%%
1 1 1 1 1
%%%% end

%%%% begin
5
1 6 4 2 8
%%%%
1 5 3 1 8
%%%% end
*/
