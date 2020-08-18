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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, nq; // <= 10^6
  cin >> n >> nq;

  vector<ll> edges(n, 0);
  cin >> edges;
  for (auto& x : edges) { x--; }

  vector<tuple<ll, ll>> qs(nq, {0, 0}); // k <= 10^9
  cin >> qs;
  for (auto& [x, _k] : qs) { x--; }

  // "Binary lifting"-like table
  ll m = 30; // 2^m > k_max
  vector<vector<ll>> table(m, vector<ll>(n, 0));
  table[0] = edges;
  FOR(i, 0, m - 1) {
    FOR(j, 0, n) {
      table[i + 1][j] = table[i][table[i][j]];
    }
  }
  // DD2(table);

  // Answer queries
  for (auto [v, k] : qs) {
    // Binary exponentiation
    int u = v;
    ll e = k;
    ll b = 0;
    while (e > 0) {
      if (e & 1) { u = table[b][u]; }
      e >>= 1;
      b++;
    }
    ll res = u + 1;
    cout << res << endl;
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
python misc/run.py cses/graph_algorithms/task1750/main.cpp --check

%%%% begin
4 3
2 1 1 4
1 2
3 4
4 1
%%%%
1
2
4
%%%% end
*/
