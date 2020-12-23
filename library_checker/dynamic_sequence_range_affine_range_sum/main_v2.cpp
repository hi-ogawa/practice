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

// Modulo integer
template<ll Modulo>
struct ModInt {
  using mint = ModInt;
  static constexpr ll modulo = Modulo;
  uint32_t v;
  ModInt() : v{0} {}
  template<class T, class = enable_if_t<is_integral_v<T>>>
  ModInt(T x) { ll y = (ll)x % modulo; if (y < 0) { y += modulo; } v = y; }
  friend istream& operator>>(istream& istr,       mint& self) { return istr >> self.v; }
  friend ostream& operator<<(ostream& ostr, const mint& self) { return ostr << self.v; }
  mint& operator+=(const mint& y) { v += y.v; while (v >= modulo) { v -= modulo; }; return *this; }
  mint& operator-=(const mint& y) { return *this += (modulo - y.v); }
  mint& operator*=(const mint& y) { v = (ll)v * y.v % modulo; return *this; }
  mint& operator/=(const mint& y) { return *this *= y.inv(); }
  friend mint operator+(const mint& x, const mint& y) { return mint(x) += y; }
  friend mint operator-(const mint& x, const mint& y) { return mint(x) -= y; }
  friend mint operator*(const mint& x, const mint& y) { return mint(x) *= y; }
  friend mint operator/(const mint& x, const mint& y) { return mint(x) /= y; }
  friend bool operator==(const mint& x, const mint& y) { return x.v == y.v; }
  friend bool operator!=(const mint& x, const mint& y) { return x.v != y.v; }
  mint operator-() const { return mint() - *this; }
  mint inv() const { return pow(modulo - 2); }
  mint pow(ll e) const {
    mint x = *this, res = 1;
    while (e > 0) {
      if (e & 1) { res *= x; }
      e >>= 1; x *= x;
    }
    return res;
  }
};

const ll modulo = 998244353;
using mint = ModInt<modulo>;

// Splay tree
struct SplayTree {
  using T = mint;

  struct Node {
    int cnt;
    array<Node*, 2> to = {};
    Node* p = nullptr;

    T v, v_acc;
    T a = 1, b = 0;
    int rev = 0;

    Node(T v) : v{v} { pull(); }

    int side() { assert(p); return p->to[1] == this; }

    void pull() {
      cnt = 1;
      v_acc = v;
      for (auto x : to) {
        if (!x) { continue; }
        cnt += x->cnt;
        v_acc += x->reduce();
      }
    }

    void push() {
      for (auto x : to) {
        if (!x) { continue; }
        x->rev ^= rev;
        x->affine(a, b);
      }
      if (rev) { swap(to[0], to[1]); }
      v = a * v + b;
      rev = 0;
      a = 1;
      b = 0;
      pull();
    }

    T reduce() { return a * v_acc + b * cnt; }

    void affine(T qa, T qb) {
      tie(a, b) = make_tuple(qa * a, qa * b + qb);
    }
  };

  void setChild(Node* p, Node* t, int i) {
    if (p) { p->to[i] = t; p->pull(); }
    if (t) { t->p = p; }
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
  }

  void splay(Node* t) {
    assert(t);
    while (t->p) {
      rotate((t->p->p && t->side() == t->p->side()) ? t->p : t);
    }
  }

  Node* maximum(Node* t) {
    assert(t);
    while (t->push(), t->to[1]) { t = t->to[1]; }
    return t;
  }

  Node* lowerBound(Node* t, int q_key, int tmp_key = 0) {
    if (!t) { return nullptr; }
    t->push();
    int t_key = tmp_key + (t->to[0] ? t->to[0]->cnt : 0);
    if (q_key <= t_key) {
      auto res = lowerBound(t->to[0], q_key, tmp_key);
      return res ? res : t;
    }
    return lowerBound(t->to[1], q_key, t_key + 1);
  }

  Node* join(Node* tl, Node* tr) {
    if (!tl) { return tr; }
    auto s = maximum(tl);
    splay(s);
    assert(!s->to[1]);
    setChild(s, tr, 1);
    return s;
  }

  pair<Node*, Node*> split(Node* t, int key) {
    if (!t) { return {}; }
    auto s = lowerBound(t, key);
    if (!s) { return {t, nullptr}; }
    splay(s);
    auto u = s->to[0];
    setChild(s, nullptr, 0);
    setChild(nullptr, u, -1);
    return {u, s};
  }

  void print(Node* t = nullptr, int order = 0) {
    dbg(t);
    string pos;
    auto pad [[gnu::unused]] = [](const string& s) {
      const int l = 6;
      return s + string(max(0, l - (int)s.size()), '-');
    };
    function<void(Node*)> rec = [&](Node* t) {
      if (!t) { return; }
      if (order == 0) { dbg(pad(pos), t->v, t->v_acc, t->a, t->b, t->rev); } // in-order
      pos.push_back('L');
      rec(t->to[0]);
      pos.pop_back();
      if (order == 1) { dbg(pad(pos), t->v, t->v_acc, t->a, t->b, t->rev); } // pre-order
      pos.push_back('R');
      rec(t->to[1]);
      pos.pop_back();
    };
    rec(t ? t : root);
  }

  Node* root = nullptr;
  ~SplayTree() {
    function<void(Node*)> rec = [&](Node* t) {
      if (!t) { return; }
      for (auto x : t->to) { rec(x); }
      delete t;
    };
    rec(root);
  }

  template<class F>
  void split3(int l, int r, F f) {
    Node* x, * y, * z, * yz;
    tie(x, yz) = split(root, l);
    tie(y, z) = split(yz, r - l);
    f(x, y, z);
    root = join(x, join(y, z));
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

  void reverse(int ql, int qr) {
    split3(ql, qr, [&](auto, auto& y, auto) {
      assert(y);
      y->rev ^= 1;
    });
  }

  void affine(int ql, int qr, T qa, T qb) {
    split3(ql, qr, [&](auto, auto& y, auto) {
      assert(y);
      y->affine(qa, qb);
    });
  }

  T reduce(int ql, int qr) {
    T res = 0;
    split3(ql, qr, [&](auto, auto& y, auto) {
      assert(y);
      res = y->reduce();
    });
    return res;
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 5 x 10^5]
  cin >> n >> nq;
  vector<mint> ls(n);
  cin >> ls;

  SplayTree tree;
  FOR(i, 0, n) { tree.insert(i, ls[i]); }

  FOR(iq, 0, nq) {
    int t, i, l, r;
    mint x, a, b;
    cin >> t;
    dbg(iq, t);
    if (t == 0) {
      cin >> i >> x;
      tree.insert(i, x);
    }
    if (t == 1) {
      cin >> i;
      tree.erase(i);
    }
    if (t == 2) {
      cin >> l >> r;
      tree.reverse(l, r);
    }
    if (t == 3) {
      cin >> l >> r >> a >> b;
      tree.affine(l, r, a, b);
    }
    if (t == 4) {
      cin >> l >> r;
      auto res = tree.reduce(l, r);
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
python misc/run.py library_checker/dynamic_sequence_range_affine_range_sum/main_v2.cpp

%%%% begin
5 2
3 3 4 3 0
3 0 4 4 6
4 1 3
%%%%
40
%%%% end

%%%% begin
8 2
0 5 0 0 5 3 3 7
3 4 7 3 3
4 2 8
%%%%
49
%%%% end

%%%% begin
5 2
4 0 2 4 0
3 2 5 1 1
4 2 5
%%%%
9
%%%% end

%%%% begin
5 6
1 10 100 1000 10000
4 1 4
0 2 100000
1 3
4 2 5
2 2 5
4 0 4
%%%%
1110
111000
11011
%%%% end
*/
