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

template<ll M>
struct ModOp {
  ll m = M;
  ll add(ll x, ll y) { return (x + y) % M; }
  ll mul(ll x, ll y) { return (x * y) % M; }
  ll div(ll x, ll y) { return mul(x, inv(y)); }
  ll inv(ll x)       { return pow(x, M - 2); }
  ll pow(ll x, ll e) {
    ll y = 1;
    while (e > 0) {
      if (e & 1) { y = mul(y, x); }
      x = mul(x, x); e >>= 1;
    }
    return y;
  }

  template<size_t N>
  using mat = array<array<ll, N>, N>;

  template<size_t N>
  mat<N> mat_id() {
    mat<N> x;
    FOR(i, 0, (int)N) {
      FOR(j, 0, (int)N) {
        x[i][j] = i == j; } }
    return x;
  }

  template<size_t N>
  mat<N> matmul(mat<N>& x, mat<N>& y) {
    mat<N> z;
    FOR(i, 0, (int)N) {
      FOR(j, 0, (int)N) {
        z[i][j] = 0;
        FOR(k, 0, (int)N) {
          z[i][j] = add(z[i][j], mul(x[i][k], y[k][j])); } } }
    return z;
  }

  template<size_t N>
  mat<N> matpow(mat<N> x, ll e) {
    mat<N> y = mat_id<N>();
    while (e > 0) {
      if (e & 1) { y = matmul(y, x); }
      x = matmul(x, x); e >>= 1;
    }
    return y;
  }

  ll dice(ll n) {
    mat<6> a = {{
      {1, 1, 1, 1, 1, 1},
      {1, 0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0, 0},
      {0, 0, 1, 0, 0, 0},
      {0, 0, 0, 1, 0, 0},
      {0, 0, 0, 0, 1, 0}}};
    auto b = matpow(a, n);
    // DD2(b);
    ll res = b[0][0];
    res = add(res, m);
    return res;
  }
};

// Main
void mainCase() {
  ll n; // <= 10^18
  cin >> n;

  static ModOp<1000'000'000 + 7> mo;
  ll res = mo.dice(n);
  cout << res << endl;
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
python misc/run.py cses/mathematics/task1096/main.cpp --check

%%%% begin
8
%%%%
125
%%%% end
*/
