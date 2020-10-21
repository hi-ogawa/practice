// WIP

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

// Segment tree for bitwise OR
struct SegmentTree {
  int n_ = 1;
  vector<int> data_;
  SegmentTree(int n) {
    while (n_ < n) { n_ *= 2; }
    data_.resize(2 * n_);
  }
  void set(int qi, int qv) {
    int j = qi + n_;
    data_[j] = qv;
    while (j > 1) {
      j /= 2;
      data_[j] = data_[2 * j] | data_[2 * j + 1];
    }
  }
  int reduce(int ql, int qr) {
    function<int(int, int, int)> _reduce = [&](int l, int r, int j) -> int {
      if (r <= ql || qr <= l) { return 0; }
      if (ql <= l && r <= qr) { return data_[j]; }
      int v0 = _reduce(l, (l + r) / 2, 2 * j);
      int v1 = _reduce((l + r) / 2, r, 2 * j + 1);
      return v0 | v1;
    };
    return _reduce(0, n_, 1);
  }
};

// Main
void mainCase() {
  int n; // [1, 2x10^5]
  cin >> n;
  string s;
  cin >> s;

  // Segment tree to find inversion
  SegmentTree tree(n);
  FOR(i, 0, n) {
    tree.set(i, 1 << (s[i] - 'a'));
  }

  const int k = 26;
  vector<vector<bool>> adj(k, vector<bool>(k));

  FOR(i, 1, n) {
    int x = tree.reduce(0, i);
    int b0 = s[i] - 'a';
    FOR(b, b0 + 1, k) {
      if (x & (1 << b)) {
        adj[b0][b] = 1;
      }
    }
  }
  dbg2(adj);
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1296E2/main_v3.cpp --check

%%%% begin
4
dacb
%%%%
%%%% end

%%%% begin
9
abacbecfd
%%%%
2
1 1 2 1 2 1 2 1 2
%%%% end

%%%% begin
8
aaabbcbb
%%%%
2
1 2 1 2 1 2 1 1
%%%% end

%%%% begin
7
abcdedc
%%%%
3
1 1 1 1 1 2 3
%%%% end

%%%% begin
5
abcde
%%%%
1
1 1 1 1 1
%%%% end
*/
