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
#define DD(X) do { if (DEBUG) { std::cout << #X ": " << (X) << std::endl << std::flush; } } while (0)
#define DD2(X) do { if (DEBUG) { std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; } } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Fenwick tree for range counting
struct FenwickTree {
  int n_;
  vector<int> data_;
  FenwickTree(int n) { n_ = n; data_.resize(n); }
  void incr(int qi, int qv) {
    while (qi < n_) {
      data_[qi] += qv;
      qi = (qi | (qi + 1));
    }
  }
  int reduce(int qi) {
    ll res = 0;
    while (qi >= 0) {
      res += data_[qi];
      qi = (qi & (qi + 1)) - 1;
    }
    return res;
  }
  int reduce(int l, int r) {
    return reduce(r) -reduce(l - 1);
  }
};

// Main
void mainCase() {
  // Input
  int n; // <= 10^5
  cin >> n;
  vector<array<int, 4>> lines(n, {0}); // |p| <= 10^6
  cin >> lines;

  // Horizontal-sweep events
  enum { kHIn = 1, kV = 2, kHOut = 3}; // Ordering matters

  vector<array<int, 4>> events; // (x, h-in/h-out/v, y1, y2)
  for (auto [x1, y1, x2, y2] : lines) {
    assert(x1 <= x2);
    assert(y1 <= y2);
    if (y1 == y2) {
      events.push_back({x1, kHIn, y1, y1});
      events.push_back({x2, kHOut, y1, y1});
    }
    if (x1 == x2) {
      events.push_back({x1, kV, y1, y2});
    }
  }
  sort(ALL(events));
  DD(events);

  // Sweep
  int y_lim = 1e6; // Translate y coord to positive for Fenwick tree range counting
  FenwickTree isects(2 * y_lim);
  ll res = 0;
  for (auto [_x, t, y1, y2] : events) {
    y1 += y_lim; y2 += y_lim;
    if (t == kHIn) { isects.incr(y1, 1); }
    if (t == kHOut) { isects.incr(y1, -1); }
    if (t == kV) {
      res += isects.reduce(y1, y2);
    }
  }
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
python misc/run.py cses/additional_problems/task1740/main.cpp --check

%%%% begin
3
2 3 7 3
3 1 3 5
6 2 6 6
%%%%
2
%%%% end
*/
