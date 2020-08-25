// TLE

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define DD(X) do { if (DEBUG) { std::cout << #X ": " << (X) << std::endl << std::flush; } } while (0)
#define DD2(X) do { if (DEBUG) { std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; } } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// DSU
struct Dsu {
  vector<int> data_;
  Dsu(int n) { data_.resize(n), iota(ALL(data_), 0); }
  int find(int a) {
    if (data_[a] == a) { return a; }
    return data_[a] = find(data_[a]);
  }
  void merge(int dst, int src) {
    data_[find(src)] = find(dst);
  }
};

// Main
void mainCase() {
  // Input
  int n, m; // <= 10^5
  cin >> n >> m;
  vector<tuple<int, int>> edges(m, {0, 0});
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  // Connected components
  Dsu dsu(n);
  for (auto [x, y] : edges) {
    dsu.merge(x, y);
  }
  map<int, int> compo_sizes;
  FOR(i, 0, n) {
    compo_sizes[dsu.find(i)]++;
  }
  vector<int> ls;
  for (auto [k, v] : compo_sizes) {
    ls.push_back(v);
  }
  sort(ALL(ls));
  DD(ls);

  // Find possible sums (obviously TLE)
  if (0) {
    int k = ls.size();
    vector<bool> dp(n + 1, 0);
    dp[0] = 1;
    FOR(i, 0, k) {
      int x = ls[i];
      for (int j = n; j >= x; j--) {
        dp[j] = dp[j] || dp[j - x];
      }
    }
    DD(dp);

    FOR(i, 1, n + 1) {
      cout << dp[i];
    }
    cout << endl;
  }

  // Find possible sums (TODO: some optimization based on multiset ps??)
  {
    map<int, int> ps;
    for (auto x : ls) { ps[x]++; }
    vector<tuple<int, int>> qs(ALL(ps));
    int l = qs.size(); // <= sqrt(n)
    DD(qs);

    vector<vector<bool>> dp(l + 1, vector<bool>(n + 1, 0));
    dp[0][0] = 1;
    FOR(i, 0, l) {
      auto [x, t] = qs[i];
      // TODO: can we cull some steps?
      for (int j = 0; j <= n; j++) {
        for (int c = 0; c <= t; c++) {
          int y = j + c * x;
          if (y > n) { break; }
          dp[i + 1][y] = dp[i + 1][y] + dp[i][j];
        }
      }
    }
    DD2(dp);

    FOR(i, 1, n + 1) {
      cout << dp[l][i];
    }
    cout << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py cses/additional_problems/task1706/main.cpp --check

%%%% begin
5 3
1 2
2 3
1 5
%%%%
10011
%%%% end
*/
