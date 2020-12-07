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

// 2D segment tree
struct SegmentTree {
  using T = ll;

  struct Node;
  using NodeP = unique_ptr<Node>;

  struct Node {
    vector<pair<int, T>> data;
    vector<T> data_acc;
    array<unique_ptr<Node>, 2> to = {};

    void init() {
      for (auto& p : to) { if (p) { p->init(); } }

      if (!data.empty()) {
        // Leaf case
        sort(ALL(data));
      } else {
        // Merge sort
        vector<pair<int, T>> d0, d1;
        if (to[0]) { d0 = to[0]->data; }
        if (to[1]) { d1 = to[1]->data; }
        int n0 = d0.size(), n1 = d1.size();
        data.resize(n0 + n1);
        int i = 0, i0 = 0, i1 = 0;
        while (i0 < n0 || i1 < n1) {
          if (i0 == n0) { data[i++] = d1[i1++]; continue; }
          if (i1 == n1) { data[i++] = d0[i0++]; continue; }
          if (d0[i0].first < d1[i1].first) {
            data[i++] = d0[i0++];
          } else {
            data[i++] = d1[i1++];
          }
        }
      }

      // Cum sum
      int n = data.size();
      data_acc.resize(n + 1);
      FOR(j, 0, n) {
        data_acc[j + 1] = data_acc[j] + data[j].second;
      }
    }

    T reduce(int ql, int qr) {
      auto itl = lower_bound(ALL(data), pair<int, T>{ql, 0});
      auto itr = lower_bound(ALL(data), pair<int, T>{qr, 0});
      int il = distance(data.begin(), itl);
      int ir = distance(data.begin(), itr);
      return data_acc[ir] - data_acc[il];
    }
  };

  NodeP root;
  int root_l = 0;
  int root_r = 1 << 30;

  void incr(int qi, int qj, T qv) {
    function<void(int, int, NodeP&)> rec = [&](int l, int r, NodeP& t) {
      if (r <= qi || qi < l) { return; }
      if (!t) { t = make_unique<Node>(); }
      if (l + 1 == r) { t->data.push_back({qj, qv}); return; }
      int m = (l + r) / 2;
      rec(l, m, t->to[0]);
      rec(m, r, t->to[1]);
    };
    rec(root_l, root_r, root);
  }

  void init() { if (root) { root->init(); } }

  T reduce(int qil, int qir, int qjl, int qjr) {
    function<T(int, int, NodeP&)> rec = [&](int l, int r, NodeP& t) -> T {
      if (!t) { return 0; }
      if (qir <= l || r <= qil) { return 0; }
      if (qil <= l && r <= qir) {
        return t->reduce(qjl, qjr);
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
  tree.init();

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
python misc/run.py library_checker/rectangle_sum/main_v5.cpp

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
