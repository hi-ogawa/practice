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

// RNG for treap priority
auto rng = mt19937(0x12345678);

// Treap
struct Treap {
  using T = ll;

  struct Node {
    T v, v_acc;
    int cnt;
    ull priority;
    Node* l = nullptr, * r = nullptr;

    Node(T v) : v{v}, priority{rng()} { pull(); }

    ~Node() { for (auto p : {l, r}) { if (p) { delete p; } } }

    void pull() {
      cnt = 1;
      v_acc = v;
      for (auto p : {l, r}) {
        if (!p) { continue; }
        cnt += p->cnt;
        v_acc += p->v_acc;
      }
    }
  };

  Node* join(Node* tl, Node* tr) {
    if (!tl || !tr) { return tl ? tl : tr; }
    Node* res;
    if (tl->priority < tr->priority) {
      tl->r = join(tl->r, tr);
      res = tl;
    } else {
      tr->l = join(tl, tr->l);
      res = tr;
    }
    res->pull();
    return res;
  }

  pair<Node*, Node*> split(Node* t, int q_key, int tmp_key = 0) {
    if (!t) { return {}; }
    pair<Node*, Node*> res = {};
    int t_key = tmp_key + (t->l ? t->l->cnt : 0);
    if (q_key <= t_key) {
      tie(res.first, t->l) = split(t->l, q_key, tmp_key);
      res.second = t;
    } else {
      tie(t->r, res.second) = split(t->r, q_key, t_key + 1);
      res.first = t;
    }
    t->pull();
    return res;
  }

  Node* root = nullptr;
  ~Treap() { if (root) { delete root; } }

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
  vector<ll> ls(n); // [0, 10^9]
  cin >> ls;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  Treap treap;
  FOR(i, 0, n) { treap.insert(i, ls[i]); }

  for (auto [t, x, y] : qs) {
    if (t == 0) {
      treap.incr(x, y);
    }
    if (t == 1) {
      auto res = treap.reduce(x, y);
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
python misc/run.py library_checker/point_add_range_sum/main_v3.cpp

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
