// MLE

// NOTE: Faking dynamic Fenwick tree by unordered_map

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

// Hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
uint32_t hash32(uint32_t x) {
  x ^= x >> 16;
  x *= 0x7feb352dU;
  x ^= x >> 15;
  x *= 0x846ca68bU;
  x ^= x >> 16;
  return x;
}

struct Hash { size_t operator()(array<int, 2> x) const { return hash32(hash32(x[0]) ^ x[1]); }; };

// 2D Fenwick tree
struct FenwickTree {
  using T = ll;
  int n, m;
  unordered_map<array<int, 2>, T, Hash> data;

  FenwickTree(int n, int m) : n{n}, m{m} {}

  void incr(int qi, int qj, T qv) {
    int i = qi;
    while (i < n) {
      int j = qj;
      while (j < m) {
        data[{i, j}] += qv;
        j = (j | (j + 1));
      }
      i = (i | (i + 1));
    }
  }

  T reduce(int qi, int qj) { // [0, qi) * [0, qj)
    T res = 0;
    int i = qi - 1;
    while (i >= 0) {
      int j = qj - 1;
      while (j >= 0) {
        if (data.count({i, j})) {
          res += data[{i, j}];
        }
        j = (j & (j + 1)) - 1;
      }
      i = (i & (i + 1)) - 1;
    }
    return res;
  }

  T reduce(int i0, int i1, int j0, int j1) { // [i0, i1) x [j0, j1)
    return reduce(i0, j0) + reduce(i1, j1) - reduce(i0, j1) - reduce(i1, j0);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<array<int, 3>> ls(n); // [0, 10^9]
  vector<array<int, 4>> qs(nq);
  cin >> ls >> qs;

  // Compress coordinates
  vector<int> xs, ys;
  for (auto [x, y, w] : ls) {
    xs.push_back(x);
    ys.push_back(y);
  }
  for (auto [x0, y0, x1, y1] : qs) {
    xs.push_back(x0);
    xs.push_back(x1);
    ys.push_back(y0);
    ys.push_back(y1);
  }
  sort(ALL(xs));
  sort(ALL(ys));
  for (auto& [x, y, w] : ls) {
    x = distance(xs.begin(), lower_bound(ALL(xs), x));
    y = distance(ys.begin(), lower_bound(ALL(ys), y));
  }
  for (auto& [x0, y0, x1, y1] : qs) {
    x0 = distance(xs.begin(), lower_bound(ALL(xs), x0));
    x1 = distance(xs.begin(), lower_bound(ALL(xs), x1));
    y0 = distance(ys.begin(), lower_bound(ALL(ys), y0));
    y1 = distance(ys.begin(), lower_bound(ALL(ys), y1));
  }
  dbg(ls);
  dbg(qs);

  // 2D Fenwick tree
  FenwickTree tree(xs.size(), ys.size());
  tree.data.reserve(ls.size() * 20 * 20);
  for (auto [x, y, w] : ls) {
    tree.incr(x, y, w);
  }

  for (auto [x0, y0, x1, y1] : qs) {
    auto res = tree.reduce(x0, x1, y0, y1);
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/rectangle_sum/main_v2.cpp

%%%% begin
5 5
0 0 1
3 0 10
1 4 100
2 2 1000
3 2 10000
0 0 4 5
0 0 4 4
3 0 4 3
2 0 4 3
1 2 2 4
%%%%
11111
11011
10010
11010
0
%%%% end
*/
