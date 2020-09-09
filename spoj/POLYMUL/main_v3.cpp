// AC

// DFT with complex number (optimization from cp-algorithms)

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

using cd = complex<double>;

uint32_t reverse32(uint32_t x) {
  x = ((x & 0x55555555U) <<  1) | ((x & 0xaaaaaaaaU) >>  1); // 0x5 = '0101', 0xa = '1010'
  x = ((x & 0x33333333U) <<  2) | ((x & 0xccccccccU) >>  2); // 0x3 = '0011', 0xc = '1100'
  x = ((x & 0x0f0f0f0fU) <<  4) | ((x & 0xf0f0f0f0U) >>  4);
  x = ((x & 0x00ff00ffU) <<  8) | ((x & 0xff00ff00U) >>  8);
  x = ((x & 0x0000ffffU) << 16) | ((x & 0xffff0000U) >> 16);
  return x;
}

void dft(vector<cd>& f, bool inv = 0) {
  int n = f.size();
  int m = 0;
  while ((1 << m) < n) { m++; }
  FOR(i, 0, n) {
    int j = reverse32(i) >> (32 - m);
    if (i < j) { swap(f[i], f[j]); }
  }
  for (int l = 2; l <= n; l <<= 1) {
    cd u = exp((inv ? 2i : -2i) * M_PI / (cd)l);
    for (int i = 0; i < n; i += l) {
      cd z = 1.0;
      for (int k = 0; k < l / 2; k++) {
        cd& x = f[i + k];
        cd& y = f[i + k + l / 2];
        tie(x, y) = make_tuple(x + z * y, x - z * y);
        z *= u;
      }
    }
  }
  if (inv) {
    for (auto& x : f) { x /= n; }
  }
}

// Main
void mainCase() {
  int n; // <= 10^4
  cin >> n;
  vector<ll> p(n + 1), q(n + 1); // |c| <= 10^3
  cin >> p >> q;

  vector<cd> pc(ALL(p)), qc(ALL(q));
  int m = 1;
  while (m < 2 * n + 1) { m <<= 1; }
  pc.resize(m);
  qc.resize(m);

  auto pc_dft = pc;
  auto qc_dft = qc;
  dft(pc_dft);
  dft(qc_dft);

  vector<cd> rc_dft(m);
  FOR(i, 0, m) { rc_dft[i] = pc_dft[i] * qc_dft[i]; }

  auto rc = rc_dft;
  dft(rc, /* inv */ true);
  dbg(rc);

  vector<ll> r(2 * n + 1);
  FOR(i, 0, 2 * n + 1) {
    r[i] = round(rc[i].real());
  }

  FOR(i, 0, 2 * n + 1) {
    if (i) cout << " ";
    cout << r[i];
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py spoj/POLYMUL/main_v3.cpp --check

%%%% begin
1
3
0 5 7 0
2 0 0 3
%%%%
0 10 14 0 15 21 0
%%%% end

%%%% begin
1
0
2
3
%%%%
6
%%%% end

%%%% begin
1
1
1 2
3 4
%%%%
3 10 8
%%%% end

%%%% begin
2
2
1 2 3
3 2 1
2
1 0 1
2 1 0
%%%%
3 8 14 8 3
2 1 2 1 0
%%%% end
*/
