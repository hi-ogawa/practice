
// NOTE: Hopefully AC but gfg compiler says something wrong...

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

// Segment tree for prefix maximum
struct SegmentTree {
  int depth_ = 0;
  vector<ll> data_;
  SegmentTree(int n) {
    while ((1 << depth_) < n) { depth_++; }
    data_.resize((1 << (depth_ + 1)));
  }
  int up(int j) { return (j - 1) / 2; }
  int left(int j) { return 2 * j + 1; }
  int right(int j) { return 2 * j + 2; }
  int index(int qi) { return (1 << depth_) - 1 + qi; }
  ll get(int qi) {
    return data_[index(qi)];
  }
  void set(int qi, int qv) {
    int j = index(qi);
    data_[j] = qv;
    while (j > 0) {
      j = up(j);
      data_[j] = max(data_[left(j)], data_[right(j)]);
    }
  };
  ll _reduce(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return 0; }
    if (ql <= l && r <= qr) { return data_[j]; }
    ll v1 = _reduce(ql, qr, l, (l + r) / 2, left(j));
    ll v2 = _reduce(ql, qr, (l + r) / 2, r, right(j));
    return max(v1, v2);
  }
  ll reduce(int ql, int qr) {
    return _reduce(ql, qr, 0, (1 << depth_), 0);
  }
};

ll solve(const vector<array<int, 3>>& ls) {
  int n = ls.size();

  map<int, map<int, int, greater<int>>> ps; // (w1, w2, max-h)
  FOR(i, 0, n) {
    FOR(j, 0, 3) {
      int a = ls[i][j];
      int b = ls[i][(j + 1) % 3];
      int c = ls[i][(j + 2) % 3];
      ps[a][b] = max(ps[a][b], c);
    }
  }
  dbg(ps);

  // Similar to geeksforgeeks/maximum-sum-increasing-subsequence/main_v2.cpp
  int k = ps.rbegin()->first;
  SegmentTree dp(k + 1);
  for (auto [_w1, qs] : ps) { // w1 is already increasing
    for (auto [w2, h] : qs) { // loop reverse (cf. greater<int>) so not to conflict within the same w1
      // Make sure w2 is increasing
      ll s = dp.reduce(0, w2);
      dp.set(w2, max(dp.get(w2), s + h));
    }
  }

  ll res = dp.reduce(0, k + 1);
  return res;
}

// [ for gfg submission ]
int maxHeight(int height[], int width[], int length[], int n) {
  vector<array<int, 3>> ls(n, {0, 0, 0});
  FOR(i, 0, n) {
    ls[i] = {height[i], width[i], length[i]};
  }
  return solve(ls);
}

// Main
void mainCase() {
  int n; // <= 100
  cin >> n;
  vector<array<int, 3>> ls(n, {0, 0, 0}); // <= 100
  cin >> ls;
  cout << solve(ls) << endl;
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
python misc/run.py geeksforgeeks/box-stacking/main.cpp --check

%%%% begin
1
4
4 6 7
1 2 3
4 5 6
10 12 32
%%%%
60
%%%% end
*/
