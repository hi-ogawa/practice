// WA

// NOTE: Connectedness cannot be determined by this approach.

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

// Segment tree for sum
struct SegmentTree {
  int n = 1;
  using Node = int;
  static inline Node kZero = 0;
  vector<Node> data;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, kZero);
  }

  Node join(const Node& lhs, const Node& rhs) {
    return lhs + rhs;
  }

  void incr(int qi, const Node& qv) {
    int j = qi + n;
    data[j] += qv;
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
  int n; // [1, 5 x 10^5]
  cin >> n;
  vector<array<int, 2>> ls(n); // {1, 2, ..., 2n}
  cin >> ls;
  if (n == 1) { cout << "YES" << "\n"; return; }

  vector<int> order(n);
  iota(ALL(order), 0);

  // Count separately for the left and right in order to check connectedness
  vector<array<int, 2>> cnt_adj(n);

  // Sorted by right
  {
    sort(ALL(order), [&](auto x, auto y) { return ls[x][1] < ls[y][1]; });

    // Segment tree to count intersections except inclusions
    SegmentTree tree(2 * n + 2);

    FOR(i, 0, n) {
      int j = order[i];
      auto [l, r] = ls[j];
      // As difference array
      cnt_adj[j][0] = tree.reduce(0, l + 1);
      tree.incr(l, 1);
      tree.incr(r + 1, -1);
    }
  }

  // Sorted by left
  {
    sort(ALL(order), [&](auto x, auto y) { return ls[x][0] > ls[y][0]; });

    SegmentTree tree(2 * n + 2);

    FOR(i, 0, n) {
      int j = order[i];
      auto [l, r] = ls[j];
      cnt_adj[j][1] = tree.reduce(0, r + 1);
      tree.incr(l, 1);
      tree.incr(r + 1, -1);
    }
  }

  dbg(cnt_adj);

  int num_edges = 0;
  int connected = 1;
  FOR(i, 0, n) {
    auto [c1, c2] = cnt_adj[i];
    if (c1 == 0 && c2 == 0) {
      connected = 0;
      break;
    }
    num_edges += c1;
  }
  dbg(connected, num_edges);

  bool res = connected && (num_edges == n - 1);
  cout << (res ? "YES" : "NO") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1278D/main.cpp

%%%% begin
4
1 4
2 5
3 6
7 8
%%%%
NO
%%%% end

%%%% begin
6
9 12
2 11
1 3
6 10
5 7
4 8
%%%%
YES
%%%% end

%%%% begin
5
1 3
2 4
5 9
6 8
7 10
%%%%
NO
%%%% end

%%%% begin
5
5 8
3 6
2 9
7 10
1 4
%%%%
NO
%%%% end
*/
