// AC

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

struct SegmentTree {
  using T = ll;
  int n = 1;

  struct Node {
    int l, r;
    array<shared_ptr<Node>, 2> cs;
    T data = 0;

    void set(int qi, T qv) {
      assert(l <= qi && qi < r);
      if (l + 1 == r) { data = qv; return; } // Leaf case

      // Propagate to a child
      int m = (l + r) / 2;
      auto& c = cs[m <= qi];
      if (!c) {
        // Create new
        c = make_shared<Node>();
        c->l = (qi < m) ? l : m;
        c->r = (qi < m) ? m : r;
      } else {
        // Create copy if there are other users
        if (c.use_count() > 1) {
          c = make_shared<Node>(*c);
        }
      }
      c->set(qi, qv);

      data = (cs[0] ? cs[0]->data : 0) + (cs[1] ? cs[1]->data : 0);
    }

    T reduce(int ql, int qr) {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return data; }
      return (cs[0] ? cs[0]->reduce(ql, qr) : 0) + (cs[1] ? cs[1]->reduce(ql, qr) : 0);
    }
  };

  shared_ptr<Node> root;

  SegmentTree(int n_orig) {
    while (n < n_orig) { n *= 2; }
    root = make_shared<Node>();
    root->l = 0;
    root->r = n;
  }

  SegmentTree copy() {
    auto new_tree = *this;
    new_tree.root = make_shared<Node>(*root);
    return new_tree;
  }

  void set(int qi, T qv) {
    root->set(qi, qv);
  }

  T reduce(int ql, int qr) {
    return root->reduce(ql, qr);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;
  vector<array<int, 4>> qs(nq);
  for (auto& q : qs) {
    cin >> q[0];
    if (q[0] == 1) { cin >> q[1] >> q[2] >> q[3]; }
    if (q[0] == 2) { cin >> q[1] >> q[2] >> q[3]; }
    if (q[0] == 3) { cin >> q[1]; }
  }

  vector<SegmentTree> trees(1, SegmentTree(n));
  FOR(i, 0, n) {
    trees[0].set(i, ls[i]);
  }

  for (auto [t, k, x, y] : qs) {
    k--;

    if (t == 1) {
      trees[k].set(x - 1, y);
    }

    if (t == 2) {
      auto res = trees[k].reduce(x - 1, y);
      cout << res << "\n";
    }

    if (t == 3) {
      trees.push_back(trees[k].copy());
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/range_queries/task1737/main.cpp

%%%% begin
5 6
2 3 1 2 5
3 1
2 1 1 5
2 2 1 5
1 2 2 5
2 1 1 5
2 2 1 5
%%%%
13
13
13
15
%%%% end
*/
