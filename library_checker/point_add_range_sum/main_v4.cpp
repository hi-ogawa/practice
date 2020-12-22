// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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

// Splay tree
struct SplayTree {
  using T = ll;

  struct Node {
    T v, v_acc;
    int cnt;
    array<Node*, 2> to = {};
    Node* p = nullptr;

    Node(T v) : v{v} { pull(); }

    ~Node() { for (auto x : to) { if (x) { delete x; } } }

    void pull() {
      cnt = 1;
      v_acc = v;
      for (auto x : to) {
        if (!x) { continue; }
        cnt += x->cnt;
        v_acc += x->v_acc;
      }
    }

    int side() { assert(p); return p->to[1] == this; }
  };

  void setChild(Node* p, Node* t, int c) {
    if (p) { p->to[c] = t; }
    if (t) { t->p = p; }
  }

  void rotate(Node* t) {
    assert(t && t->p);
    int c = t->side();
    auto p = t->p;
    setChild(p->p, t, p->p && p->side());
    setChild(p, t->to[!c], c);
    setChild(t, p, !c);
    p->pull();
    t->pull();
  }

  void splay(Node* t) {
    assert(t);
    while (t->p) {
      rotate((t->p->p && t->side() == t->p->side()) ? t->p : t);
    }
  }

  Node* maximum(Node* t) {
    assert(t);
    while (t->to[1]) { t = t->to[1]; }
    return t;
  }

  Node* lowerBound(Node* t, int q_key, int tmp_key = 0) {
    if (!t) { return nullptr; }
    int t_key = tmp_key + (t->to[0] ? t->to[0]->cnt : 0);
    if (q_key <= t_key) {
      auto res = lowerBound(t->to[0], q_key, tmp_key);
      return res ? res : t;
    }
    return lowerBound(t->to[1], q_key, t_key + 1);
  }

  Node* join(Node* tl, Node* tr) {
    if (!tl) { return tr; }
    auto s = maximum(tl);
    splay(s);
    assert(!s->to[1]);
    setChild(s, tr, 1);
    s->pull();
    return s;
  }

  pair<Node*, Node*> split(Node* t, int key) {
    if (!t) { return {}; }
    auto s = lowerBound(t, key);
    if (!s) { return {t, nullptr}; }
    splay(s);
    auto u = s->to[0];
    if (u) { s->to[0] = u->p = nullptr; }
    s->pull();
    return {u, s};
  }

  Node* root = nullptr;
  ~SplayTree() { if (root) { delete root; } }

  template<class F>
  void split3(int l, int r, F f) {
    Node* x, * y, * z, * yz;
    tie(x, yz) = split(root, l);
    tie(y, z) = split(yz, r - l);
    f(x, y, z);
    yz = join(y, z);
    root = join(x, yz);
  }

  void insert(int qi, T qv) {
    split3(qi, qi, [&](auto, auto& y, auto) {
      assert(!y);
      y = new Node(qv);
    });
  }

  void erase(int qi) {
    split3(qi, qi + 1, [&](auto, auto& y, auto) {
      assert(y);
      delete y;
      y = nullptr;
    });
  }

  void incr(int qi, T qv) {
    split3(qi, qi + 1, [&](auto, auto& y, auto) {
      assert(y);
      y->v += qv;
      y->pull();
    });
  }

  T reduce(int ql, int qr) {
    T res = 0;
    split3(ql, qr, [&](auto, auto& y, auto) {
      assert(y);
      res = y->v_acc;
    });
    return res;
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 5 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [0, 10^9]
  cin >> ls;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  SplayTree tree;
  FOR(i, 0, n) { tree.insert(i, ls[i]); }

  for (auto [t, x, y] : qs) {
    if (t == 0) {
      tree.incr(x, y);
    }
    if (t == 1) {
      auto res = tree.reduce(x, y);
      cout << res << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/point_add_range_sum/main_v4.cpp

%%%% begin
5 5
1 2 3 4 5
1 0 5
1 2 4
0 3 10
1 0 5
1 0 3
%%%%
15
7
25
6
%%%% end
*/
