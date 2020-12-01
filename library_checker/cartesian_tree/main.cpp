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

// Segment tree for minimum position
struct SegmentTree {
  using T = pair<int, int>;
  static inline T zero = {1 << 30, -1};
  static T join(T lhs, T rhs) {
    return lhs.first < rhs.first ? lhs : rhs;
  }

  int n = 1;
  vector<T> data;

  SegmentTree(int n_orig) {
    while (n < n_orig) { n *= 2; }
    data.assign(2 * n, zero);
  }

  void set(int qi, T qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  T reduce(int ql, int qr) {
    T res = zero;
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
  int n; // [1, 10^6]
  cin >> n;
  vector<int> ls(n); // [0, 10^9], distinct
  cin >> ls;

  SegmentTree tree(n);
  FOR(i, 0, n) { tree.set(i, {ls[i], i}); }

  vector<int> res(n);

  function<void(int, int, int)> solve = [&](int l, int r, int parent) {
    auto [x0, i0] = tree.reduce(l, r);
    assert(i0 != -1);
    res[i0] = (parent == -1) ? i0 : parent;
    dbg(l, i0, r);
    if (l < i0) { solve(l, i0, i0); }
    if (i0 + 1 < r) { solve(i0 + 1, r, i0); }
  };
  solve(0, n, -1);

  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/cartesian_tree/main.cpp

%%%% begin
3
1 0 2
%%%%
1 1 1
%%%% end

%%%% begin
11
9 3 7 1 8 12 10 20 15 18 5
%%%%
1 3 1 3 10 6 4 8 6 8 3
%%%% end
*/
