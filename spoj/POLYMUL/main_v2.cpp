// AC

// DFT with complex number

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

void _dft(
    const vector<cd>& f, vector<cd>& g, vector<cd>& tmp,
    int beg, int step, int n, bool inv) {
  if (n == 1) { g[beg] = f[beg]; return; }
  int m = n / 2;
  _dft(f, g, tmp, beg,        2 * step, m, inv);
  _dft(f, g, tmp, beg + step, 2 * step, m, inv);
  cd u = exp((inv ? 2i : -2i) * M_PI / (cd)n);
  cd z = 1.0;
  FOR(k, 0, m) {
    cd x = g[beg + 2 * step * k];
    cd y = g[beg + 2 * step * k + step];
    tmp[beg + step * k]       = x + z * y;
    tmp[beg + step * (k + m)] = x - z * y;
    z *= u;
  }
  FOR(k, 0, n) {
    g[beg + step * k] = tmp[beg + step * k];
  }
}

void dft(const vector<cd>& f, vector<cd>& g, bool inv = false) {
  vector<cd> tmp(f.size());
  _dft(f, g, tmp, 0, 1, f.size(), inv);
  if (inv) { for (auto& x : g) { x /= g.size(); } }
}

// Main
void mainCase() {
  int n; // <= 10^4
  cin >> n;
  vector<ll> p(n + 1), q(n + 1); // |c| <= 10^3
  cin >> p >> q;
  reverse(ALL(p));
  reverse(ALL(q));

  vector<cd> pc(ALL(p)), qc(ALL(q));
  int m = 1 << (int)ceil(log2(2 * n + 1));
  pc.resize(m);
  qc.resize(m);

  vector<cd> pc_dft(m), qc_dft(m);
  dft(pc, pc_dft);
  dft(qc, qc_dft);

  vector<cd> rc_dft(m);
  FOR(i, 0, m) { rc_dft[i] = pc_dft[i] * qc_dft[i]; }

  vector<cd> rc(m);
  dft(rc_dft, rc, /* inv */ true);
  dbg(rc);

  vector<ll> r(2 * n + 1);
  FOR(i, 0, 2 * n + 1) {
    r[i] = round(rc[i].real());
  }

  reverse(ALL(r));
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
python misc/run.py spoj/POLYMUL/main_v2.cpp --check

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
