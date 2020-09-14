// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

struct Trie {
  struct Node {
    array<unique_ptr<Node>, 2> cs; // children
    int count = 0;
  };
  Node root;

  void _insert(Node& node, ull x, int b) {
    node.count++;
    if (b == 64) { return; }
    int xb = (x >> (63 - b)) & 1;
    auto& nc = node.cs[xb];
    if (!nc) { nc.reset(new Node); }
    _insert(*nc, x, b + 1);
  }

  void insert(ull x) {
    _insert(root, x, 0);
  }

  void _erase(Node& node, ull x, int b) {
    assert(node.count > 0);
    node.count--;
    if (b == 64) { return; }
    int xb = (x >> (63 - b)) & 1;
    auto& nc = node.cs[xb];
    assert(nc);
    _erase(*nc, x, b + 1);
    if (nc->count == 0) { nc.reset(); }
  }

  void erase(ull x) {
    _erase(root, x, 0);
  }

  ull _solve(Node& node, ull x, int b) {
    assert(node.count > 0);
    if (b == 64) { return 0; }
    int xb = (x >> (63 - b)) & 1;
    ull res = 0, bonus = 0;
    if (node.cs[!xb]) {
      // Get bonus if exclusive to "x[b]"
      res = _solve(*node.cs[!xb], x, b + 1);
      bonus = 1ULL << (63 - b);
    } else {
      res = _solve(*node.cs[xb],  x, b + 1);
    }
    return res | bonus;
  }

  ull solve(ull x) {
    return _solve(root, x, 0);
  }
};

// Main
void mainCase() {
  int nq; // [1, 2x10^5]
  cin >> nq;
  vector<tuple<char, ull>> qs(nq); // x ∈ [1, 10^9]
  cin >> qs;

  Trie trie;
  trie.insert(0);
  for (auto [t, x] : qs) {
    if (t == '+') { trie.insert(x); }
    if (t == '-') { trie.erase(x); }
    if (t == '?') {
      int res = trie.solve(x);
      cout << res << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/706D/main.cpp --check

%%%% begin
10
+ 8
+ 9
+ 11
+ 6
+ 1
? 3
- 8
? 3
? 8
? 11
%%%%
11
10
14
13
%%%% end
*/
