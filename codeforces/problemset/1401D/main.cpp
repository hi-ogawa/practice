// AC

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
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n; // [2, 10^5]
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  int m; // [1, 6 x 10^4]
  cin >> m;
  vector<ll> ls(m);
  cin >> ls;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  vector<ll> coeffs; // linear coefficient of edges
  vector<int> sizes(n); // subtree size
  function<void(int, int)> dfs = [&](int v, int vp) {
    sizes[v] = 1;
    for (auto u : adj[v]) {
      if (u == vp) { continue; }
      dfs(u, v);
      sizes[v] += sizes[u];
      coeffs.push_back((ll)sizes[u] * (n - sizes[u]));
    }
  };
  dfs(0, 0);
  assert((int)coeffs.size() == n - 1);

  const ll modulo = 1e9 + 7;
  auto add = [&](ll x, ll y) { return (x + y) % modulo; };
  auto mul = [&](ll x, ll y) { return (x * y) % modulo; };
  auto addeq = [&](ll&x, ll y) { return x = add(x, y); };
  auto muleq = [&](ll&x, ll y) { return x = mul(x, y); };

  // Fill "dummy" factors
  if (m < n - 1) {
    fill_n(back_inserter(ls), n - 1 - m, 1);
  }

  // Collect large factors into one
  sort(ALL(ls));
  if (m > n - 1) {
    FOR(i, n - 1, m) {
      muleq(ls[n - 2], ls[i]);
    }
    ls.resize(n - 1);
  }

  // Dot product
  sort(ALL(coeffs));
  ll res = 0;
  FOR(i, 0, n - 1) {
    addeq(res, mul(ls[i], coeffs[i]));
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1401D/main.cpp --check

%%%% begin
1
16
5 10
16 1
14 1
7 5
13 2
16 11
1 7
1 4
3 14
8 16
1 6
4 9
4 12
5 13
1 15
18
45893 9901 51229 15511 46559 28433 4231 30241 29837 34421 12953 6577 12143 52711 40493 89 34819 28571
%%%%
667739716
%%%% end

%%%% begin
3
4
1 2
2 3
3 4
2
2 2
4
3 4
1 3
3 2
2
3 2
7
6 1
2 3
4 6
7 3
5 1
3 6
4
7 5 13 3
%%%%
17
18
286
%%%% end
*/
