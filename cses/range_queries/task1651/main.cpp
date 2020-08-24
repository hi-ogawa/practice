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

// Segment tree with range value
struct SegmentTree {
  int depth_ = 0;
  vector<ll> data_;
  SegmentTree(int n) {
    while ((1 << depth_) < n) { depth_++; }
    data_.resize(1 << (depth_ + 1));
  }
  int index(int qi) {
    return (1 << depth_) - 1 + qi;
  }
  ll get(int qi) {
    int j = index(qi);
    ll res = data_[j];
    while (j > 0) {
      j = (j - 1) / 2;
      res += data_[j];
    }
    return res;
  }
  void _incr(int ql, int qr, int qv, int l, int r, int j) {
    if (ql <= l && r <= qr) { data_[j] += qv; return; }
    if (qr <= l || r <= ql) { return; }
    int mid = (l + r) / 2;
    _incr(ql, qr, qv, l, mid, 2 * j + 1);
    _incr(ql, qr, qv, mid, r, 2 * j + 2);
  }
  void incr(int ql, int qr, int qv) {
    _incr(ql, qr, qv, 0, 1 << depth_, 0);
  }
};

// Main
void mainCase() {
  int n, nq;
  cin >> n >> nq;
  vector<int> ls(n, 0);
  cin >> ls;
  vector<array<int, 4>> qs(nq, {0});
  FOR(iq, 0, nq) {
    int t, a, b, c; t = a = b = c = 0;
    cin >> t;
    if (t == 1) { cin >> a >> b >> c; }
    if (t == 2) { cin >> a; }
    qs[iq] = {t, a, b, c};
  }
  // DD(qs);

  SegmentTree tree(n);
  for (auto [t, a, b, c] : qs) {
    if (t == 1) {
      a--;
      tree.incr(a, b, c);
    }
    if (t == 2) {
      a--;
      ll res = tree.get(a);
      res += ls[a];
      cout << res << endl;
    }
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
python misc/run.py cses/range_queries/task1651/main.cpp --check

%%%% begin
8 3
3 2 4 5 1 1 5 3
2 4
1 2 5 1
2 4
%%%%
5
6
%%%% end
*/
