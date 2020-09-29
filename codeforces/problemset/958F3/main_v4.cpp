// AFTER EDITORIAL, AC

// NOTE: complex<double> fft with small trick (https://codeforces.com/blog/entry/58888?#comment-425352)

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
    using TV = typename T::value_type;
    const TV pi = acos(-1);
    roots[0].resize(1 << nb_max);
    roots[1].resize(1 << nb_max);
    for (int b = 1; b < nb_max; b++) {
      int l = 1 << b;
      roots[0][b].resize(l / 2);
      roots[1][b].resize(l / 2);
      for (int k = 0; k < l / 2; k++) {
        TV t = 2.0 * pi * (TV)k / (TV)l;
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

void polymul2(vector<int>& p, vector<int>& q, vector<int>& r) {
  int n = p.size();
  using fft_t = complex<double>;
  vector<fft_t> pp(n), qq(n), rr(n);
  const int modulo = 1009;
  auto mod_up = [](int x) { return (x % modulo + modulo) % modulo; };
  FOR(i, 0, n) {
    if ((p[i] > modulo / 2)) { p[i] -= modulo; }
    if ((q[i] > modulo / 2)) { q[i] -= modulo; }
    pp[i] = p[i];
    qq[i] = q[i];
  }
  polymul(pp, qq, rr);
  FOR(i, 0, n) {
    r[i] = mod_up((int)round(rr[i].real()));
  }
}

int pow2Ceil(int n) {
  int b = 0;
  while ((1 << b) < n) { b++; }
  return 1 << b;
}

void polymul3(vector<int>& p, vector<int>& q, vector<int>& r, int n_lim) {
  // Align to power of two
  int n = pow2Ceil(min(n_lim, 2 * (int)max(p.size(), q.size())));
  p.resize(n); q.resize(n); r.resize(n);
  // Multiply
  polymul2(p, q, r);
  // Remove leading zeros
  while (r.size() >= 2 && r.back() == 0) { r.pop_back(); }
}

vector<int> polymulAll(vector<vector<int>>& ps, int n_lim) {
  // Multiply together from small degrees
  auto compare = [](auto& x, auto& y) { return x.size() < y.size(); };
  multiset<vector<int>, decltype(compare)> heap(compare);
  heap.insert(ALL(ps));
  while (heap.size() >= 2) {
    auto p = *heap.begin(); heap.erase(heap.begin());
    auto q = *heap.begin(); heap.erase(heap.begin());
    polymul3(p, q, q, n_lim);
    heap.insert(q);
  }
  return *heap.begin();
}

// Main
void mainCase() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> ls(n);
  cin >> ls;

  vector<int> cnts(m);
  for (auto x : ls) { x--; cnts[x]++; }

  // Make 0/1 coefficient polynomials
  vector<vector<int>> ps(m);
  FOR(i, 0, m) { ps[i].assign(cnts[i] + 1, 1); }

  auto q = polymulAll(ps, n + 1);
  assert(k < (int)q.size());

  int res = q[k];
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/958F3/main_v4.cpp --check

%%%% begin
111 16 58
15 6 4 7 7 10 16 2 3 1 4 8 10 1 2 11 6 6 14 16 6 16 1 2 13 2 7 13 1 4 1 4 12 2 4 11 15 12 9 13 10 4 11 7 5 3 12 11 11 3 16 15 9 6 15 11 4 14 8 15 16 3 9 10 9 1 8 4 14 7 13 5 1 8 5 11 8 14 1 8 15 2 5 2 4 5 9 2 10 11 11 5 7 11 11 14 5 16 14 2 4 11 12 10 7 14 2 5 3 2 1
%%%%
552
%%%% end

%%%% begin
4 3 2
1 2 3 2
%%%%
4
%%%% end
*/
