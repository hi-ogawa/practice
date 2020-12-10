// TLE

// NOTE: Time ~ n^(3/2) log^2(n) ~ 8 10^9

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

const int kInf = 1 << 30;

// Merge sort tree
struct SegmentTree {
  using T = int;
  int n = 1;
  vector<vector<T>> data;

  SegmentTree(int n_orig) {
    while (n < n_orig) { n *= 2; }
    data.resize(2 * n);
  }

  void init(const vector<T>& v) {
    FOR(i, 0, n) {
      data[i + n].push_back((i < (int)v.size()) ? v[i] : kInf);
    }

    function<void(int, int, int)> rec = [&](int l, int r, int j) {
      if (l + 1 == r) { return; }
      int m = (l + r) / 2;
      rec(l, m, 2 * j);
      rec(m, r, 2 * j + 1);
      auto& d = data[j];
      auto& dl = data[2 * j];
      auto& dr = data[2 * j + 1];
      int k = (r - l) / 2;
      int i = 0, il = 0, ir = 0;
      d.resize(2 * k);
      while (il < k || ir < k) {
        if (il == k) { d[i++] = dr[ir++]; continue; }
        if (ir == k) { d[i++] = dl[il++]; continue; }
        if (dl[il] < dr[ir]) {
          d[i++] = dl[il++];
        } else {
          d[i++] = dr[ir++];
        }
      }
    };
    rec(0, n, 1);
  }

  int orderOfKey(int ql, int qr, T qv) {
    // Collect segments
    vector<vector<T>*> segs;
    function<void(int, int, int)> rec = [&](int l, int r, int j) {
      if (qr <= l || r <= ql) { return; }
      if (ql <= l && r <= qr) { segs.push_back(&data[j]); return; }
      int m = (l + r) / 2;
      rec(l, m, 2 * j);
      rec(m, r, 2 * j + 1);
    };
    rec(0, n, 1);

    // Binary search
    int res = 0;
    for (auto seg : segs) {
      res += distance((*seg).begin(), lower_bound(ALL(*seg), qv));
    }
    return res;
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [0, 10^9]
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  // Mo's algorithm
  int n_blk = sqrt(n);
  auto compare = [&](auto x, auto y) {
    x[0] /= n_blk; y[0] /= n_blk;
    if (x[0] == y[0] && x[0] % 2) { swap(x[1], y[1]); }
    return x < y;
  };
  vector<int> order(nq);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return compare(qs[x], qs[y]); });

  // State
  ll cnt = 0;
  int l = 0, r = 0;
  SegmentTree tree(n);
  tree.init(ls);

  auto insertL = [&](int i) {
    cnt += tree.orderOfKey(l, r, ls[i]);
  };

  auto insertR = [&](int i) {
    cnt += (r - l) - tree.orderOfKey(l, r, ls[i] + 1);
  };

  auto eraseL = [&](int i) {
    cnt -= tree.orderOfKey(l, r, ls[i]);
  };

  auto eraseR = [&](int i) {
    cnt -= (r - l) - tree.orderOfKey(l, r, ls[i] + 1);
  };

  vector<ll> res(nq);
  FOR(o, 0, nq) {
    int i = order[o];
    auto [ql, qr] = qs[i];
    while (r < qr) { insertR(r++); }
    while (ql < l) { insertL(--l); }
    while (qr < r) { eraseR(--r); }
    while (l < ql) { eraseL(l++); }
    res[i] = cnt;
  }

  for (auto x : res) {
    cout << x << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/static_range_inversions_query/main_v2.cpp

%%%% begin
4 2
4 1 4 0
1 3
0 4
%%%%
0
4
%%%% end
*/
