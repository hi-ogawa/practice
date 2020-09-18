// AC

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

// Trie
struct Trie {
  struct Node {
    array<Node*, 3> children = {};
    int key(char c) { return c - 'a'; }

    void insert(const string& s, int i, int n) {
      if (i == n) { return; }
      int k = key(s[i]);
      if (!children[k]) { children[k] = new Node(); }
      children[k]->insert(s, i + 1, n);
    }

    bool search(const string& s, int i, int n) {
      if (i == n) { return true; }
      int k = key(s[i]);
      return children[k] && children[k]->search(s, i + 1, n);
    }

    bool solve(const string& s, int i, int n) {
      if (i == n) { return false; }
      bool res = false;
      int k = key(s[i]);
      FOR(kk, 0, 3) {
        if (children[kk]) {
          if (kk == k) {
            res = res || children[kk]->solve(s, i + 1, n);
          } else {
            res = res || children[kk]->search(s, i + 1, n);
          }
        }
      }
      return res;
    }
  };

  Node root;
  void insert(const string& s) { root.insert(s, 0, s.size()); }
  bool solve(const string& s) { return root.solve(s, 0, s.size()); }
};

// Main
void mainCase() {
  int n, m;
  cin >> n >> m;
  vector<string> ls1(n), ls2(m);
  cin >> ls1 >> ls2;

  // Dictionary
  Trie trie;
  for (auto& s : ls1) {
    trie.insert(s);
  }

  // Answer queries
  for (auto& s : ls2) {
    bool res = trie.solve(s);
    cout << (res ? "YES" : "NO") << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/514C/main.cpp --check

%%%% begin
2 3
aaaaa
acacaca
aabaa
ccacacc
caaac
%%%%
YES
NO
NO
%%%% end
*/
