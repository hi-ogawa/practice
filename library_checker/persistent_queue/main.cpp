// AC

// NOTE: Persistent segment tree must be overkill, but don't know how to implement otherwise...

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Persistent segment tree
struct SegmentTree {
  using T1 = int;
  using T2 = pair<T1, int>; // (value, index) of first non-zero entry
  static inline T2 zero = {0, -1};

  static T2 join(T2 lhs, T2 rhs) {
    return lhs.first > 0 ? lhs : rhs;
  }

  struct Node {
    T2 data = zero;
    array<shared_ptr<Node>, 2> cs;

    void ensureChildren(int qi, int m) {
      int side = m <= qi;
      auto& c = cs[side];
      if (c.use_count() == 0) { // Create node
        c = make_shared<Node>();
        return;
      }
      if (c.use_count() >= 2) { // Copy node
        c = make_shared<Node>(*c);
        return;
      }
    }

    void set(int qi, T1 qv, int l, int r) {
      if (qi < l || r <= qi) { return; }
      if (l + 1 == r) { data = {qv, l}; return; }
      int m = (l + r) / 2;
      ensureChildren(qi, m);
      T2 res = zero;
      if (cs[0]) { cs[0]->set(qi, qv, l, m); res = join(res, cs[0]->data); }
      if (cs[1]) { cs[1]->set(qi, qv, m, r); res = join(res, cs[1]->data); }
      data = res;
    }
  };

  int n = 1;
  Node root;

  SegmentTree(int n_orig) {
    while (n < n_orig) { n *= 2; }
  }

  void set(int qi, T1 qv) { root.set(qi, qv, 0, n); }
};

// Main
void mainCase() {
  int n; // [1, 5 x 10^5]
  cin >> n;

  vector<SegmentTree> trees(1, SegmentTree(n + 1));

  FOR(i, 0, n) {
    int t, k;
    cin >> t >> k;
    k++;
    assert(k < (int)trees.size());
    auto& tree = trees.emplace_back(trees[k]);

    if (t == 0) {
      int x;
      cin >> x; // [0, 10^9]
      x++; // Make it non-zero
      tree.set(i + 1, x);
    }

    if (t == 1) {
      auto [x, j] = tree.root.data;
      assert(x > 0);
      x--;
      tree.set(j, 0);
      cout << x << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/persistent_queue/main.cpp

%%%% begin
6
0 -1 6
0 0 7
1 0
0 -1 8
1 3
1 1
%%%%
6
8
6
%%%% end
*/
