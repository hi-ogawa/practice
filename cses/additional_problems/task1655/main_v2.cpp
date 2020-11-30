// AC

// Cf. Trie from library_checker/set_xor_min/main_v2.cpp

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

// Bounded size trie
struct Trie {
  struct Node {
    int cnt = 0;
    array<int, 2> to = {0, 0};
  };

  int n = 2; // default = 0 and root = 1
  int n_max;
  vector<Node> data;
  static inline int b_max = 30;

  Trie(int num_insert) : n_max{2 + num_insert * b_max} {
    data.resize(n_max);
  }

  int find(int x) {
    int t = 1;
    for (int b = b_max - 1; b >= 0; b--) {
      t = data[t].to[(x >> b) & 1];
      if (data[t].cnt == 0) { return 0; }
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
    incr(x, 1);
  }

  void erase(int x) {
    int t = find(x);
    assert(data[t].cnt > 0);
    incr(x, -1);
  }

  // max { y ^ x | y \in trie }
  int solve(int x) {
    int res = 0;
    int t = 1;
    for (int b = b_max - 1; b >= 0; b--) {
      int tx = data[t].to[(x >> b) & 1];
      int ty = data[t].to[!((x >> b) & 1)];
      if (data[ty].cnt > 0) {
        res |= (1 << b);
        t = ty;
        continue;
      }
      assert(data[tx].cnt > 0);
      t = tx;
    }
    return res;
  }
};

// Main
void mainCase() {
  int n;
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  // Cum XOR
  auto ps = ls;
  FOR(i, 1, n) { ps[i] ^= ps[i - 1]; }

  // Trie
  Trie trie(n);
  FOR(i, 0, n) { trie.insert(ps[i]); }

  int res = trie.solve(0);
  FOR(i, 0, n - 1) {
    // Find max xor segment starting from "i + 1"
    int x = ps[i];
    trie.erase(x);
    int t = trie.solve(x);
    res = max(res, t);
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1655/main_v2.cpp

%%%% begin
4
5 1 5 9
%%%%
13
%%%% end
*/
