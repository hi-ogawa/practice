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

// Segment Tree
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
  int get(int qi) { return data_[index(qi)]; }
  void incr(int qi, int qv) { set(qi, get(qi) + qv); }
  void set(int qi, int qv) {
    int j = index(qi);
    data_[j] = qv;
    while (j > 0) {
      j = up(j);
      data_[j] = data_[left(j)] + data_[right(j)];
    }
  }
  int _reduce(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return 0; }
    if (ql <= l && r <= qr) { return data_[j]; }
    int v1 = _reduce(ql, qr, l, (l + r) / 2, left(j));
    int v2 = _reduce(ql, qr, (l + r) / 2, r, right(j));
    return v1 + v2;
  }
  int reduce(int ql, int qr) {
    return _reduce(ql, qr, 0, (1 << depth_), 0);
  }
};

// Main
void mainCase() {
  int n; // <= 10^6
  cin >> n;
  vector<int> ls(n); // <= 10^9
  cin >> ls;

  // Compress values
  vector<int> dec = ls;
  sort(ALL(dec));
  dec.erase(unique(ALL(dec)), dec.end());
  map<int, int> enc;
  FOR(i, 0, (int)dec.size()) { enc[dec[i]] = i; }
  FOR(i, 0, n) {
    ls[i] = enc[ls[i]];
  }

  // Count left/right values
  SegmentTree left(n), right(n);
  FOR(i, 1, n) { right.incr(ls[i], 1); }

  // Sweep "j" of i < j < k
  ll res = 0;
  FOR(j, 1, n) {
    left.incr(ls[j - 1], 1);
    right.incr(ls[j], -1);
    ll x = left.reduce(ls[j] + 1, n);
    ll y = right.reduce(0, ls[j]);
    res += x * y;
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
python misc/run.py codeforces/problemset/61E/main.cpp --check

%%%% begin
4
10 8 3 1
%%%%
4
%%%% end
*/
