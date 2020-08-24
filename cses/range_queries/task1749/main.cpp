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

// Segment tree for sum
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
    return data_[index(qi)];
  }
  void incr(int qi, ll qv) {
    set(qi, get(qi) + qv);
  }
  void set(int qi, ll qv) {
    int j = index(qi);
    data_[j] = qv;
    while (j > 0) {
      j = (j - 1) / 2;
      data_[j] = data_[2 * j + 1] + data_[2 * j + 2];
    }
  }
  ll _reduce(int ql, int qr, int l, int r, int j) {
    if (ql <= l && r <= qr) { return data_[j]; }
    if (qr <= l || r <= ql) { return 0; }
    int mid = (l + r) / 2;
    ll v1 = _reduce(ql, qr, l, mid, 2 * j + 1);
    ll v2 = _reduce(ql, qr, mid, r, 2 * j + 2);
    return v1 + v2;
  }
  ll reduce(int ql, int qr) { return _reduce(ql, qr, 0, 1 << depth_, 0); }
};

// Main
void mainCase() {
  int n; // <= 10^6
  cin >> n;
  vector<ll> ls1(n, 0), ls2(n, 0);
  cin >> ls1 >> ls2;

  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, 1); }

  // min { i | k <= tree-sum[:i] }
  auto search = [&](int k) -> int {
    if (tree.reduce(0, n) < k) { return -1; }
    // (i0, i1]
    int i0 = 0;
    int i1 = n;
    while (i0 + 1 < i1) {
      int i = (i0 + i1 + 1) / 2;
      if (k <= tree.reduce(0, i)) { i1 = i; }
      else                        { i0 = i; }
    }
    return i1 - 1;
  };

  vector<int> res(n, 0);
  FOR(i, 0, n) {
    int k = ls2[i];
    int j = search(k);
    assert(j >= 0);
    res[i] = ls1[j];
    tree.set(j, 0);
  }

  FOR(i, 0, n) {
    if (i) cout << " ";
    cout << res[i];
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
python misc/run.py cses/range_queries/task1749/main.cpp --check

%%%% begin
5
2 6 1 4 2
3 1 3 1 1
%%%%
1 2 2 6 4
%%%% end
*/
