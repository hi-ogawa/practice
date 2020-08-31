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

struct SegmentTree {
  struct Node {
    int p = 0; // paired
    int l = 0, r = 0; // unpaired brakets
    Node() {}
    Node(char c) { l = c == '('; r = c == ')'; }

    static Node merge(const Node& v1, const Node& v2) {
      int new_p = min(v1.l, v2.r);
      Node res;
      res.p = v1.p + v2.p + 2 * new_p;
      res.l = (v1.l - new_p) + v2.l;
      res.r = (v2.r - new_p) + v1.r;
      return res;
    }
  };

  int depth_ = 0;
  vector<Node> data_;

  SegmentTree(const string& s) {
    int n = s.size();
    while ((1 << depth_) < n) { depth_++; }
    data_.resize((1 << (depth_ + 1)));
    FOR(i, 0, n) {
      set(i, Node(s[i]));
    }
  }
  ostream& print(ostream& ostr) {
    FOR(d, 0, depth_ + 1) {
      int j0 = (1 << d) - 1;
      FOR(j, j0, j0 + (1 << d)) {
        if (j > j0) { ostr << " "; }
        auto v = data_[j];
        ostr << make_tuple(v.p, v.l, v.r);
      }
      ostr << endl;
    }
    ostr << endl;
    return ostr;
  }

  int up(int j) { return (j - 1) / 2; }
  int left(int j) { return 2 * j + 1; }
  int right(int j) { return 2 * j + 2; }
  int index(int qi) { return (1 << depth_) - 1 + qi; }

  void set(int qi, Node qv) {
    int j = index(qi);
    data_[j] = qv;
    while (j > 0) {
      j = up(j);
      data_[j] = Node::merge(data_[left(j)], data_[right(j)]);
    }
  }

  Node _reduce(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return Node(); }
    if (ql <= l && r <= qr) { return data_[j]; }
    Node v1 = _reduce(ql, qr, l, (l + r) / 2, left(j));
    Node v2 = _reduce(ql, qr, (l + r) / 2, r, right(j));
    return Node::merge(v1, v2);
  }

  int reduce(int ql, int qr) {
    return _reduce(ql, qr, 0, (1 << depth_), 0).p;
  }
};

// Main
void mainCase() {
  string s; // |s| <= 10^6
  cin >> s;
  int nq; // <= 10^5
  cin >> nq;
  vector<array<int, 2>> qs(nq);
  cin >> qs;
  dbgv(s, qs);

  // Precompute "bracket number"
  SegmentTree tree(s);
  #if DEBUG
    tree.print(cout);
  #endif

  // Answer queries
  for (auto [l, r] : qs) {
    dbgv(l, r);
    int res = tree.reduce(l - 1, r);
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
python misc/run.py codeforces/problemset/380C/main.cpp --check

%%%% begin
())(())(())(
7
1 1
2 3
1 2
1 12
8 12
5 11
2 10
%%%%
0
0
2
10
4
6
6
%%%% end
*/
