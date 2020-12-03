// MLE

// NOTE: 2D dynamic segment tree. It doesn't work for this problem, but the implementation is working.

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

// 2D dynamic segment tree
struct SegmentTree {
  using T = ll;
  static inline T zero = 0;
  static T join(T lhs, T rhs) { return lhs + rhs; }

  struct Node {
    T data = zero;
    array<array<int, 2>, 2> to = {}; // {{row-up, row-down}, {col-left, col-right}}
  };

  int n = 2, n_max; // default = 0, root = 1;
  vector<Node> nodes;
  static inline int root_l = 0;
  static inline int root_r = 1 << 20;
  static inline int root_t = 1;

  SegmentTree(int nq) : n_max{nq * 20 * 20 + 2} {
    nodes.resize(n_max);
  }

  void incr(int qi, int qj, T qv) {
    auto rec_col = y_combinator([&](auto rec_col, int jl, int jr, int& t) -> T {
      if (qj < jl || jr <= qj) { return nodes[t].data; }
      if (t == 0) { t = n++; assert(n <= n_max); } // Allocate new node
      if (jl + 1 == jr) { return nodes[t].data += qv; }
      int jm = (jl + jr) / 2;
      T res = zero;
      res = join(res, rec_col(jl, jm, nodes[t].to[1][0]));
      res = join(res, rec_col(jm, jr, nodes[t].to[1][1]));
      return nodes[t].data = res;
    });

    auto rec_row = y_combinator([&](auto rec_row, int il, int ir, int& t) -> void {
      if (qi < il || ir <= qi) { return; }
      if (t == 0) { t = n++; assert(n <= n_max); } // Allocate new node
      rec_col(root_l, root_r, t);
      if (il + 1 == ir) { return; }
      int im = (il + ir) / 2;
      rec_row(il, im, nodes[t].to[0][0]);
      rec_row(im, ir, nodes[t].to[0][1]);
    });

    rec_row(root_l, root_r, root_t);
  }

  T reduce(int qil, int qir, int qjl, int qjr) {
    auto rec = y_combinator([&](auto rec, int il, int ir, int jl, int jr, int t) -> T {
      if (t == 0) { return zero; } // Skip default empty node
      if (qir <= il || ir <= qil) { return zero; }
      if (qil <= il && ir <= qir) {
        if (qjr <= jl || jr <= qjl) { return zero; }
        if (qjl <= jl && jr <= qjr) { return nodes[t].data; }
        int jm = (jl + jr) / 2;
        T jres = zero;
        jres = join(jres, rec(il, ir, jl, jm, nodes[t].to[1][0]));
        jres = join(jres, rec(il, ir, jm, jr, nodes[t].to[1][1]));
        return jres;
      }
      int im = (il + ir) / 2;
      T ires = zero;
      ires = join(ires, rec(il, im, jl, jr, nodes[t].to[0][0]));
      ires = join(ires, rec(im, ir, jl, jr, nodes[t].to[0][1]));
      return ires;
    });
    return rec(root_l, root_r, root_l, root_r, root_t);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<array<int, 3>> ls(n); // [0, 10^9]
  vector<array<int, 4>> qs(nq);
  cin >> ls >> qs;

  // Compress coordinates
  vector<int> xs, ys;
  for (auto [x, y, w] : ls) {
    xs.push_back(x);
    ys.push_back(y);
  }
  for (auto [x0, y0, x1, y1] : qs) {
    xs.push_back(x0);
    xs.push_back(x1);
    ys.push_back(y0);
    ys.push_back(y1);
  }
  sort(ALL(xs));
  sort(ALL(ys));
  xs.erase(unique(ALL(xs)), xs.end());
  ys.erase(unique(ALL(ys)), ys.end());
  for (auto& [x, y, w] : ls) {
    x = distance(xs.begin(), lower_bound(ALL(xs), x));
    y = distance(ys.begin(), lower_bound(ALL(ys), y));
  }
  for (auto& [x0, y0, x1, y1] : qs) {
    x0 = distance(xs.begin(), lower_bound(ALL(xs), x0));
    x1 = distance(xs.begin(), lower_bound(ALL(xs), x1));
    y0 = distance(ys.begin(), lower_bound(ALL(ys), y0));
    y1 = distance(ys.begin(), lower_bound(ALL(ys), y1));
  }

  SegmentTree tree(n);
  for (auto [x, y, w] : ls) {
    assert(x < (1 << 20));
    assert(y < (1 << 20));
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
python misc/run.py library_checker/rectangle_sum/main_v3.cpp

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
