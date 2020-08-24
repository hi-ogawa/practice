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

// Segment tree for maximum
struct SegmentTree {
  int depth_ = 0;
  vector<ll> data_;
  SegmentTree(int n) {
    while ((1 << depth_) < n) { depth_++; }
    data_.resize(1 << (depth_ + 1));
  }
  int index(int qi) { return (1 << depth_) - 1 + qi; }
  ll get(int qi) { return data_[index(qi)]; }
  void incr(int qi, ll qv) { set(qi, get(qi) + qv); }
  void set(int qi, ll qv) {
    int j = index(qi);
    data_[j] = qv;
    while (j > 0) {
      j = (j - 1) / 2;
      // data_[j] = data_[2 * j + 1] + data_[2 * j + 2]; // Sum
      data_[j] = max(data_[2 * j + 1], data_[2 * j + 2]); // Max
    }
  }
  ll _reduce(int ql, int qr, int l, int r, int j) {
    if (ql <= l && r <= qr) { return data_[j]; }
    if (qr <= l || r <= ql) { return 0; }
    int mid = (l + r) / 2;
    ll v1 = _reduce(ql, qr, l, mid, 2 * j + 1);
    ll v2 = _reduce(ql, qr, mid, r, 2 * j + 2);
    // return v1 + v2; // Sum
    return max(v1, v2); // Max
  }
  ll reduce(int ql, int qr) { return _reduce(ql, qr, 0, 1 << depth_, 0); }
};

// Main
void mainCase() {
  int n, m; // <= 10^6
  cin >> n >> m;
  vector<ll> ls1(n, 0), ls2(m, 0);
  cin >> ls1 >> ls2;

  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, ls1[i]); }

  // min { i | x <= tree-max[:i] }
  auto search = [&](int x) -> int {
    if (tree.reduce(0, n) < x) { return -1; }
    // (i0, i1]
    int i0 = 0;
    int i1 = n;
    while (i0 + 1 < i1) {
      int i = (i0 + i1 + 1) / 2;
      if (x <= tree.reduce(0, i)) { i1 = i; }
      else                        { i0 = i; }
    }
    return i1 - 1;
  };

  vector<int> res(m, 0);
  FOR(j, 0, m) {
    int x = ls2[j];
    int i = search(x);
    res[j] = i;
    if (i != -1) { tree.incr(i, -x); }
  }

  FOR(i, 0, m) {
    if (i) cout << " ";
    cout << (res[i] + 1);
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
python misc/run.py cses/range_queries/task1143/main.cpp --check

%%%% begin
8 5
3 2 4 1 5 5 2 6
4 4 7 1 1
%%%%
3 5 0 1 1
%%%% end
*/
