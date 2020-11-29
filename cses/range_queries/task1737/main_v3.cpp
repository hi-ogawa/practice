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

    void ensureChildren(int qi) {
      int m = (l + r) / 2;
      int side = m <= qi;
      auto& c = cs[side];
      if (c.use_count() == 0) { // Create node
        c = make_shared<Node>();
        c->l = side ? m : l;
        c->r = side ? r : m;
        return;
      }
      if (c.use_count() >= 2) { // Copy node
        c = make_shared<Node>(*c);
        return;
      }
    }

    void set(int qi, T qv) {
      if (qi < l || r <= qi) { return; }
      if (l + 1 == r) { data = qv; return; } // Leaf case
      ensureChildren(qi);
      T res = 0;
      FOR(i, 0, 2) {
        if (cs[i]) {
          cs[i]->set(qi, qv);
          res += cs[i]->data;
        }
      }
      data = res;
    }

    T reduce(int ql, int qr) {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return data; }
      T res = 0;
      FOR(i, 0, 2) {
        if (cs[i]) {
          res += cs[i]->reduce(ql, qr);
        }
      }
      return res;
    }
  };

  Node root;

  SegmentTree(int n_orig) {
    while (n < n_orig) { n *= 2; }
    root.l = 0;
    root.r = n;
  }

  void set(int qi, T qv) {
    root.set(qi, qv);
  }

  T reduce(int ql, int qr) {
    return root.reduce(ql, qr);
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
      // Default copy constructor works!
      trees.push_back(trees[k]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/range_queries/task1737/main_v3.cpp

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
