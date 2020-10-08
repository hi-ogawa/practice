// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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

// Segment tree for gcd
struct SegmentTree {
  int n = 1;
  using Node = array<int, 2>; // (gcd, count)
  vector<Node> data;
  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, {0, 0});
  }
  Node join(Node x, Node y) {
    auto [gx, cx] = x; auto [gy, cy] = y;
    if (gx == gy) { return {gx, cx + cy}; }
    int g = gcd(gx, gy);
    if (g == gx) { return {gx, cx}; }
    if (g == gy) { return {gy, cy}; }
    return {g, 0};
  }
  void set(int qi, int qv) {
    int j = qi + n;
    data[j] = {qv, 1};
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }
  Node reduce(int ql, int qr) {
    function<Node(int, int, int)> rec = [&](int l, int r, int j) -> Node {
      if (qr <= l || r <= ql) { return {0, 0}; }
      if (ql <= l && r <= qr) { return data[j]; }
      int m = (l + r) / 2;
      return join(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    return rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int n; // [1, 10^6]
  cin >> n;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;
  int nq;
  cin >> nq;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, ls[i]); }

  for (auto [x, y] : qs) {
    auto [g, c] = tree.reduce(x - 1, y);
    int res = (y - x + 1) - c;
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/474F/main.cpp

%%%% begin
5
1 3 2 4 2
4
1 5
2 5
3 5
4 5
%%%%
4
4
1
1
%%%% end
*/
