// AFTER EDITORIAL, AC

// Cf. https://codeforces.com/blog/entry/84024?#comment-714500

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

// Segment tree for maximum
struct SegmentTree {
  int n = 1;
  using Node = int;
  vector<Node> data;
  static inline Node kZero = 1e9;

  SegmentTree(int _n) {
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

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ls(n); // [1, n]
  cin >> ls;

  int k = *max_element(ALL(ls)) + 2;

  // Position for each value
  vector<vector<int>> ps(k);
  FOR(x, 1, k) { ps[x].push_back(-1); } // Dummy boundary to handle boundary naturally
  FOR(i, 0, n) {
    ps[ls[i]].push_back(i);
  }
  FOR(x, 1, k) { ps[x].push_back(n); }

  // Segments not occuring "x"
  vector<array<int, 3>> segs; // (x, l, r)
  FOR(x, 1, k) {
    FOR(i, 0, ps[x].size() - 1) {
      segs.push_back({x, ps[x][i], ps[x][i + 1]});
    }
  }
  sort(ALL(segs), [](auto x, auto y) { return x[2] < y[2]; });

  // Find minimum index of last occurence of any of {1, .., x - 1}
  SegmentTree tree(k);
  FOR(x, 0, k) { tree.set(x, -1); }

  vector<int> found(k + 1);
  for (auto [x, l, r] : segs) {
    if (r < n) { tree.set(x, r); } // Skip dummy right boundary
    if (l + 1 == r) { continue; } // Skip empty segment
    int i = tree.reduce(1, x);
    dbg(x, l, r, i);
    if (l < i) { found[x] = 1; }
  }

  int res = 0;
  FOR(x, 1, k + 1) {
    if (!found[x]) {
      res = x;
      break;
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
python misc/run.py codeforces/contest/1436/e/main.cpp

%%%% begin
3
1 3 2
%%%%
3
%%%% end

%%%% begin
5
1 4 3 1 2
%%%%
6
%%%% end
*/
