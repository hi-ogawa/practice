// MLE

// NOTE: Use raw pointer instead of unique_ptr. but still MLE.

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

// Li Chao tree (cf. library_checker/line_add_get_min/main_v2.cpp)
// with small modification for persistence
struct LiChaoTree {
  using T = ll;
  using vec2 = array<T, 2>;
  static T value(vec2 f, T x) { return f[0] * x + f[1]; }
  static inline T inf = 1LL << 62;

  // Maximum mode
  static inline T init_value = -inf;
  static bool compare(T lhs, T rhs) { return lhs > rhs; }
  static T join(T lhs, T rhs) { return compare(lhs, rhs) ? lhs : rhs; }

  struct Node;
  using NodeP = Node*;
  struct Node {
    vec2 data = {0, init_value};
    array<NodeP, 2> to = {nullptr, nullptr};
    ~Node() { for (auto p : to) { if (p) { delete p; }}}
  };

  NodeP root = nullptr;
  static inline T root_l = - (1 << 30);
  static inline T root_r = + (1 << 30);

  // [ Persistence ]
  vector<tuple<int, NodeP*, NodeP*, vec2>> history; // (type, pointer, ...)
  vector<int> checkpoints;

  ~LiChaoTree() { if (root) { delete root; } }

  void insert(vec2 f) {
    function<void(T, T, NodeP&)> rec = [&](T l, T r, NodeP& t) {
      if (!t) {
        t = new Node();
        t->data = f;
        history.push_back({1, &t, nullptr, vec2()}); // [ Persistence ]
        return;
      }
      T m = l + (r - l) / 2;
      bool cl = compare(value(f, l), value(t->data, l));
      bool cm = compare(value(f, m), value(t->data, m));
      if (cm) {
        history.push_back({2, nullptr, &t, t->data}); // [ Persistence ]
        swap(t->data, f);
      }
      if (l == m) { return; }
      if (cl != cm) {
        rec(l, m, t->to[0]);
      } else {
        rec(m, r, t->to[1]);
      }
    };
    rec(root_l, root_r, root);
  }

  T evaluate(T x) {
    function<T(T, T, NodeP&)> rec = [&](T l, T r, NodeP& t) -> T {
      if (!t) { return init_value; }
      if (x < l || r <= x) { return init_value; }
      T res = value(t->data, x);
      T m = l + (r - l) / 2;
      if (l == m) { return res; }
      if (x < m) {
        res = join(res, rec(l, m, t->to[0]));
      } else {
        res = join(res, rec(m, r, t->to[1]));
      }
      return res;
    };
    return rec(root_l, root_r, root);
  }

  // [ Persistence ]
  void persist() {
    checkpoints.push_back(history.size());
  }

  void rollback() {
    int cp = checkpoints.back(); checkpoints.pop_back();
    while ((int)history.size() > cp) {
      auto [t, p1, p2, f] = history.back(); history.pop_back();
      if (t == 1) { assert(*p1); delete (*p1); *p1 = nullptr; }
      if (t == 2) { assert(*p2); (*p2)->data = f; }
    }
  }
};

// Cf. codeforces/edu/dsu/3/c/main.cpp
struct SegmentTree {
  using T = int;

  vector<vector<T>> data;
  int n = 1;

  SegmentTree(int n_orig) {
    while (n < n_orig) { n *= 2; }
    data.resize(2 * n);
  }

  // Split "qv" into power of two segments
  void insert(int ql, int qr, T qv) {
    function<void(int, int, int)> rec = [&](int l, int r, int j) {
      if (qr <= l || r <= ql) { return; }
      if (ql <= l && r <= qr) { data[j].push_back(qv); return; }
      int m = (l + r) / 2;
      rec(l, m, 2 * j);
      rec(m, r, 2 * j + 1);
    };
    rec(0, n, 1);
  }

  // DFS with callbacks
  template<class F1, class F2, class F3>
  void dfs(F1 f_in, F2 f_out, F3 f_leaf) {
    function<void(int, int, int)> rec = [&](int l, int r, int j) {
      f_in(data[j]);
      if (l + 1 == r) {
        f_leaf(l);
      } else {
        int m = (l + r) / 2;
        rec(l, m, 2 * j);
        rec(m, r, 2 * j + 1);
      }
      f_out();
    };
    rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int nq; // [1, 3 x 10^5]
  cin >> nq;
  vector<array<int, 3>> qs(nq);
  for (auto& [t, x, y] : qs) {
    cin >> t;
    if (t == 1) {
      cin >> x >> y; // [-10^9, 10^9]
    }
    if (t == 2) {
      cin >> x;
      x--; // [0, n)
    }
    if (t == 3) {
      cin >> x; // [-10^9, 10^9]
    }
  }

  LiChaoTree lichao;
  SegmentTree seg(nq);
  vector<ll> res(nq);

  // Check line's life span
  vector<int> times(nq, nq);
  FOR(i, 0, nq) {
    auto [t, x, y] = qs[i];
    if (t == 2) { times[x] = i; }
  }
  FOR(i, 0, nq) {
    auto [t, x, y] = qs[i];
    if (t == 1) {
      seg.insert(i, times[i], i);
    }
  }

  // DFS
  auto f_in = [&](const vector<int>& qids) {
    lichao.persist();
    for (auto i : qids) {
      auto [t, x, y] = qs[i];
      lichao.insert({x, y});
    }
  };
  auto f_out = [&]() {
    lichao.rollback();
  };
  auto f_leaf = [&](int i) {
    if (i >= nq) { return; }
    auto [t, x, y] = qs[i];
    if (t == 3) {
      res[i] = lichao.evaluate(x);
    }
  };
  seg.dfs(f_in, f_out, f_leaf);

  FOR(i, 0, nq) {
    auto [t, x, y] = qs[i];
    if (t == 3) {
      auto z = res[i];
      cout << (z == LiChaoTree::init_value ? "EMPTY SET" : to_string(z)) << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/678F/main_v2.cpp

%%%% begin
7
3 1
1 2 3
3 1
1 -1 100
3 1
2 4
3 1
%%%%
EMPTY SET
5
99
5
%%%% end
*/
