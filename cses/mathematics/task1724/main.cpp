// AC

// Cf. Tropical ring

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<class T> using vector2 = vector<vector<T>>;
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
  ll n, m, k; // n <= 100, k <= 10^9
  cin >> n >> m >> k;
  vector<array<ll, 3>> edges(m, {0, 0, 0});
  cin >> edges;

  // Toropical matrix zeros and identity
  vector2<ll> tzeros(n, vector<ll>(n, -1));
  auto tidentity = tzeros;
  FOR(i, 0, n) { tidentity[i][i] = 0; }

  // Toropical add/mul
  auto tadd = [](ll x, ll y) {
    if (y == -1) { swap(x, y); }
    return x == -1 ? y : min(x, y);
  };

  auto tmul = [](ll x, ll y) {
    return (x == -1 || y == -1) ? -1 : (x + y);
  };

  // Toropical matrix mul/pow
  auto tmatmul = [&](vector2<ll>& x, const vector2<ll>& y) {
    auto z = tzeros;
    FOR(i, 0, n) {
      FOR(j, 0, n) {
        z[i][j] = -1;
        FOR(k, 0, n) {
          z[i][j] = tadd(z[i][j], tmul(x[i][k], y[k][j]));
        }
      }
    }
    return z;
  };

  auto tmatpow = [&](vector2<ll>& b, ll& e) {
    auto res = tidentity;
    auto x = b;
    while (e > 0) {
      if (e & 1) { res = tmatmul(res, x); }
      x = tmatmul(x, x);
      e >>= 1;
    }
    return res;
  };

  vector2<ll> adj = tzeros;
  for (auto [x, y, c] : edges) {
    x--; y--;
    adj[y][x] = tadd(adj[y][x], c); // Can be multiple edges
  }
  // DD2(adj);

  // Answer
  auto res = tmatpow(adj, k);
  // DD2(res);

  cout << res[n - 1][0] << endl;
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
python misc/run.py cses/mathematics/task1724/main.cpp --check

%%%% begin
3 4 8
1 2 5
2 3 4
3 1 1
3 2 2
%%%%
27
%%%% end

%%%% begin
5 20 8
4 5 10
2 5 10
4 4 3
4 4 1
4 1 5
3 5 7
1 3 2
4 1 9
3 1 3
1 1 2
4 2 3
3 3 4
2 4 7
4 1 9
3 5 2
5 3 5
1 3 3
5 3 1
4 1 6
2 2 5
%%%%
13
%%%% end
*/
