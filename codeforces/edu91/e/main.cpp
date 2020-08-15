// AFTER CONTEST, TLE

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
template<class T, size_t N>  istream& operator>>(istream& i, array<T, N>& x)  { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T, size_t N>  ostream& operator<<(ostream& o, const array<T, N>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Segment tree (cf. codeforces/edu/ex273169A/main.cpp)
struct SegmentTree {
  using Node = tuple<int, int, int>; // (left-type, right-type, consecutive)
  int n_;
  int depth_;
  vector<Node> data_;

  SegmentTree(int n) : n_{n} {
    depth_ = 0;
    while ((1 << depth_) < n_) { depth_++; }
    data_.resize(1 << (depth_ + 1));
    FOR(i, 0, 1 << depth_) { set(i, - i - 1); } // Initialize with irrelavant elements
  }

  void set(int qi, int qv) {
    int i0 = (1 << depth_) - 1 + qi;
    data_[i0] = {qv, qv, 0};
    int i = i0;
    while (i > 0) {
      i = ((i + 1) / 2) - 1;
      auto [l1, r1, c1] = data_[2 * i + 1];
      auto [l2, r2, c2] = data_[2 * i + 2];
      data_[i] = {l1, r2, c1 + c2 + (r1 == l2)};
    }
  }

  int getConsecutive() {
    return get<2>(data_[0]);
  }
};

// Main
void mainCase() {
  ll n, m;
  cin >> n >> m;

  vector<ll> ls(n, 0);
  cin >> ls;
  // DD(ls);

  vector<tuple<ll, ll>> qs(m - 1, {0, 0});
  cin >> qs;
  // DD(qs);

  // TODO: should be dsu?
  map<int, set<int>> groups;
  FOR(i, 0, n) {
    groups[ls[i]].insert(i);
  }
  // DD(groups);

  // Initialize segment tree
  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, ls[i]); }
  // DD(tree.getConsecutive());

  // Befor queries
  cout << (n - 1 - tree.getConsecutive()) << endl;

  // Answer queries
  for (auto [a, b] : qs) {
    // TODO: too much update O(n^2)
    for (auto i : groups[b]) {
      ls[i] = a;
      tree.set(i, a);
      groups[a].insert(i);
    }
    // DD(tree.getConsecutive());

    int res = n - 1 - tree.getConsecutive();
    cout << res << endl;
  }
}

int main() {
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
python misc/run.py codeforces/edu91/e/main.cpp --check

%%%% begin
7 4
1 2 3 3 1 4 3
3 1
2 3
2 4
%%%%
5
4
2
0
%%%% end
*/
