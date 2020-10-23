// TLE

// NOTE: It takes 3.6 sec for input06.txt.

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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

const ll kInf = 1e18;

// Segment tree for range max
struct SegmentTree {
  int n = 1;
  using Node = ll;
  static inline Node kZero = -kInf;
  vector<ll> data;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, kZero);
  }

  void set(int qi, ll qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = max(data[2 * j], data[2 * j + 1]);
    }
  }

  ll reduce(int ql, int qr) {
    function<ll(int, int, int)> rec = [&](int l, int r, int j) -> ll {
      if (qr <= l || r <= ql) { return kZero; }
      if (ql <= l && r <= qr) { return data[j]; }
      int m = (l + r) / 2;
      return max(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    return rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int num_types; // [1, 100]
  int max_cost; // [1, 10^5]
  cin >> num_types >> max_cost;
  vector<vector<int>> ls(3, vector<int>(num_types)); // (costs, gains, counts) // [1, 1000]
  cin >> ls;

  // dp(i, j) = g  \iff there exists a way to make "gain = g" by "total cost = j" using "1, 2, .. i types"
  vector<ll> dp(max_cost + 1, -kInf);
  dp[0] = 0;
  FOR(i, 0, num_types) {
    // Range max for bounded count knapsack
    int cost = ls[0][i];
    int gain = ls[1][i];
    int count = ls[2][i];

    vector<SegmentTree> trees(cost, SegmentTree(max_cost / cost + 1));
    FOR(j, 0, max_cost + 1) {
      int q = j / cost, r = j % cost;
      trees[r].set(q, dp[j] - q * gain);
    }

    FOR(j, 0, max_cost + 1) {
      int q = j / cost, r = j % cost;
      int p = max(q - count, 0);
      ll t = trees[r].reduce(p, q + 1);
      dp[j] = t + q * gain;
    }
    dbg(dp);
  }

  ll res = *max_element(ALL(dp));
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1159/main.cpp

%%%% begin
3 10
2 6 3
8 5 4
3 5 2
%%%%
28
%%%% end
*/
