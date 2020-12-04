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

struct Treap {
  using T = int;

  struct Node;
  using NodeP = unique_ptr<Node>; // too much "move" is just too sketchy...

  struct Node {
    T v;
    array<NodeP, 2> to = {};
    int priority;
    int cnt = 1;
    int rev = 0;
  };

  static int cnt(NodeP& t) { return t ? t->cnt : 0; }
  static void updateCount(NodeP& t) { t->cnt = 1 + cnt(t->to[0]) + cnt(t->to[1]); }
  static void updateReverse(NodeP& t) {
    if (t->rev) {
      swap(t->to[0], t->to[1]);
      if (t->to[0]) { t->to[0]->rev ^= 1; }
      if (t->to[1]) { t->to[1]->rev ^= 1; }
      t->rev = 0;
    }
  }

  static void split(NodeP t, int q_key, NodeP& res_l, NodeP& res_r, int key = 0) {
    if (!t) { return; }
    updateReverse(t);
    int t_key = key + cnt(t->to[0]);
    if (q_key < t_key) {
      split(move(t->to[0]), q_key, res_l, t->to[0], key);
      res_r = move(t);
      updateCount(res_r);
    } else {
      split(move(t->to[1]), q_key, t->to[1], res_r, t_key + 1);
      res_l = move(t);
      updateCount(res_l);
    }
  }

  static void merge(NodeP tl, NodeP tr, NodeP& res) {
    if (!tl || !tr) { res = move(tl ? tl : tr); return; }
    if (tl->priority < tr->priority) {
      updateReverse(tl);
      merge(move(tl->to[1]), move(tr), tl->to[1]);
      res = move(tl);
    } else {
      updateReverse(tr);
      merge(move(tl), move(tr->to[0]), tr->to[0]);
      res = move(tr);
    }
    updateCount(res);
  }

  static void insert(NodeP& t, NodeP& s, int s_key, int key = 0) {
    if (!t) { t = move(s); return; }
    if (s->priority < t->priority) {
      split(move(t), s_key, s->to[0], s->to[1], key);
      t = move(s);
    } else {
      updateReverse(t);
      int t_key = key + cnt(t->to[0]);
      if (s_key < t_key) {
        insert(t->to[0], s, s_key, key);
      } else {
        insert(t->to[1], s, s_key, t_key + 1);
      }
    }
    updateCount(t);
  }

  static T find(NodeP& t, int q_key, int key = 0) {
    assert(t);
    updateReverse(t);
    int t_key = key + cnt(t->to[0]);
    if (q_key == t_key) { return t->v; }
    if (q_key < t_key) {
      return find(t->to[0], q_key, key);
    } else {
      return find(t->to[1], q_key, t_key + 1);
    }
  }

  static void toVector(NodeP& t, vector<T>& res) {
    if (!t) { return; }
    updateReverse(t);
    toVector(t->to[0], res);
    res.push_back(t->v);
    toVector(t->to[1], res);
  }

  static vector<T> toVector(NodeP& t) {
    vector<T> res;
    toVector(t, res);
    return res;
  }

  NodeP root;
  mt19937 rng;
  Treap() : rng{mt19937((ull)this)} {}

  vector<T> toVector() { return toVector(root); }

  void insert(int i, T v) {
    auto t = make_unique<Node>();
    t->v = v;
    t->priority = rng();
    insert(root, t, i);
  }

  void erase(int i) {
    NodeP x, y, z, w;
    split(move(root), i - 1, x, y);
    split(move(y)   , 0,     z, w);
    merge(move(x), move(w), root);
  }

  T find(int i) {
    return find(root, i);
  }

  void shift(int l, int r) {
    auto v = find(r - 1);
    erase(r - 1);
    insert(l - 1, v);
  }

  void reverse(int l, int r) {
    NodeP x, y, z, w;
    split(move(root), r - 1, x, w);
    split(move(x),    l - 1, y, z);
    assert(z);
    z->rev ^= 1;
    merge(move(y), move(z), x);
    merge(move(x), move(w), root);
  }
};

// Main
void mainCase() {
  int n, nq, m; // n, nq \in [1, 2 x 10^5], m \in [1, 100]
  cin >> n >> nq >> m;
  vector<int> ls(n); // [1, 10^9]
  vector<array<int, 3>> qs(nq);
  vector<int> xs(m);
  cin >> ls >> qs >> xs;

  Treap treap;
  FOR(i, 0, n) {
    treap.insert(i, ls[i]);
  }

  for (auto [t, l, r] : qs) {
    l--;
    dbg(treap.toVector());
    dbg(t, l, r);
    if (t == 1) {
      treap.shift(l, r);
    }
    if (t == 2) {
      treap.reverse(l, r);
    }
  }
  dbg(treap.toVector());

  FOR(i, 0, m) {
    auto res = treap.find(xs[i] - 1);
    cout << res << " \n"[i == m - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/863D/main.cpp

%%%% begin
6 3 5
1 2 3 4 5 6
2 1 3
2 3 6
1 1 6
2 2 1 5 3
%%%%
3 3 1 5 2
%%%% end
*/
