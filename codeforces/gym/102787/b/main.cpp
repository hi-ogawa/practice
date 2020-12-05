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

const ll modulo = 1e9 + 7;
using mint = ModInt<modulo>;

// RNG for treap priority and rolling hash base
auto rng = mt19937(0x18181);

const mint hash_base = int(rng());
vector<mint> hash_base_powers;

struct Treap {

  // Implementation

  struct Node {
    char v;
    mint hash_lr;
    mint hash_rl;
    int priority;
    int cnt;
    array<unique_ptr<Node>, 2> to = {};
  };
  using NodeP = unique_ptr<Node>;

  mint combine(mint hash_l, mint hash_r, mint length_l) {
    return hash_l + hash_base_powers[length_l.v] * hash_r;
  }

  void pull(NodeP& t) {
    if (!t) { return; }
    t->cnt = 1 + (t->to[0] ? t->to[0]->cnt : 0) + (t->to[1] ? t->to[1]->cnt : 0);
    t->hash_lr = t->hash_rl = t->v;
    if (t->to[1]) { t->hash_lr = combine(t->hash_lr, t->to[1]->hash_lr, 1); }
    if (t->to[0]) { t->hash_lr = combine(t->to[0]->hash_lr, t->hash_lr, t->to[0]->cnt); }
    if (t->to[0]) { t->hash_rl = combine(t->hash_rl, t->to[0]->hash_rl, 1); }
    if (t->to[1]) { t->hash_rl = combine(t->to[1]->hash_rl, t->hash_rl, t->to[1]->cnt); }
  }

  void split(NodeP t, NodeP& res_l, NodeP& res_r, int q_key, int key = 0) {
    if (!t) { return; }
    int t_key = key + (t->to[0] ? t->to[0]->cnt : 0);
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
      merge(move(tl->to[1]), move(tr), tl->to[1]);
      res = move(tl);
    } else {
      merge(move(tl), move(tr->to[0]), tr->to[0]);
      res = move(tr);
    }
    pull(res);
  }

  // Interface

  NodeP root;

  template<class FuncT>
  void split3(int l, int r, FuncT f) {
    NodeP x, y, z, yz;
    split(move(root), x, yz, l);
    split(move(yz), y, z, r - l);
    f(x, y, z);
    merge(move(y), move(z), yz);
    merge(move(x), move(yz), root);
  }

  void insert(int i, char v) {
    split3(i, i, [&](auto&, auto& y, auto&) {
      assert(!y);
      y = make_unique<Node>();
      y->v = v;
      y->priority = rng();
      pull(y);
    });
  }

  void erase(int l, int r) {
    split3(l, r, [&](auto&, auto& y, auto&) {
      assert(y);
      y.reset(nullptr);
    });
  }

  bool isPalindrome(int l, int r) {
    bool res = 0;
    split3(l, r, [&](auto&, auto& y, auto&) {
      assert(y);
      dbg(y->v, y->hash_lr, y->hash_rl);
      res = y->hash_lr == y->hash_rl;
    });
    return res;
  }
};

// Main
void mainCase() {
  int n, nq;
  cin >> n >> nq;
  vector<char> ls(n);
  cin >> ls;

  // Precompute hash base poweres
  int m = n + nq + 1;
  hash_base_powers.resize(m);
  hash_base_powers[0] = 1;
  FOR(i, 1, m) {
    hash_base_powers[i] = hash_base_powers[i - 1] * hash_base;
  }


  Treap treap;
  FOR(i, 0, n) { treap.insert(i, ls[i]); }

  FOR(_, 0, nq) {
    int t;
    cin >> t;
    if (t == 1) {
      int l, r;
      cin >> l >> r;
      treap.erase(l - 1, r);
    }
    if (t == 2) {
      char c; int i;
      cin >> c >> i;
      treap.insert(i - 1, c);
    }
    if (t == 3) {
      int l, r;
      cin >> l >> r;
      auto res = treap.isPalindrome(l - 1, r);
      cout << (res ? "yes" : "no") << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/gym/102787/b/main.cpp

%%%% begin
4 4
aaaa
1 3 4
3 1 1
3 1 1
2 a 3
%%%%
yes
yes
%%%% end

%%%% begin
5 5
aaaaa
2 b 3
1 1 1
3 5 5
1 5 5
1 3 3
%%%%
yes
%%%% end
*/
