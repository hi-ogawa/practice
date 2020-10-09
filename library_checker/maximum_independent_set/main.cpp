// AC

// NOTE: "meet in the middle" to solve maximum independent set for n = 40
// TODO: try max clique on complement (cf. https://github.com/yosupo06/library-checker-problems/blob/master/graph/maximum_independent_set/sol/correct.cpp)

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
  int n, m; // n \in [1, 40]
  cin >> n >> m;
  vector<array<int, 2>> edges(m);
  cin >> edges;

  // Split vertices into [0, n1) and [n1, n)
  int n1 = n / 2, n2 = n - n1;
  vector<array<int, 2>> edges1, edges2, edges3;
  for (auto [x, y] : edges) {
    if (x > y) { swap(x, y); }
    if (y < n1) { edges1.push_back({x, y}); continue; }
    if (x >= n1) { edges2.push_back({x - n1, y - n1}); continue; }
    edges3.push_back({x, y - n1});
  }
  dbg(n1, n2, edges);
  dbg(edges1, edges2, edges3);

  auto popcount = [](int x) -> int { return __builtin_popcount(x); };

  // DP over subsets
  auto runDP = [&](int n, const vector<array<int, 2>>& edges) -> vector<int> {
    vector<int> dp((1 << n), 0); // dp[S] = 0 \iff no edge in S
    for (auto [x, y] : edges) {
      dp[(1 << x) | (1 << y)] = 1;
    }
    FOR(s, 0, 1 << n) {
      FOR(x, 0, n) {
        int sx = s | (1 << x);
        if (s == sx) { continue; }
        dp[sx] |= dp[s];
      }
    }
    // f(S) = T  s.t.  max { |T| | T ⊆ S and no edge in T }
    vector<int> f((1 << n), 0);
    FOR(s, 0, 1 << n) {
      FOR(x, 0, n) {
        int sx = s | (1 << x);
        if (s == sx) { continue; }
        if (dp[sx] == 0) { f[sx] = sx; }
        if (popcount(f[s]) > popcount(f[sx])) {
          f[sx] = f[s];
        }
      }
    }
    return f;
  };
  auto dp1 = runDP(n1, edges1);
  auto dp2 = runDP(n2, edges2);

  // Meet in the middle
  vector<int> connection(n1);
  for (auto [x, y] : edges3) {
    connection[x] |= (1 << y);
  }
  auto takeComplement = [&](int s1) -> int {
    int s2 = 0;
    FOR(x, 0, n1) {
      if (s1 & (1 << x)) {
        s2 |= connection[x];
      }
    }
    return ((1 << n2) - 1) & ~s2;
  };
  int res = 0;
  int res1, res2;
  FOR(s1, 0, 1 << n1) {
    int s2 = takeComplement(s1);
    int t = popcount(dp1[s1]) + popcount(dp2[s2]);
    if (t > res) {
      res = t;
      res1 = dp1[s1];
      res2 = dp2[s2];
    }
  }
  vector<int> res3;
  FOR(x, 0, n1) {
    if (res1 & (1 << x)) {
      res3.push_back(x);
    }
  }
  FOR(y, 0, n2) {
    if (res2 & (1 << y)) {
      res3.push_back(y + n1);
    }
  }
  dbg(res, res1, res2, res3);

  cout << res << "\n";
  FOR(i, 0, res) {
    cout << res3[i] << " \n"[i == res - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/maximum_independent_set/main.cpp

%%%% begin
8 10
0 1
2 3
4 5
6 7
0 2
2 4
4 6
1 3
3 5
5 7
%%%%
4
5 2 1 6
%%%% end

%%%% begin
7 9
0 1
1 2
2 0
2 3
3 4
4 2
4 5
5 6
6 4
%%%%
3
6 1 3
%%%% end
*/
