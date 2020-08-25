// TLE

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

// Segment tree for vertical union size (with quite sketchy lazy system)
struct SegmentTree {
  int depth_ = 0;
  vector<ll> data_; // non-zero segment size
  vector<ll> req_; // increment request

  SegmentTree(int n) {
    while ((1 << depth_) < n) { depth_++; }
    data_.resize((1 << (depth_ + 1)));
    req_.resize((1 << (depth_ + 1)));
  }
  int up(int j) { return (j - 1) / 2; }
  int left(int j) { return 2 * j + 1; }
  int right(int j) { return 2 * j + 2; }
  int index(int qi) { return (1 << depth_) - 1 + qi; }

  void merge(ll qv, int j) { // Merge request
    req_[j] += qv;
  }

  void propagate(int j) { // Propagate request
    ll v = req_[j];
    merge(v, left(j));
    merge(v, right(j));
    req_[j] = 0;
  }

  // TODO: probably this relies on the fact that all "add request" is countered by "sub request"
  ll value(int l, int r, int j) { // Value with resolving request if negative
    if (req_[j] < 0) {
      // TODO: this makes it's not really "lazy" segment tree system (i.e. probably not "log(n)" query)
      propagate(j);
      ll v1 = value(l, (l + r) / 2, left(j));
      ll v2 = value((l + r) / 2, r, right(j));
      return data_[j] = v1 + v2;
    }
    return req_[j] > 0 ? (r - l) : data_[j];
  }

  // @returns (l, r)-nonzero-size
  ll _incr(int ql, int qr, ll qv, int l, int r, int j) {
    if (qr <= l || r <= ql) { return value(l, r, j); }
    if (ql <= l && r <= qr) { merge(qv, j); return value(l, r, j); }
    propagate(j);
    ll v1 = _incr(ql, qr, qv, l, (l + r) / 2, left(j));
    ll v2 = _incr(ql, qr, qv, (l + r) / 2, r, right(j));
    return data_[j] = v1 + v2;
  }

  void incr(int ql, int qr, ll qv) {
    _incr(ql, qr, qv, 0, (1 << depth_), 0);
  }

  // @returns ((ql, qr)-nonzero, (l, r)-nonzero)
  tuple<ll, ll> _reduce(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return {0, value(l, r, j)}; }
    if (ql <= l && r <= qr) { return {value(l, r, j), value(l, r, j)}; }
    propagate(j);
    auto [u1, v1] = _reduce(ql, qr, l, (l + r) / 2, left(j));
    auto [u2, v2] = _reduce(ql, qr, (l + r) / 2, r, right(j));
    return {u1 + u2, data_[j] = v1 + v2};
  }
  ll reduce(int ql, int qr) {
    return get<0>(_reduce(ql, qr, 0, (1 << depth_), 0));
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
  enum { kIn, kOut };

  vector<array<int, 4>> events; // (x, y1, y2, in/out)
  for (auto [x1, y1, x2, y2] : lines) {
    assert(x1 <= x2);
    assert(y1 <= y2);
    events.push_back({x1, y1, y2, kIn});
    events.push_back({x2, y1, y2, kOut});
  }
  sort(ALL(events));
  DD(events);

  // Sweep
  int lim = 1e6; // Translate y coord to positive
  SegmentTree isects(2 * lim + 1);
  ll res = 0;
  int ie = 0, ne = events.size();
  FOR(sweep_x, -lim, lim + 1) {
    // Integrate vertical union
    ll tmp = isects.reduce(0, 2 * lim + 1);
    DD(tie(sweep_x, tmp));
    res += tmp;

    // Update isects
    while (ie < ne && events[ie][0] <= sweep_x) {
      auto [x, y1, y2, t] = events[ie++];
      DD(tie(sweep_x, x, y1, y2, t));
      y1 += lim; y2 += lim;
      if (t == kIn) {
        isects.incr(y1, y2, 1);
      }
      if (t == kOut) {
        isects.incr(y1, y2, -1);
      }
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
python misc/run.py cses/additional_problems/task1741/main.cpp --check

%%%% begin
3
1 3 4 5
3 1 7 4
5 3 8 6
%%%%
24
%%%% end
*/
