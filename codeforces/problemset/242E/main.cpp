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

// SegmentTree for sum and flip 0/1
struct SegmentTree {
  int depth_ = 0;
  vector<int> data_;
  vector<bool> req_;

  SegmentTree(int n) {
    while ((1 << depth_) < n) { depth_++; }
    data_.resize(1 << (depth_ + 1));
    req_.resize(1 << (depth_ + 1));
  }
  ostream& print(ostream& ostr) {
    FOR(d, 0, depth_ + 1) {
      int j0 = (1 << d) - 1;
      FOR(j, j0, j0 + (1 << d)) {
        if (j > j0) { ostr << "  "; }
        ostr << data_[j];
        if (req_[j]) { ostr << "#"; }
      }
      ostr << endl;
    }
    ostr << endl;
    return ostr;
  }
  int up(int j) { return (j - 1) / 2; }
  int left(int j) { return 2 * j + 1; }
  int right(int j) { return 2 * j + 2; }
  int index(int i) { return (1 << depth_) - 1 + i; }

  // Only for initializationn
  void set(int qi, int qv) {
    int j = index(qi);
    data_[j] = qv;
    while (j > 0) {
      j = up(j);
      data_[j] = data_[left(j)] + data_[right(j)];
    }
  }

  int value(int l, int r, int j) {
    int k = r - l;
    return req_[j] ? (k - data_[j]) : data_[j];
  }

  void propagate(int l, int r, int j) {
    if (req_[j]) {
      data_[j] = value(l, r, j);
      req_[j] = 0;
      req_[left(j)] = !req_[left(j)];
      req_[right(j)] = !req_[right(j)];
    }
  }

  int _flip(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return value(l, r, j); }
    if (ql <= l && r <= qr) { req_[j] = !req_[j]; return value(l, r, j); }
    propagate(l, r, j);
    int v0 = _flip(ql, qr, l, (l + r) / 2, left(j));
    int v1 = _flip(ql, qr, (l + r) / 2, r, right(j));
    return data_[j] = v0 + v1;
  }

  void flip(int ql, int qr) {
    _flip(ql, qr, 0, 1 << depth_, 0);
  }

  int _reduce(int ql, int qr, int l, int r, int j) {
    if (qr <= l || r <= ql) { return 0; }
    if (ql <= l && r <= qr) { return value(l, r, j); }
    propagate(l, r, j);
    auto v0 = _reduce(ql, qr, l, (l + r) / 2, left(j));
    auto v1 = _reduce(ql ,qr, (l + r) / 2, r, right(j));
    return v0 + v1;
  }

  int reduce(int ql, int qr) {
    return _reduce(ql, qr, 0, 1 << depth_, 0);
  }
};

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<int> ls(n);
  cin >> ls;
  int nq; // [1, 5x10^4]
  cin >> nq;
  vector<array<int, 4>> qs(nq);
  FOR(i, 0, nq) {
    auto& q = qs[i];
    cin >> q[0];
    if (q[0] == 1) { cin >> q[1] >> q[2]; }
    if (q[0] == 2) { cin >> q[1] >> q[2] >> q[3]; }
  }

  // Make segmentTree for each bit
  const int b_lim = 20; // 10^6 < 2^b
  vector<SegmentTree> trees(b_lim, n);
  FOR(b, 0, b_lim) {
    FOR(i, 0, n) {
      if ((ls[i] & (1 << b))) {
        trees[b].set(i, 1);
      }
    }
  }

  auto solve1 = [&](int l, int r) -> ll {
    ll res = 0;
    FOR(b, 0, b_lim) {
      ll c = trees[b].reduce(l, r);
      res += (c << b);
    }
    return res;
  };

  auto solve2 = [&](int l, int r, int x) {
    FOR(b, 0, b_lim) {
      if (x & (1 << b)) {
        trees[b].flip(l, r);
      }
    }
  };

  for (auto [t, l, r, x] : qs) {
    l--; // [l, r)

    if (DEBUG) {
      trees[0].print(cout);
      dbgv(t, l, r, x);
    }

    if (t == 1) {
      ll res = solve1(l, r);
      cout << res << endl;
    }
    if (t == 2) {
      solve2(l, r, x);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/242E/main.cpp --check

%%%% begin
4
0 0 1 1
5
1 2 4
2 1 3 1
1 2 4
2 1 3 1
1 2 4
%%%%
2
2
2
%%%% end

%%%% begin
5
4 10 3 13 7
8
1 2 4
2 1 3 3
1 2 4
1 3 3
2 2 5 5
1 1 5
2 1 2 10
1 2 3
%%%%
26
22
0
34
11
%%%% end

%%%% begin
6
4 7 4 0 7 3
5
2 2 3 8
1 1 5
2 3 5 1
2 4 5 6
1 2 3
%%%%
38
28
%%%% end
*/
