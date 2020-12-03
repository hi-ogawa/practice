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

// Printing 128 bit integer
namespace std {
  ostream& operator<<(ostream& ostr, __int128 x) {
    if (x == 0) { return ostr << 0; }
    bool neg = x < 0;
    if (neg) { x = -x; }
    string res;
    while (x > 0) {
      res += (x % 10) + '0';
      x /= 10;
    }
    reverse(ALL(res));
    return ostr << (neg ? "-" : "") << res;
  }
}

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

// Li Chao tree (cf. library_checker/line_add_get_min/main_v2.cpp)
struct LiChaoTree {
  using T = __int128;
  static inline T inf = T(1) << 120;
  using vec2 = array<T, 2>;
  static T value(vec2 f, T x) { return f[0] * x + f[1]; }

  // Maximum mode
  static inline T init = -inf;
  static bool compare(T lhs, T rhs) { return lhs > rhs; }
  static T join(T lhs, T rhs) { return compare(lhs, rhs) ? lhs : rhs; }

  struct Node {
    vec2 data = {0, init};
    array<unique_ptr<Node>, 2> to = {};
  };

  unique_ptr<Node> root;
  static inline T root_l = 0;
  static inline T root_r = 1 << 20;

  void insert(vec2 f) {
    y_combinator([&](auto rec, T l, T r, unique_ptr<Node>& node) -> void {
      if (!node) {
        node = make_unique<Node>();
        node->data = f;
        return;
      }
      T m = l + (r - l) / 2;
      bool comp_l = compare(value(f, l), value(node->data, l));
      bool comp_m = compare(value(f, m), value(node->data, m));
      if (comp_m) { swap(node->data, f); }
      if (l == m) { return; }
      if (comp_l != comp_m) {
        rec(l, m, node->to[0]);
      } else {
        rec(m, r, node->to[1]);
      }
    })(root_l, root_r, root);
  }

  T evaluate(T x) {
    return y_combinator([&](auto rec, T l, T r, unique_ptr<Node>& node) -> T {
      if (!node) { return init; }
      if (x < l || r <= x) { return init; }
      T res = value(node->data, x);
      T m = l + (r - l) / 2;
      if (l == m) { return res; }
      if (x < m) {
        res = join(res, rec(l, m, node->to[0]));
      } else       {
        res = join(res, rec(m, r, node->to[1]));
      }
      return res;
    })(root_l, root_r, root);
  }
};


// Main
void mainCase() {
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> xs(n); // [-10^7, 10^7]
  cin >> xs;

  // We solve the reversed problem since it goes better with usual cumsum ordering.
  //  x(1), x(2)   ..., x(k)
  //  k,    (k-1)  ..., 1
  reverse(ALL(xs));

  vector<__int128> ys(n + 1); // Cum sum        y(i) = x0 + x1 + ... + x(i-1)
  vector<__int128> zs(n + 1); // Sum of cum sum z(i) = ...
  FOR(i, 0, n) {
    ys[i + 1] = ys[i] + xs[i];
    zs[i + 1] = zs[i] + ys[i + 1];
  }
  dbg(xs);
  dbg(ys);
  dbg(zs);

  //
  // DEF.
  //   f(i, j) = 1 x(i) + 2 x(i+1) + ... + (j - i + 1) x(j - 1)
  //           = z(j) - z(i) - y(i) (j - i)
  //
  //   g(j)    = max_{i < j} f(i, j)
  //           = (max - y(i) * j + y(i) * i - z(i)) + z(j)
  //

  LiChaoTree tree;

  vector<__int128> g(n + 1);
  FOR(j, 0, n) {
    tree.insert({- ys[j], ys[j] * j - zs[j]});
    g[j + 1] = tree.evaluate(j + 1) + zs[j + 1];
  }
  dbg(g);

  ll res = *max_element(ALL(g));
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/660F/main.cpp

%%%% begin
6
5 -1000 1 -3 7 -8
%%%%
16
%%%% end

%%%% begin
5
1000 1000 1001 1000 1000
%%%%
15003
%%%% end

%%%% begin
3
-60 -70 -80
%%%%
0
%%%% end
*/
