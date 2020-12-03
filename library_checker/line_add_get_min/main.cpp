// AC

// NOTE: Iterative version doesn't seem to be faster...

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

// Y combinator (cf. http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html)
template<class FuncT>
struct y_combinator_result {
  FuncT f;
  template<class T>
  explicit y_combinator_result(T&& f) : f{forward<T>(f)} {}
  template<class ...Ts>
  decltype(auto) operator()(Ts&& ...args) { return f(ref(*this), forward<Ts>(args)...); }
};

template<class FuncT>
decltype(auto) y_combinator(FuncT&& f) {
  return y_combinator_result<decay_t<FuncT>>(forward<FuncT>(f));
}

// Li Chao tree for minimum
struct LiChaoTree {
  using T = ll;
  using vec2 = array<T, 2>;
  static T value(vec2 f, T x) { return f[0] * x + f[1]; }
  static inline T inf = 1LL << 62;

  struct Node {
    vec2 data = {0, inf};
    array<int, 2> to = {};
  };

  vector<Node> nodes;
  int n = 2, n_max; // default = 0, root = 1;
  static inline T root_l = - (1 << 30);
  static inline T root_r = + (1 << 30);
  static inline int root_t = 1;

  LiChaoTree(int num_insert) : n_max{num_insert * 31 + 2} {
    nodes.resize(n_max);
  }

  void insert(vec2 f) {
    // [ Recursive ]
    // y_combinator([&](auto rec, T l, T r, int& t) -> void {
    //   if (t == 0) {
    //     t = n++; assert(n <= n_max);
    //     nodes[t].data = f;
    //     return;
    //   }
    //   T m = l + (r - l) / 2;
    //   T fl = value(f, l), gl = value(nodes[t].data, l);
    //   T fm = value(f, m), gm = value(nodes[t].data, m);
    //   if (fm < gm) { swap(nodes[t].data, f); }
    //   if (l == m) { return; }
    //   if (fl < gl != fm < gm) {
    //     rec(l, m, nodes[t].to[0]);
    //   } else {
    //     rec(m, r, nodes[t].to[1]);
    //   }
    // })(root_l, root_r, root_t);

    // [ Iterative ]
    T l = root_l, r = root_r;
    int t = root_t;
    while (true) {
      T m = l + (r - l) / 2;
      T fl = value(f, l), gl = value(nodes[t].data, l);
      T fm = value(f, m), gm = value(nodes[t].data, m);
      if (fm < gm) { swap(nodes[t].data, f); }
      if (l == m) { break; }
      int which = (fl < gl) == (fm < gm);
      tie(l, r) = which ? make_tuple(m, r) : make_tuple(l, m);
      int& t_next = nodes[t].to[which];
      if (t_next == 0) {
        t_next = n++; assert(n <= n_max);
        nodes[t_next].data = f;
        break;
      }
      t = t_next;
    }
  }

  T evaluate(T x) {
    // [ Recursive ]
    // return y_combinator([&](auto rec, T l, T r, int t) -> T {
    //   if (t == 0 || x < l || r <= x) { return inf; }
    //   T res = value(nodes[t].data, x);
    //   T m = l + (r - l) / 2;
    //   if (l == m) { return res; }
    //   if (x < m) {
    //     res = min(res, rec(l, m, nodes[t].to[0]));
    //   } else       {
    //     res = min(res, rec(m, r, nodes[t].to[1]));
    //   }
    //   return res;
    // })(root_l, root_r, root_t);

    // [ Iterative ]
    T res = inf;
    T l = root_l, r = root_r;
    int t = root_t;
    while (t != 0) {
      res = min(res, value(nodes[t].data, x));
      T m = l + (r - l) / 2;
      if (l == m) { break; }
      int which = m <= x;
      tie(l, r) = which ? make_tuple(m, r) : make_tuple(l, m);
      t = nodes[t].to[which];
    }
    return res;
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;

  LiChaoTree tree(n + nq);

  FOR(_, 0, n) {
    ll a, b; // a \in [-10^9, 10^9], b \in [-10^18, 10^18]
    cin >> a >> b;
    tree.insert({a, b});
  }

  FOR(_, 0, nq) {
    ll t;
    cin >> t;
    if (t == 0) {
      ll a, b;
      cin >> a >> b;
      tree.insert({a, b});
    }

    if (t == 1) {
      ll x; // x \in [-10^9, 10^9]
      cin >> x;
      auto y = tree.evaluate(x);
      cout << y << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/line_add_get_min/main.cpp

%%%% begin
2 8
-1 -1
0 1
1 -1
1 -2
1 0
1 2
0 0 -10
1 -2
1 0
1 2
%%%%
0
1
-1
-3
-10
-10
-10
%%%% end
*/
