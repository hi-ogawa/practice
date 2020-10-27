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

const int kInf = 1e9;

// Segment tree for range add and range minimum
struct SegmentTree {
  int n = 1;

  vector<int> data;
  vector<int> lazy;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, kInf);
    lazy.assign(2 * n, 0);
  }

  // Only for initialization
  void set(int qi, int qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = min(data[2 * j], data[2 * j + 1]);
    }
  }

  int join(int lhs, int rhs) {
    return min(lhs, rhs);
  }

  int value(int j) {
    return data[j] + lazy[j];
  }

  void push(int j) {
    data[j] = value(j);
    lazy[2 * j] += lazy[j];
    lazy[2 * j + 1] += lazy[j];
    lazy[j] = 0;
  }

  void incr(int ql, int qr, int qv) {
    function<int(int, int, int)> rec = [&](int l, int r, int j) -> int {
      if (qr <= l || r <= ql) { return value(j); }
      if (ql <= l && r <= qr) { lazy[j] += qv; return value(j); }
      push(j);
      int m = (l + r) / 2;
      return data[j] = join(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    rec(0, n, 1);
  }

  int reduce(int ql, int qr) {
    function<int(int, int, int)> rec = [&](int l, int r, int j) -> int {
      if (qr <= l || r <= ql) { return kInf; }
      if (ql <= l && r <= qr) { return value(j); }
      push(j);
      int m = (l + r) / 2;
      return join(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    return rec(0, n, 1);
  }
};


// Main
void mainCase() {
  int k1, k2, k3; // [1, 2 x 10^5]
  cin >> k1 >> k2 >> k3;
  int n = k1 + k2 + k3;
  vector<int> ls1(k1), ls2(k2), ls3(k3); // [1, n]
  cin >> ls1 >> ls2 >> ls3;
  sort(ALL(ls1));
  sort(ALL(ls2));
  sort(ALL(ls3));

  // Cum counts
  vector<int> ps1(n + 1), ps2(n + 1), ps3(n + 1);
  vector<int> qs1(n + 2), qs2(n + 2), qs3(n + 2);
  for (auto x : ls1) { ps1[x]++; }
  for (auto x : ls2) { ps2[x]++; }
  for (auto x : ls3) { ps3[x]++; }
  FOR(i, 0, n + 1) { qs1[i + 1] = qs1[i] + ps1[i]; }
  FOR(i, 0, n + 1) { qs2[i + 1] = qs2[i] + ps2[i]; }
  FOR(i, 0, n + 1) { qs3[i + 1] = qs3[i] + ps3[i]; }

  // Enumerte cost for separation [0, x), [x, y), [y, oo)

  // Segment tree to find minimum cost for ls2 <-> ls3
  // (TODO: clearly heap would suffice)
  SegmentTree tree(n + 2);

  // Initialize cost for the case x = 0 and y = i case (i.e. [0, 0), [0, i), [i, oo))
  FOR(i, 0, n + 2) {
    int t = k2 - qs2[i] + qs3[i];
    tree.set(i, t);
  }

  int res = kInf;
  FOR(x, 1, n + 2) {
    // Cost for ls1 <-> ls2 and ls1 <-> ls3
    int t1 = ((x - 1) - qs1[x]) + (k1 - qs1[x]); // [0, x) \ ls1 + ls1 \ [0, x)
    int t2 = tree.reduce(x, n + 2);
    res = min(res, t1 + t2);

    // Update cost for ls2 <-> ls3
    if (x <= n && ps3[x] == 1) {
      tree.incr(x + 1, n + 2, -1);
    }
  }

  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1257E/main.cpp

%%%% begin
2 1 2
3 1
4
2 5
%%%%
1
%%%% end

%%%% begin
3 2 1
3 2 1
5 4
6
%%%%
0
%%%% end

%%%% begin
2 1 3
5 6
4
1 2 3
%%%%
3
%%%% end

%%%% begin
1 5 1
6
5 1 2 4 7
3
%%%%
2
%%%% end
*/
