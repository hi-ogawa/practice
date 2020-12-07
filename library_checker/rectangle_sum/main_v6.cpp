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
  struct Node;
  using NodeP = unique_ptr<Node>;

  struct Node {
    T data;
    array<NodeP, 2> to = {};
  };

  NodeP root;
  int root_l = 0, root_r = 1 << 30;

  void incr(int qi, T qv) {
    function<T(int, int, NodeP&)> rec = [&](int l, int r, NodeP& t) -> T {
      if (qi < l || r <= qi) { return t ? t->data : 0; }
      if (!t) { t = make_unique<Node>(); }
      if (l + 1 == r) { return t->data += qv; }
      int m = (l + r) / 2;
      return t->data = rec(l, m, t->to[0]) + rec(m, r, t->to[1]);
    };
    rec(root_l, root_r, root);
  }

  T reduce(int ql, int qr) {
    function<T(int, int, NodeP&)> rec = [&](int l, int r, NodeP& t) -> T {
      if (!t) { return 0; }
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return t->data; }
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

  vector<array<int, 6>> events; // (x, point/rect-left/rect-right, y0, y1, weight, query-id)

  for (auto [x, y, w] : ls) {
    events.push_back({x, 0, y, -1, w, -1});
  }
  FOR(i, 0, nq) {
    auto [x0, y0, x1, y1] = qs[i];
    events.push_back({x0 - 1, 1, y0, y1, -1, i});
    events.push_back({x1 - 1, 2, y0, y1, -1, i});
  }
  sort(ALL(events));

  vector<ll> res(nq);
  SegmentTree tree;

  for (auto [x, t, y0, y1, w, i] : events) {
    if (t == 0) {
      dbg(t, x, y0, w);
      tree.incr(y0, w);
    }
    if (t == 1) {
      dbg(t, x, y0, y1, i);
      res[i] -= tree.reduce(y0, y1);
    }
    if (t == 2) {
      dbg(t, x, y0, y1, i);
      res[i] += tree.reduce(y0, y1);
    }
  }

  FOR(i, 0, nq) {
    cout << res[i] << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/rectangle_sum/main_v6.cpp

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
