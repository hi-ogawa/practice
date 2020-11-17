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
bool mainSolve(const vector<int>& ls1, const vector<int>& ls2) {
  map<int, int> cnts;
  for (auto x : ls1) { cnts[x]++; }

  vector<int> ls3;
  for (auto [k, v] : cnts) { ls3.push_back(v); }

  //
  // Problem
  //   Partition "xs" and assign each partition to "y" s.t. sum(partition) <= y
  //
  // N.B.
  //   With this formulation, the problem becomes a generalized version of https://cses.fi/problemset/task/1653/
  //
  auto& xs = ls2;
  auto& ys = ls3;
  int m = xs.size(); // [1, 10]
  int k = ys.size(); // [1, 50]

  // WLOG, we can assign from large "y"
  sort(ALL(ys));
  reverse(ALL(ys));

  dbg(xs, ys);

  // dp(S) = tuple of (count consumed ys, current partition's sum) for subset S
  vector<tuple<int, int>> dp(1 << m, {k, 0});
  dp[0] = {0, 0};
  FOR(s, 0, 1 << m) {
    auto [j, t] = dp[s];
    if (j >= k) { break; } // Already invalid

    FOR(i, 0, m) {
      if (s & (1 << i)) { continue; }
      int s2 = s | (1 << i);
      int j2 = j;
      int t2 = t + xs[i];
      if (t2 > ys[j2]) { // Move to next "y"
        j2++;
        t2 = xs[i];
      }
      if (j2 == k || t2 > ys[j2]) { // Found invalid
        break;
      }
      if (tie(j2, t2) < dp[s2]) {
        dp[s2] = {j2, t2};
      }
    }
  }

  auto [j, t] = dp[(1 << m) - 1];
  bool res = j < k;
  return res;
}

// Submission
class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
      return mainSolve(nums, quantity);
    }
};

// Testing
void mainCase() {
  int n, m;
  cin >> n >> m;
  vector<int> ls1(n), ls2(m);
  cin >> ls1 >> ls2;
  auto res = mainSolve(ls1, ls2);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py leetcode/problems/distribute-repeating-integers/main.cpp

%%%% begin
5 2
1 1 1 1 1
2 3
%%%%
1
%%%% end

%%%% begin
4 1
1 2 3 4
2
%%%%
0
%%%% end
*/
