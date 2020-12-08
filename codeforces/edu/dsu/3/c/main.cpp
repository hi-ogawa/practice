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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Same as codeforces/edu/dsu/3/b/main.cpp
struct Dsu {
  vector<int> parents;
  vector<int> sizes;
  int num_components;
  vector<array<int, 2>> history;
  vector<int> checkpoints;

  Dsu(int n) {
    parents.assign(n, 0);
    iota(ALL(parents), 0);
    sizes.assign(n, 1);
    num_components = n;
  }

  int find(int x) {
    if (x == parents[x]) { return x; }
    return find(parents[x]);
  }

  void merge(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) { return; }
    if (sizes[x] > sizes[y]) { swap(x, y); }
    parents[x] = y;
    sizes[y] += sizes[x];
    num_components--;
    history.push_back({x, y});
  }

  void persist() {
    checkpoints.push_back(history.size());
  }

  void rollback() {
    int cp = checkpoints.back(); checkpoints.pop_back();
    while ((int)history.size() > cp) {
      auto [x, y] = history.back(); history.pop_back();
      parents[x] = x;
      sizes[y] -= sizes[x];
      num_components++;
    }
  }
};

// Cf. https://cp-algorithms.com/data_structures/deleting_in_log_n.html
struct SegmentTree {
  using T = array<int, 2>;

  vector<vector<T>> data;
  int n = 1;

  SegmentTree(int n_orig) {
    while (n < n_orig) { n *= 2; }
    data.resize(2 * n);
  }

  void insert(int ql, int qr, T qv) {
    function<void(int, int, int)> rec = [&](int l, int r, int j) {
      if (qr <= l || r <= ql) { return; }
      if (ql <= l && r <= qr) { data[j].push_back(qv); return; }
      int m = (l + r) / 2;
      rec(l, m, 2 * j);
      rec(m, r, 2 * j + 1);
    };
    rec(0, n, 1);
  }

  template<class F1, class F2, class F3>
  void solve(F1 f_in, F2 f_out, F3 f_leaf) {
    function<void(int, int, int)> rec = [&](int l, int r, int j) {
      f_in(data[j]);
      if (l + 1 == r) {
        f_leaf(l);
      } else {
        int m = (l + r) / 2;
        rec(l, m, 2 * j);
        rec(m, r, 2 * j + 1);
      }
      f_out();
    };
    rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 3 x 10^5]
  cin >> n >> nq;
  vector<tuple<char, int, int>> qs(nq);
  for (auto& [t, x, y] : qs) {
    cin >> t;
    if (t == '+' || t == '-') {
      cin >> x >> y;
      x--; y--;
      if (x > y) { swap(x, y); }
    }
  }

  // Persistent DSU
  Dsu dsu(n);

  // Segment tree over query timings
  SegmentTree tree(nq);
  vector<int> res(nq);

  // Split edge's life span into power of two segments
  map<array<int, 2>, int> times;
  FOR(i, 0, nq) {
    auto [t, x, y] = qs[i];
    if (t == '?') { continue; }
    if (t == '+') {
      assert(!times.count({x, y}));
      times[{x, y}] = i;
    }
    if (t == '-') {
      assert(times.count({x, y}));
      int j = times[{x, y}]; times.erase({x, y});
      tree.insert(j, i, {x, y});
    }
  }
  for (auto [xy, i] : times) {
    tree.insert(i, nq, xy);
  }

  // Answer query along DFS
  auto f_in = [&](const vector<array<int, 2>>& edges) {
    dsu.persist();
    for (auto [x, y] : edges) { dsu.merge(x, y); }
  };
  auto f_out = [&]() {
    dsu.rollback();
  };
  auto f_leaf = [&](int i) {
    if (i >= nq) { return; }
    auto [t, x, y] = qs[i];
    if (t == '?') {
      res[i] = dsu.num_components;
    }
  };
  tree.solve(f_in, f_out, f_leaf);

  // Output
  FOR(i, 0, nq) {
    auto [t, x, y] = qs[i];
    if (t == '?') {
      cout << res[i] << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/dsu/3/c/main.cpp

%%%% begin
5 11
?
+ 1 2
+ 2 3
+ 3 4
+ 4 5
+ 5 1
?
- 2 3
?
- 4 5
?
%%%%
5
1
1
2
%%%% end
*/
