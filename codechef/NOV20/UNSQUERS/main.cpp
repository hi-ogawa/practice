// AFTER EDITORIAL, AC

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

// Persistent segment tree for range increment and range max
// (cf. cses/range_queries/task1737/main.cpp for non-lazy persistent segment tree)
struct SegmentTree {
  using T = int;
  static T join(T lhs, T rhs) { return max(lhs, rhs); }

  struct Node {
    int l, r;
    T data = 0, lazy = 0;
    array<shared_ptr<Node>, 2> cs;

    void ensureChildren() {
      int m = (l + r) / 2;
      FOR(i, 0, 2) {
        auto& c = cs[i];
        if (c.use_count() == 0) {
          // Create node
          c = make_shared<Node>();
          c->l = i ? l : m;
          c->r = i ? m : r;
        }
        if (c.use_count() >= 2) {
          // Copy node if there are other users
          c = make_shared<Node>(*c);
        }
      }
    }

    T value() {
      return data + lazy;
    }

    void push() {
      if (lazy == 0) { return; }
      ensureChildren();
      data = value();
      cs[0]->lazy += lazy;
      cs[1]->lazy += lazy;
      lazy = 0;
    }

    T incr(int ql, int qr, T qv) {
      if (qr <= l || r <= ql) { return value(); }
      if (ql <= l && r <= qr) { lazy += qv; return value(); }
      push();
      ensureChildren();
      return data = join(cs[0]->incr(ql, qr, qv), cs[1]->incr(ql, qr, qv));
    }

    T reduce(int ql, int qr) {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return value(); }
      push();
      T res = 0;
      if (cs[0]) { res = join(res, cs[0]->reduce(ql, qr)); }
      if (cs[1]) { res = join(res, cs[1]->reduce(ql, qr)); }
      return res;
    }
  };

  Node root;
  int n = 1;

  SegmentTree(int n_orig) {
    while (n < n_orig) { n *= 2; }
    root.l = 0;
    root.r = n;
  }

  void incr(int ql, int qr, T qv) {
    root.incr(ql, qr, qv);
  }

  T reduce(int ql, int qr) {
    return root.reduce(ql, qr);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  int mode; // {0, 1}
  cin >> mode;
  vector<int> ls(n); // [1, 10^5]
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  // "cum max point" from each index
  vector<int> ps(n);
  {
    vector<array<int, 2>> st; // (index, value)
    FOR(i, 0, n) {
      while (!st.empty() && st.back()[1] < ls[i]) {
        st.pop_back();
      }
      if (!st.empty()) {
        ps[i] = st.back()[0] + 1;
      }
      st.push_back({i, ls[i]});
    }

  }
  dbg(ps);

  vector<SegmentTree> trees(1, SegmentTree(n));
  FOR(i, 0, n) {
    trees.push_back(trees.back());
    trees.back().incr(ps[i], i + 1, 1);
  }

  // [ Debug ]
  // FOR(i, 0, n) {
  //   FOR(j, 0, n) {
  //     dbg(i, j, trees[i].reduce(j, n));
  //   }
  // }
  // return;

  int res = 0;
  for (auto [l, r] : qs) {
    l = (l + mode * res - 1) % n;
    r = (r + mode * res - 1) % n;
    if (l > r) { swap(l, r); }
    r++;
    res = trees[r].reduce(l, r);
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codechef/NOV20/UNSQUERS/main.cpp

%%%% begin
6 3 0
4 2 3 1 5 5
1 6
2 4
3 4
%%%%
3
2
1
%%%% end

%%%% begin
10 10 1
7 8 8 9 10 10 2 3 5 10
9 6
2 9
10 6
4 2
5 10
4 5
8 7
8 2
7 7
9 5
%%%%
3
3
3
1
4
2
2
4
1
4
%%%% end
*/
