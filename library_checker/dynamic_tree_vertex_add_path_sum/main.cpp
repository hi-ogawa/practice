// AC

// TODO: Prove amortized complexity bound

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

struct LinkCutTree {
  using T = ll;

  //
  // Splay tree implementation with slight modification to support path parent
  //

  struct Node {
    T v, v_sum;
    array<Node*, 2> to = {};
    Node* p = nullptr;
    int rev = 0;
    Node* p_path = nullptr; // [ Link-Cut tree ]

    Node(T _v) : v{_v} { pull(); }

    int side() { assert(p); return p->to[1] == this; }

    void pull() {
      v_sum = v;
      for (auto x : to) {
        if (!x) { continue; }
        v_sum += x->v_sum;
      }
    }

    void push() {
      if (!rev) { return; }
      swap(to[0], to[1]);
      for (auto x : to) { if (x) { x->rev ^= 1; } }
      rev = 0;
    }

    void set(T _v) { v = _v; pull(); }
  };

  void setChild(Node* p, Node* t, int i) {
    if (p) { p->to[i] = t; p->pull(); }
    if (t) { t->p = p; }
  }

  void unsetChild(Node* p, int i) {
    setChild(nullptr, p->to[i], -1);
    setChild(p, nullptr, i);
  }

  void rotate(Node* t) {
    assert(t && t->p);
    auto p = t->p;
    auto g = p->p;
    int i = t->side();
    int j = g && p->side();
    setChild(p, t->to[!i], i);
    setChild(t, p,        !i);
    setChild(g, t,         j);
    t->p_path = p->p_path;  // [ Link-Cut tree ]
    p->p_path = nullptr;
  }

  void splay(Node* t) {
    assert(t);
    // Push down to the node "t"
    function<void(Node*)> rec = [&](Node* t) {
      if (t->p) { rec(t->p); }
      t->push();
    };
    rec(t);
    // Usual splay
    while (t->p) {
      rotate((t->p->p && t->side() == t->p->side()) ? t->p : t);
    }
  }

  void print(Node* t) {
    string pos;
    auto pad [[gnu::unused]] = [](const string& s) {
      const int l = 6;
      return s + string(max(0, l - (int)s.size()), '-');
    };
    function<void(Node*)> rec = [&](Node* t) {
      if (!t) { return; }
      pos.push_back('L');
      rec(t->to[0]);
      pos.pop_back();
      dbg(pad(pos), t, t->v, t->v_sum, t->p_path, t->rev); // pre-order
      pos.push_back('R');
      rec(t->to[1]);
      pos.pop_back();
    };
    rec(t);
  }

  //
  // Link-Cut tree implementation
  //

  //  [p]            [p]
  //    \              \
  //   (p_path)  <=>  (to[1])
  //      \              \
  //      [t]            [t]

  void setPath(Node* p, Node* t) {
    assert(!p->p);
    assert(!p->to[1]);
    assert(p == t->p_path);
    setChild(p, t, 1);
    t->p_path = nullptr;
  }

  void clearPath(Node* p) {
    assert(!p->p);
    auto t = p->to[1];
    if (!t) { return; }
    assert(t->p_path == nullptr);
    unsetChild(p, 1);
    t->p_path = p;
  }

  Node* access(Node* t) {
    splay(t);
    clearPath(t);
    auto last = t;
    while (t->p_path) {
      last = t->p_path;
      splay(t->p_path);
      clearPath(t->p_path);
      setPath(t->p_path, t);
      splay(t);
    }
    return last;
  }

  void reroot(Node* t) {
    access(t);
    t->rev ^= 1;
    t->push();
  }

  void link(Node* x, Node* y) {
    access(x);
    reroot(y);
    assert(!x->to[1]);
    assert(!y->to[0] && !y->p && !y->p_path);
    setChild(x, y, 1);
  }

  void cut(Node* x, Node* y) {
    reroot(x);
    access(y);
    assert(x == y->to[0]);
    unsetChild(y, 0);
  }

  T reduce(Node* x, Node* y) {
    reroot(x);
    access(y);
    return y->v_sum;
  }

  // Not used
  Node* lca(Node* x, Node* y) {
    access(x);
    return access(y);
  }

  //
  // Link-Cut tree interface
  //

  vector<Node> nodes;
  LinkCutTree(int n) : nodes(n, Node(0)) {}

  void printAll() {
    dbg("========");
    FOR(i, 0, nodes.size()) {
      dbg(i, &nodes[i]);
      if (nodes[i].p) { continue; }
      print(&nodes[i]);
    }
  }

  void set(int x, T v) {
    access(&nodes[x]);
    nodes[x].set(v);
  }

  void link(int x, int y) {
    link(&nodes[x], &nodes[y]);
  }

  void cut(int x, int y) {
    cut(&nodes[x], &nodes[y]);
  }

  T reduce(int x, int y) {
    return reduce(&nodes[x], &nodes[y]);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<ll> ls(n); // [0, 10^9]
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  LinkCutTree tree(n);
  FOR(i, 0, n) {
    tree.set(i, ls[i]);
  }

  for (auto [x, y] : edges) {
    tree.link(x, y);
  }

  FOR(i, 0, nq) {
    int t;
    cin >> t;
    // dbg(i, t);
    // tree.printAll();
    if (t == 0) {
      int u1, v1, u2, v2;
      cin >> u1 >> v1 >> u2 >> v2;
      tree.cut(u1, v1);
      tree.link(u2, v2);
    }
    if (t == 1) {
      int x, y;
      cin >> x >> y;
      tree.set(x, ls[x] += y);
    }
    if (t == 2) {
      int u, v;
      cin >> u >> v;
      auto res = tree.reduce(u, v);
      cout << res << "\n";
    }
  }
  // tree.printAll();
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/dynamic_tree_vertex_add_path_sum/main.cpp

%%%% begin
4 1
1 10 100 1000
1 0
2 1
3 2
0 1 0 2 0
%%%%
%%%% end

%%%% begin
5 7
1 10 100 1000 10000
0 1
1 2
2 3
1 4
2 0 3
1 1 100000
2 3 4
0 1 2 2 0
2 3 4
0 2 3 3 1
2 2 3
%%%%
1111
111110
111111
101111
%%%% end
*/
