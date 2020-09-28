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

// Segment tree for maximum
struct SegmentTree {
  int n = 1;
  vector<int> data;
  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.resize(n * 2);
  }

  void set(int qi, int qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = max(data[j * 2], data[j * 2 + 1]);
    }
  }

  int _reduce(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return 0; }
    if (ql <= l && r <= qr) { return data[j]; }
    int v0 = _reduce(ql, qr, l, (l + r) / 2, j * 2);
    int v1 = _reduce(ql, qr, (l + r) / 2, r, j * 2 + 1);
    return max(v0, v1);
  }

  int reduce(int ql, int qr) {
    return _reduce(ql, qr, 0, n, 1);
  }
};

// Main
void mainCase() {
  int n, k; // [0, 3 x 10^5]
  cin >> n >> k;
  vector<int> ls(n); // [0, 3 x 10^5]
  cin >> ls;

  int m = *max_element(ALL(ls));

  // Value domain segments
  SegmentTree tree(m + 1);

  FOR(i, 0, n) {
    int x = ls[i];
    int l = tree.reduce(x - k, x + k + 1);
    tree.set(x, l + 1);
  }

  int res = tree.reduce(0, m + 1);
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abl0/d/main.cpp --check

%%%% begin
10 3
1
5
4
3
8
6
9
7
2
4
%%%%
7
%%%% end
*/
