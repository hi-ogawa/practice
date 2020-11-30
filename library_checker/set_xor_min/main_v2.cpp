// AC

// NOTE: Bounded size trie with recursion

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

// Cf. https://judge.yosupo.jp/submission/22735 by (anonymous) user
struct Trie {
  struct Node {
    int cnt = 0;
    array<int, 2> to = {0, 0};
  };
  vector<Node> data;
  int n = 2, n_max;
  static inline int b_max = 30;

  Trie(int nq) : n_max{nq * b_max + 2} { // default = 0 and root = 1
    data.resize(n_max);
  }

  int find(int x) {
    int t = 1;
    for (int b = b_max - 1; b >= 0; b--) {
      t = data[t].to[(x >> b) & 1];
    }
    return t;
  }

  void incr(int x, int v) {
    int t = 1;
    data[t].cnt += v;
    for (int b = b_max - 1; b >= 0; b--) {
      int& tx = data[t].to[(x >> b) & 1];
      if (tx == 0) { tx = n++; assert(n <= n_max); }
      t = tx;
      data[t].cnt += v;
    }
  }

  void insert(int x) {
    int t = find(x);
    if (data[t].cnt > 0) { return; }
    incr(x, 1);
  }

  void erase(int x) {
    int t = find(x);
    if (data[t].cnt == 0) { return; }
    incr(x, -1);
  }

  int solve(int x) {
    int res = 0;
    int t = 1;
    for (int b = b_max - 1; b >= 0; b--) {
      int xb = (x >> b) & 1;
      int tx = data[t].to[xb];
      int ty = data[t].to[!xb];
      if (data[tx].cnt > 0) { t = tx; continue; }
      assert(data[ty].cnt > 0);
      t = ty;
      res |= (1 << b);
    }
    return res;
  }
};

// Main
void mainCase() {
  int nq; // [1, 5 x 10^5]
  cin >> nq;
  vector<array<int, 2>> qs(nq); // x \in [0, 2^30)
  cin >> qs;

  Trie trie(nq);

  for (auto [t, x] : qs) {
    if (t == 0) { trie.insert(x); }
    if (t == 1) { trie.erase(x); }
    if (t == 2) {
      auto res = trie.solve(x);
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
python misc/run.py library_checker/set_xor_min/main_v2.cpp

%%%% begin
2
0 6
2 7
%%%%
1
%%%% end

%%%% begin
6
0 6
0 7
2 5
1 7
1 10
2 7
%%%%
2
1
%%%% end
*/
