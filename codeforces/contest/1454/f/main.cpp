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
#define dbg(...) do { cout << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cout << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Segment tree for minimum
struct SegmentTree1 {
  int n = 1;
  using Node = int;
  static inline Node kZero = 1e9;
  vector<Node> data;

  SegmentTree1(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, kZero);
  }

  Node join(const Node& lhs, const Node& rhs) {
    return min(lhs, rhs);
  }

  void set(int qi, const Node& qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  Node reduce(int ql, int qr) {
    Node res = kZero;
    int jl = ql + n, jr = qr + n;
    for (; jl < jr; jl /= 2, jr /= 2) {
      if (jl % 2) { res = join(res, data[jl++]); }
      if (jr % 2) { res = join(res, data[--jr]); }
    }
    return res;
  }
};

// Segment tree for maximum
struct SegmentTree2 {
  int n = 1;
  using Node = int;
  static inline Node kZero = 0;
  vector<Node> data;

  SegmentTree2(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, kZero);
  }

  Node join(const Node& lhs, const Node& rhs) {
    return max(lhs, rhs);
  }

  void set(int qi, const Node& qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  Node reduce(int ql, int qr) {
    Node res = kZero;
    int jl = ql + n, jr = qr + n;
    for (; jl < jr; jl /= 2, jr /= 2) {
      if (jl % 2) { res = join(res, data[jl++]); }
      if (jr % 2) { res = join(res, data[--jr]); }
    }
    return res;
  }
};

// Main
void mainCase() {
  int n; // [3, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;

  SegmentTree1 tree1(n);
  SegmentTree2 tree2(n);
  FOR(i, 0, n) {
    tree1.set(i, ls[i]);
    tree2.set(i, ls[i]);
  }

  auto search = [&](int x, int a) -> tuple<bool, int> {
    int y0 = x, y1 = n - 1; // (y0, y1]
    while (y0 + 1 < y1) {
      int y = (y0 + y1 + 1) / 2;
      int b = tree1.reduce(x, y);
      int c = tree2.reduce(y, n);
      if (make_tuple(b, c) > make_tuple(a, a)) {
        y0 = y;
      } else {
        y1 = y;
      }
    }
    int b1 = tree1.reduce(x, y1);
    int c1 = tree2.reduce(y1, n);
    bool ok = a == b1 && b1 == c1;
    return {ok, y1};
  };

  bool ok = 0;
  array<int, 3> res;
  FOR(x, 1, n - 1) {
    int a = tree2.reduce(0, x);
    auto [found, y] = search(x, a);
    if (found) {
      ok = 1;
      res[0] = x;
      res[1] = y - x;
      res[2] = n - res[0] - res[1];
      break;
    }
  }

  cout << (ok ? "YES" : "NO") << "\n";
  if (!ok) { return; }
  FOR(i, 0, 3) {
    cout << res[i] << " \n"[i == 2];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1454/f/main.cpp

%%%% begin
1
9
2 1 4 2 4 3 3 1 2
%%%%
YES
2 5 2
%%%% end

%%%% begin
6
11
1 2 3 3 3 4 4 3 4 2 1
8
2 9 1 7 3 9 4 1
9
2 1 4 2 4 3 3 1 2
7
4 2 1 1 4 1 4
5
1 1 1 1 1
7
4 3 4 3 3 3 4
%%%%
YES
6 1 4
NO
YES
2 5 2
YES
4 1 2
YES
1 1 3
YES
2 1 4
%%%% end
*/
