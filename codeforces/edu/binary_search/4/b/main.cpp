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

using Real = double;
const Real kInf = 1e18;
const Real kEps = 1e-10;

// Main
void mainCase() {
  int n, m; // [1, 10^5]
  cin >> n >> m;
  vector<array<int, 3>> edges(m); // w \in [0, 100]
  cin >> edges;

  vector<vector<array<int, 2>>> adjT(n);
  for (auto [x, y, w] : edges) {
    x--; y--;
    adjT[y].push_back({x, w});
  }

  // f(x) = d(1, n | x) = shortest path in "x-biased graph"
  auto evaluate = [&](Real x) -> tuple<Real, vector<int>> {
    vector<Real> dp(n, kInf);
    vector<int> parents(n);
    dp[0] = 0;
    FOR(j, 1, n) {
      for (auto [i, w] : adjT[j]) {
        auto t = dp[i] + (w - x); // bias "x"
        if (t < dp[j]) {
          dp[j] = t;
          parents[j] = i;
        }
      }
    }
    return {dp[n - 1], move(parents)};
  };

  // max { x | f(x) >= 0 }
  auto search = [&]() -> Real {
    Real x0 = 0;
    Real x1 = kInf;
    while (x1 - x0 >= kEps) {
      auto x = (x0 + x1) / 2;
      auto [dist, parents] = evaluate(x);
      dbg(x0, x1, x, dist, parents);
      if (dist >= 0) {
        x0 = x;
      } else {
        x1 = x;
      }
    }
    return x1;
  };

  auto x = search();
  auto [dist, parents] = evaluate(x);
  vector<int> res;
  int v = n - 1;
  while (v != 0) {
    res.push_back(v);
    v = parents[v];
  }
  res.push_back(0);
  reverse(ALL(res));

  int k = res.size();
  cout << (k - 1) << "\n";
  FOR(i, 0, k) {
    cout << (res[i] + 1) << " \n"[i == k - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/binary_search/4/b/main.cpp

%%%% begin
4 3
1 2 1
2 3 0
2 4 1
%%%%
2
1 2 4
%%%% end

%%%% begin
3 3
1 2 1
2 3 2
1 3 1
%%%%
1
1 3
%%%% end
*/
