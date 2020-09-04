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
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Segment tree
struct SegmentTree {
  int depth_ = 0;
  vector<int> data_;
  SegmentTree(int n) {
    while ((1 << depth_) < n) { depth_++; }
    data_.resize((1 << (depth_ + 1)));
  }
  int up(int j) { return (j - 1) / 2; }
  int left(int j) { return 2 * j + 1; }
  int right(int j) { return 2 * j + 2; }
  int index(int qi) { return (1 << depth_) - 1 + qi; }

  int op(int x, int y, int d) {
    return (d % 2 == 0) ? (x | y) : (x ^ y);
  }

  void set(int qi, int qv) {
    int j = index(qi);
    int d = 0;
    data_[j] = qv;
    while (j > 0) {
      j = up(j);
      data_[j] = op(data_[left(j)], data_[right(j)], d);
      d++;
    }
  }

  int _reduce(int ql, int qr, int l, int r, int j, int d) {
    if (qr <= l || r <= ql) { return 0; }
    if (ql <= l && r <= qr) { return data_[j]; }
    int v1 = _reduce(ql, qr, l, (l + r) / 2, left(j),  d + 1);
    int v2 = _reduce(ql, qr, (l + r) / 2, r, right(j), d + 1);
    return op(v1, v2, d);
  }

  int reduce(int ql, int qr) {
    return _reduce(ql, qr, 0, (1 << depth_), 0, 0);
  }
};

// Main
void mainCase() {
  int nb, nq;
  cin >> nb >> nq;
  int n = 1 << nb;
  vector<int> ls(n);
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, ls[i]); }

  for (auto [x, y] : qs) {
    tree.set(x - 1, y);
    int res = tree.reduce(0, n);
    cout << res << endl;
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
python misc/run.py codeforces/problemset/339D/main.cpp --check

%%%% begin
2 4
1 6 3 5
1 4
3 4
1 2
1 2
%%%%
1
3
3
3
%%%% end
*/
