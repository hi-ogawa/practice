// WIP, WA

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

// FFT
uint32_t reverse32(uint32_t x) {
  x = ((x & 0x55555555U) <<  1) | ((x & 0xaaaaaaaaU) >>  1); // 0101 = 0x5, 1010 = 0xa
  x = ((x & 0x33333333U) <<  2) | ((x & 0xccccccccU) >>  2); // 0011 = 0x3, 1100 = 0xc
  x = ((x & 0x0f0f0f0fU) <<  4) | ((x & 0xf0f0f0f0U) >>  4);
  x = ((x & 0x00ff00ffU) <<  8) | ((x & 0xff00ff00U) >>  8);
  x = ((x & 0x0000ffffU) << 16) | ((x & 0xffff0000U) >> 16);
  return x;
}

template<class T>
void fft(vector<T>& f, bool inv) {
  static bool first_run = true;
  constexpr int nb_max = 20;
  static array<vector<vector<T>>, 2> roots; // roots[inv][b][k] = (2^b root)^k
  if (first_run) {
    first_run = false;
    using U = typename T::value_type;
    const U pi = acos(-1);
    roots[0].resize(nb_max + 1);
    roots[1].resize(nb_max + 1);
    for (int b = 1; b <= nb_max; b++) {
      int l = 1 << b;
      roots[0][b].resize(l / 2);
      roots[1][b].resize(l / 2);
      for (int k = 0; k < l / 2; k++) {
        U t = 2.0 * pi * (U)k / (U)l;
        roots[0][b][k] = {cos(t), - sin(t)};
        roots[1][b][k] = {cos(t), + sin(t)};
      }
    }
  }

  int n = f.size();
  assert(n <= (1 << nb_max));
  int nb = 0;
  while ((1 << nb) < n) { nb++; }
  FOR(i, 0, n) {
    int j = reverse32(i) >> (32 - nb);
    if (i < j) { swap(f[i], f[j]); }
  }
  for (int lb = 1; lb <= nb; lb++) {
    int l = 1 << lb;
    auto& u = roots[inv][lb];
    for (int i = 0; i < n; i += l) {
      for (int k = 0; k < l / 2; k++) {
        auto x = f[i + k];
        auto y = f[i + k + l / 2] * u[k];
        f[i + k]         = x + y;
        f[i + k + l / 2] = x - y;
      }
    }
  }
  if (inv) {
    for (auto& x : f) { x /= n; }
  }
}

template<class T>
void polymul(vector<T>& p, vector<T>& q, vector<T>& r) {
  fft(p, 0); fft(q, 0);
  FOR(i, 0, (int)p.size()) { r[i] = p[i] * q[i]; }
  fft(r, 1);
}

void polymul3(vector<int>& p, vector<int>& q, vector<int>& r, int modulo) {
  // Karatsuba
  int n = p.size();
  int base = sqrt(modulo) + 1;
  using C = complex<double>;
  array<vector<C>, 3> pp, qq, rr;
  pp.fill(vector<C>(n));
  qq.fill(vector<C>(n));
  rr.fill(vector<C>(n));
  FOR(i, 0, n) {
    pp[0][i] = p[i] % base;
    pp[1][i] = p[i] / base;
    pp[2][i] = pp[0][i] + pp[1][i];
    qq[0][i] = q[i] % base;
    qq[1][i] = q[i] / base;
    qq[2][i] = qq[0][i] + qq[1][i];
  }
  FOR(j, 0, 3) { polymul(pp[j], qq[j], rr[j]); }

  auto up  = [&](ll x) { return (x + modulo) % modulo; };
  auto add = [&](ll x, ll y) { return up((x + y) % modulo); };
  auto mul = [&](ll x, ll y) { return up((x * y) % modulo); };
  auto addeq = [&](ll&x, ll y) { return x = add(x, y); };

  FOR(i, 0, n) {
    ll x = 0;
    array<C::value_type, 3> ri;
    FOR(j, 0, 3) { ri[j] = round(rr[j][i].real()); }
    addeq(x, ri[0]);
    addeq(x, mul(ri[2] - ri[1] - ri[0], base));
    addeq(x, mul(ri[1], mul(base, base)));
    r[i] = x;
  }
}

int pow2Ceil(int n) {
  int m = 1;
  while (m < n) { m *= 2; }
  return m;
}

void polymul2(vector<int>& p, vector<int>& q, vector<int>& r, int modulo) {
  int n = 2 * pow2Ceil(max(p.size(), q.size()));
  p.resize(n); q.resize(n); r.resize(n);
  polymul3(p, q, r, modulo);
}

// Main
void mainCase() {
  int n, m;
  cin >> n >> m;
  vector<int> p(n), q(m), r;
  cin >> p >> q;

  const int modulo = 1e9 + 7;
  polymul2(p, q, r, modulo);

  int k = n + m - 1;
  FOR(i, 0, k) {
    cout << r[i] << " \n"[i == k - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/convolution_mod_1000000007/main_v2.cpp --check

%%%% begin
4 5
1 2 3 4
5 6 7 8 9
%%%%
5 16 34 60 70 70 59 36
%%%% end

%%%% begin
1 1
10000000
10000000
%%%%
999300007
%%%% end

%%%% begin
1 1
1000000000
1000000000
%%%%
49
%%%% end
*/
