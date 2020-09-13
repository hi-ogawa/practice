// AFTER EDITORIAL, AC

// NOTE: Use FFT (idea is from neal's solution)

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
using cd = complex<double>;

uint32_t reverse32(uint32_t x) {
  x = ((x & 0x55555555U) <<  1) | ((x & 0xaaaaaaaaU) >>  1); // 0101 = 0x5, 1010 = 0xa
  x = ((x & 0x33333333U) <<  2) | ((x & 0xccccccccU) >>  2); // 0011 = 0x3, 1100 = 0xc
  x = ((x & 0x0f0f0f0fU) <<  4) | ((x & 0xf0f0f0f0U) >>  4);
  x = ((x & 0x00ff00ffU) <<  8) | ((x & 0xff00ff00U) >>  8);
  x = ((x & 0x0000ffffU) << 16) | ((x & 0xffff0000U) >> 16);
  return x;
}

void fft(vector<cd>& f, bool inv) {
  int n = f.size();
  int m = 0;
  while ((1 << m) < n) { m++; }
  FOR(i, 0, n) {
    int j = reverse32(i) >> (32 - m);
    if (i < j) { swap(f[i], f[j]); }
  }
  for (int l = 2; l <= n; l *= 2) {
    cd u = exp((inv ? 2i: -2i) * M_PI / (cd)l);
    for (int i = 0; i < n; i += l) {
      cd z = 1.0;
      for (int k = 0; k < l / 2; k++) {
        auto& x = f[i + k];
        auto& y = f[i + k + l / 2];
        tie(x, y) = make_tuple(x + z * y, x - z * y);
        z *= u;
      }
    }
  }
  if (inv) {
    for (auto& x : f) { x /= n; }
  }
}

void polymul(vector<cd>& p, vector<cd>& q, vector<cd>& r) {
  fft(p, 0); fft(q, 0);
  int n = p.size();
  FOR(i, 0, n) { r[i] = p[i] * q[i]; }
  fft(r, 1);
}

int roundPow2(int n) {
  int m = 1;
  while (m < n) { m *= 2; }
  return m;
};

void polymul01(vector<cd>& p, vector<cd>& q) {
  int np = p.size(), nq = q.size();
  int n = 2 * roundPow2(max(np, nq));
  p.resize(n);
  q.resize(n);
  polymul(p, q, q);
  int nn = 0;
  FOR(i, 0, n) {
    q[i] = round(q[i].real()) >= 1;
    if (q[i] == (cd)1) { nn = i + 1; }
  }
  q.resize(nn);
};

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
  map<int, vector<int>> compos;
  FOR(i, 0, n) {
    compos[dsu.find(i)].push_back(i);
  }

  // Multiplicity of each component size (ms.size() ~ O(√n))
  map<int, int> ms;
  for (auto& [_k, vs] : compos) {
    ms[vs.size()]++;
  }
  dbg(ms);

  //
  // Find subset sums via FFT
  //

  // Construct 0/1 coefficient polynomials
  vector<vector<cd>> ps;
  for (auto [s, m] : ms) {
    auto& p = ps.emplace_back();
    p.resize(m * s + 1);
    FOR(i, 0, m + 1) { p[i * s] = 1; }
  }
  dbg2(ps);

  // Multiply them all
  auto compare = [](auto& x, auto& y) { return x.size() < y.size(); };
  multiset<vector<cd>, decltype(compare)> heap(compare);
  heap.insert(ALL(ps));
  dbg2(heap);

  while (heap.size() > 1) {
    auto p = *heap.begin(); heap.erase(heap.begin());
    auto q = *heap.begin(); heap.erase(heap.begin());
    polymul01(p, q);
    heap.insert(q);
  }
  auto res = *heap.begin();

  FOR(i, 1, n + 1) {
    cout << round(res[i].real());
  }
  cout << endl;
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
python misc/run.py cses/additional_problems/task1706/main_v5.cpp --check

%%%% begin
10 7
2 3
4 5
9 10
1 2
3 4
7 8
6 7
%%%%
0110101101
%%%% end

%%%% begin
5 3
1 2
2 3
1 5
%%%%
10011
%%%% end
*/
