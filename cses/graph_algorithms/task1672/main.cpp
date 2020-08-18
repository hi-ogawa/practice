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
  ll n, m, nq; // <= 500
  cin >> n >> m >> nq;

  vector<array<int, 3>> edges(m, {0, 0, 0});
  cin >> edges;

  vector<array<int, 2>> qs(nq, {0, 0});
  cin >> qs;

  // Floyd-Warshall
  ll kInf = 1L << 50;
  vector<vector<ll>> ds(n, vector<ll>(n, kInf));
  auto _ds = [&](int x, int y) -> ll& {
    if (x > y) { swap(x, y); }
    return ds[x][y];
  };
  for (auto [x, y, d] : edges) {
    x--; y--;
    _ds(x, y) = min(_ds(x, y), (ll)d);
  }
  FOR(i, 0, n) { _ds(i, i) = 0; }
  // DD2(ds);

  FOR(k, 0, n) {
    FOR(i, 0, n) {
      FOR(j, 0, n) {
        _ds(i, j) = min(_ds(i, j), _ds(i, k) + _ds(k, j));
      }
    }
  }
  // DD2(ds);

  // Answer queries
  for (auto [v1, v2] : qs) {
    v1--; v2--;
    ll d = _ds(v1, v2);
    cout << (d == kInf ? -1 : d) << endl;
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
python misc/run.py cses/graph_algorithms/task1672/main.cpp --check

%%%% begin
2 2 1
1 2 1
1 2 2
1 2
%%%%
1
%%%% end


%%%% begin
4 3 5
1 2 5
1 3 9
2 3 3
1 2
2 1
1 3
1 4
3 2
%%%%
5
5
8
-1
3
%%%% end
*/
