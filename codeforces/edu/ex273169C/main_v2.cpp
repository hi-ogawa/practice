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

constexpr int kInf = 1e9 + 1;

// SegmentTree for minimum counting
struct SegmentTree {
  int n = 1;
  vector<tuple<int, int>> data;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(n * 2, {kInf, -1});
  }

  tuple<int, int> join(tuple<int, int> v1, tuple<int, int> v2) {
    auto [m1, c1] = v1;
    auto [m2, c2] = v2;
    int m = min(m1, m2);
    int c = 0;
    if (m == m1) { c += c1; }
    if (m == m2) { c += c2; }
    return {m, c};
  }

  void set(int qi, int qv) {
    int j = qi + n;
    data[j] = {qv, 1};
    while (j > 1) {
      j /= 2;
      data[j] = join(data[j * 2], data[j * 2 + 1]);
    }
  }

  tuple<int, int> _reduce(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return {kInf, -1}; }
    if (ql <= l && r <= qr) { return data[j]; }
    auto v1 = _reduce(ql, qr, l, (l + r) / 2, j * 2);
    auto v2 = _reduce(ql, qr, (l + r) / 2, r, j * 2 + 1);
    return join(v1, v2);
  }

  tuple<int, int> reduce(int ql, int qr) {
    return _reduce(ql, qr, 0, n, 1);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  vector<int> ls(n);
  cin >> ls;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, ls[i]); }

  for (auto [t, x, y] : qs) {
    if (t == 1) {
      tree.set(x, y);
    }
    if (t == 2) {
      auto [m, c] = tree.reduce(x, y);
      cout << m << " " << c << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/ex273169C/main_v2.cpp --check

%%%% begin
5 5
3 4 3 5 2
2 0 3
1 1 2
2 0 3
1 0 2
2 0 5
%%%%
3 2
2 1
2 3
%%%% end
*/
