// TLE

// NOTE: For input_max_00.txt example, memory is okay (~200MB) but TLE (20sec)

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

// RNG
auto rng = mt19937(0x12345678);

// Treap for range sum
struct Treap {
  using T = ll;

  // Implementation

  struct Node {
    T v = 0;
    T v_acc = 0;
    int key;
    int priority;
    array<unique_ptr<Node>, 2> to = {};
  };
  using NodeP = unique_ptr<Node>;

  void pull(NodeP& t) {
    if (!t) { return; }
    t->v_acc = t->v;
    for (auto& p : t->to) {
      if (!p) { continue; }
      t->v_acc += p->v_acc;
    }
  }

  void split(NodeP t, NodeP& res_l, NodeP& res_r, int q_key) {
    if (!t) { return; }
    if (q_key <= t->key) {
      split(move(t->to[0]), res_l, t->to[0], q_key);
      pull(t);
      res_r = move(t);
    } else {
      split(move(t->to[1]), t->to[1], res_r, q_key);
      pull(t);
      res_l = move(t);
    }
  }

  void merge(NodeP tl, NodeP tr, NodeP& res) {
    if (!tl || !tr) { res = move(tl ? tl : tr); return; }
    if (tl->priority < tr->priority) {
      merge(move(tl->to[1]), move(tr), tl->to[1]);
      res = move(tl);
    } else {
      merge(move(tl), move(tr->to[0]), tr->to[0]);
      res = move(tr);
    }
    pull(res);
  }

  // Interface

  NodeP root;

  template<class FuncT>
  void split3(int l, int r, FuncT f) {
    NodeP x, y, z, yz;
    split(move(root), x, yz, l);
    split(move(yz), y, z, r);
    f(x, y, z);
    merge(move(y), move(z), yz);
    merge(move(x), move(yz), root);
  }

  void insert(int i, T v) {
    split3(i, i + 1, [&](auto&, auto& y, auto&) {
      if (y) {
        y->v += v;
      } else {
        y = make_unique<Node>();
        y->key = i;
        y->v = v;
        y->priority = rng();
      }
      pull(y);
    });
  }

  T reduce(int l, int r) {
    T res = 0;
    split3(l, r, [&](auto&, auto& y, auto&) {
      if (y) { res = y->v_acc; }
    });
    return res;
  }
};

// 2D segment tree with treap for inner dimention
struct SegmentTree {
  using T = ll;

  struct Node {
    Treap v;
    array<unique_ptr<Node>, 2> to = {};
  };
  using NodeP = unique_ptr<Node>;

  NodeP root;
  int root_l = 0;
  int root_r = 1 << 30;

  void incr(int qi, int qj, T qv) {
    // [ Recursive ]
    function<void(int, int, NodeP&)> rec = [&](int l, int r, NodeP& t) {
      if (r <= qi || qi < l) { return; }
      if (!t) { t = make_unique<Node>(); }
      dbg(l, r, qj, qv);
      t->v.insert(qj, qv);
      int m = (l + r) / 2;
      if (l == m) { return; }
      rec(l, m, t->to[0]);
      rec(m, r, t->to[1]);
    };
    rec(root_l, root_r, root);

    // [ Iterative ]
    // NodeP* t = &root;
    // int l = root_l, r = root_r;
    // while (true) {
    //   if (!(*t)) { *t = make_unique<Node>(); }
    //   (*t)->v.insert(qj, qv);
    //   int m = (l + r) / 2;
    //   if (l == m) { break; }
    //   tie(l, r) = (qi >= m) ? make_tuple(m, r) : make_tuple(l, m);
    //   t = &(*t)->to[qi >= m];
    // }
  }

  T reduce(int qil, int qir, int qjl, int qjr) {
    function<T(int, int, NodeP&)> rec = [&](int l, int r, NodeP& t) -> T {
      if (!t) { return 0; }
      if (qir <= l || r <= qil) { return 0; }
      if (qil <= l && r <= qir) {
        dbg(l, r, qjl, qjr, t->v.reduce(qjl, qjr));
        return t->v.reduce(qjl, qjr);
      }
      int m = (l + r) / 2;
      return rec(l, m, t->to[0]) + rec(m, r, t->to[1]);
    };
    return rec(root_l, root_r, root);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<array<int, 3>> ls(n); // [0, 10^9]
  vector<array<int, 4>> qs(nq);
  cin >> ls >> qs;

  SegmentTree tree;
  for (auto [x, y, w] : ls) {
    tree.incr(x, y, w);
  }

  for (auto [x0, y0, x1, y1] : qs) {
    auto res = tree.reduce(x0, x1, y0, y1);
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/rectangle_sum/main_v4.cpp

%%%% begin
4 1
1 2 2
2 0 0
2 2 2
2 1 1
1 0 4 4
%%%%
5
%%%% end

%%%% begin
5 5
0 0 1
3 0 10
1 4 100
2 2 1000
3 2 10000
0 0 4 5
0 0 4 4
3 0 4 3
2 0 4 3
1 2 2 4
%%%%
11111
11011
10010
11010
0
%%%% end
*/
