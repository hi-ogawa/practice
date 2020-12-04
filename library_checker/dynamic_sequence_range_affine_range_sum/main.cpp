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

// Treap
struct Treap {
  using T = mint;

  //
  // Treap implementation
  //

  struct Node {
    T v = 0;
    T v_acc = 0;
    T a = 1;
    T b = 0;
    int cnt = 1;
    int rev = 0;
    int priority = 0;
    array<unique_ptr<Node>, 2> to = {};
    T value() { return a * v_acc + cnt * b; }
    void combine(T pa, T pb) { tie(a, b) = make_tuple(pa * a, pa * b + pb); }
  };
  using NodeP = unique_ptr<Node>;

  int cnt(NodeP& t) { return t ? t->cnt : 0; }

  void push(NodeP& t) {
    if (t->rev) { swap(t->to[0], t->to[1]); }
    for (auto& p : t->to) {
      if (p) {
        p->rev ^= t->rev;
        p->combine(t->a, t->b);
      }
    }
    t->rev = 0;
    t->v = t->a * t->v + t->b;
    t->a = 1;
    t->b = 0;
  }

  void pull(NodeP& t) {
    t->cnt = 1;
    t->v_acc = t->v;
    for (auto& p : t->to) {
      if (p) {
        t->cnt += p->cnt;
        t->v_acc += p->value();
      }
    }
  }

  // Split to (-oo, q) and [q, oo)
  void split(NodeP t, NodeP& res_l, NodeP& res_r, int q_key, int key = 0) {
    if (!t) { return; }
    push(t);
    int t_key = key + cnt(t->to[0]);
    if (q_key <= t_key) {
      split(move(t->to[0]), res_l, t->to[0], q_key, key);
      pull(t);
      res_r = move(t);
    } else {
      split(move(t->to[1]), t->to[1], res_r, q_key, t_key + 1);
      pull(t);
      res_l = move(t);
    }
  }

  void merge(NodeP tl, NodeP tr, NodeP& res) {
    if (!tl || !tr) { res = move(tl ? tl : tr); return; }
    if (tl->priority < tr->priority) {
      push(tl);
      merge(move(tl->to[1]), move(tr), tl->to[1]);
      res = move(tl);
    } else {
      push(tr);
      merge(move(tl), move(tr->to[0]), tr->to[0]);
      res = move(tr);
    }
    pull(res);
  }

  NodeP root;
  mt19937 rng;
  Treap() : rng{mt19937(0x12345678)} {}

  //
  // Treap interface
  //

  array<NodeP, 3> split3(int l, int r) {
    NodeP x, y, z, yz;
    split(move(root), x, yz, l);
    split(move(yz), y, z, r - l);
    return {move(x), move(y), move(z)};
  }

  void merge3(array<NodeP, 3> xyz) {
    auto& [x, y, z] = xyz;
    NodeP yz;
    merge(move(y), move(z), yz);
    merge(move(x), move(yz), root);
  }

  void insert(int i, T v) {
    NodeP t = make_unique<Node>();
    t->v = t->v_acc = v;
    t->priority = rng();
    auto xyz = split3(i, i);
    xyz[1] = move(t);
    merge3(move(xyz));
  }

  void erase(int i) {
    auto xyz = split3(i, i + 1);
    xyz[1].reset(nullptr);
    merge3(move(xyz));
  }

  void reverse(int l, int r) {
    auto xyz = split3(l, r);
    xyz[1]->rev ^= 1;
    merge3(move(xyz));
  }

  void affine(int l, int r, T a, T b) {
    auto xyz = split3(l, r);
    xyz[1]->combine(a, b);
    merge3(move(xyz));
  }

  T reduce(int l, int r) {
    auto xyz = split3(l, r);
    auto res = xyz[1]->value();
    merge3(move(xyz));
    return res;
  }

  void print() {
    string state = "0";
    function<void(NodeP&)> rec = [&](auto& t) {
      if (!t) { return; }
      dbg(state, t->v, t->v_acc, t->a, t->b, t->cnt);
      state.push_back('0');
      rec(t->to[0]);
      state.back() = '1';
      rec(t->to[1]);
      state.pop_back();
    };
    rec(root);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 5 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n);
  cin >> ls;

  Treap treap;
  FOR(i, 0, n) {
    treap.insert(i, ls[i]);
  }
  #ifdef DEBUG
    treap.print();
  #endif

  FOR(_, 0, nq) {
    int t;
    cin >> t;
    if (t == 0) {
      int i, x;
      cin >> i >> x;
      treap.insert(i, x);
    }

    if (t == 1) {
      int i;
      cin >> i;
      treap.erase(i);
    }

    if (t == 2) {
      int l, r;
      cin >> l >> r;
      treap.reverse(l, r);
    }

    if (t == 3) {
      int l, r, a, b;
      cin >> l >> r >> a >> b;
      treap.affine(l, r, a, b);
    }

    if (t == 4) {
      int l, r;
      cin >> l >> r;
      auto res = treap.reduce(l, r);
      cout << res << "\n";
    }

    #ifdef DEBUG
      treap.print();
    #endif
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/dynamic_sequence_range_affine_range_sum/main.cpp

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
