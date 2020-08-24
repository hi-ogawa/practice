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

// Segment tree for max-sum-segment
struct SegmentTree {
  // For each segment, we track
  //   Total sum
  //   max prefix sum
  //   max suffix sum
  //   max infix sum
  struct Node {
    ll tot = 0, pre = 0, suf = 0, inf = 0;
    Node() {}
    Node(ll x) {
      tot = x;
      if (x >= 0) { pre = suf = inf = x; }
    }

  };
  int depth_ = 0;
  vector<Node> data_;

  SegmentTree(int n) {
    while ((1 << depth_) < n) { depth_++; }
    int k = 1 << (depth_ + 1);
    data_.resize(k);
  }
  int index(int qi) { return (1 << depth_) - 1 + qi; }
  int up(int j) { return (j - 1) / 2; }
  int left(int j) { return 2 * j + 1; }
  int right(int j) { return 2 * j + 2; }

  // Kadane-like DP
  Node merge(Node l, Node r) {
    Node res;
    res.tot = l.tot + r.tot;
    res.inf = max(l.inf, max(r.inf, l.suf + r.pre));
    res.pre = max(l.pre, l.tot + r.pre);
    res.suf = max(l.suf + r.tot, r.suf);
    return res;
  }

  void set(int qi, int qv) {
    int j = index(qi);
    data_[j] = Node(qv);
    while (j > 0) {
      j = up(j);
      data_[j] = merge(data_[left(j)], data_[right(j)]);
    }
  }
};

// Main
void mainCase() {
  int n, nq;
  cin >> n >> nq;
  vector<int> ls(n, 0);
  cin >> ls;
  vector<array<int, 2>> qs(nq, {0});
  cin >> qs;

  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, ls[i]); }

  for (auto [i, x] : qs) {
    i--;
    tree.set(i, x);
    ll res = tree.data_[0].inf;
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
python misc/run.py cses/range_queries/task1190/main.cpp --check

%%%% begin
5 3
1 2 -3 5 -1
2 6
3 1
2 -2
%%%%
9
13
6
%%%% end
*/
