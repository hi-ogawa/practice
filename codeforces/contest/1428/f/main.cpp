// AFTER EDITORIAL, AC

// NOTE: Managed to get AC after a bit unusal optimizations for lazy segment tree.

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (decltype(Y) I = (X); I < (Y); ++I)
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

// Segment tree for range increment and sum
struct SegmentTree {
  int n = 1;
  vector<ll> data, lazy;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.resize(2 * n);
    lazy.resize(2 * n);
  }

  ll value(int l, int r, int j) {
    return data[j] + lazy[j] * (r - l);
  }

  void push(int l, int r, int j) {
    if (lazy[j] == 0) { return; }
    data[j] = value(l, r, j);
    lazy[2 * j] += lazy[j];
    lazy[2 * j + 1] += lazy[j];
    lazy[j] = 0;
  }

  void pushToLeaf(int i) {
    if (i < 0 || n <= i) { return; }
    int j_leaf = i + n;
    int j = 1;
    int l = 0, r = n;
    while (j != j_leaf) {
      push(l, r, j);
      int m = (l + r) / 2;
      j = 2 * j + (i >= m);
      (i >= m) ? (l = m) : (r = m);
    }
  }

  void pullFromLeaf(int i) {
    if (i < 0 || n <= i) { return; }
    int j = i + n;
    int l = i, r = i + 1;
    int w = 1;
    while (j > 1) {
      (j % 2) ? (l -= w) : (r += w);
      j /= 2;
      w *= 2;
      int m = (l + r) / 2;
      data[j] = value(l, m, 2 * j) + value(m, r, 2 * j + 1);
    }
  }

  void incr_v1(int ql, int qr, ll qv) {
    function<ll(int, int, int)> rec = [&](int l, int r, int j) -> ll {
      if (qr <= l || r <= ql) { return value(l, r, j); }
      if (ql <= l && r <= qr) { lazy[j] += qv; return value(l, r, j); }
      push(l, r, j);
      int m = (l + r) / 2;
      return data[j] = rec(l, m, 2 * j) + rec(m, r, 2 * j + 1);
    };
    rec(0, n, 1);
  }

  // Iterative version
  void incr_v2(int ql, int qr, ll qv) {
    ql = max(0, ql);
    qr = min(n, qr);
    int jl = ql + n, jr = qr + n;
    int jl_l = ql, jl_r = ql + 1;
    int jr_l = qr, jr_r = qr + 1;
    int w = 1; // width of [l, r)
    while (jl < jr) {
      if (jl % 2) {
        lazy[jl] += qv;
        jl++; jl_l += w; jl_r += w;
      }
      if (jr % 2) {
        jr--; jr_l -= w; jr_r -= w;
        lazy[jr] += qv;
      }
      (jl % 2) ? (jl_l -= w) : (jl_r += w);
      (jr % 2) ? (jr_l -= w) : (jr_r += w);
      jl /= 2;
      jr /= 2;
      w *= 2;
    }
    pullFromLeaf(ql);
    pullFromLeaf(qr);
  }

  void incr(int ql, int qr, ll qv) {
    incr_v2(ql, qr, qv);
  }

  ll reduce_v1(int ql, int qr) {
    function<ll(int, int, int)> rec = [&](int l, int r, int j) -> ll {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return value(l, r, j); }
      push(l, r, j);
      int m = (l + r) / 2;
      return rec(l, m, 2 * j) + rec(m, r, 2 * j + 1);
    };
    return rec(0, n, 1);
  }

  // Iterative version
  ll reduce_v2(int ql, int qr) {
    ql = max(0, ql);
    qr = min(n, qr);
    pushToLeaf(ql);
    pushToLeaf(qr);
    ll res = 0;
    int jl = ql + n, jr = qr + n;
    int jl_l = ql, jr_l = qr;
    int w = 1; // width of [l, r)
    while (jl < jr) {
      if (jl % 2) {
        res += value(jl_l, jl_l + w, jl);
        jl++; jl_l += w;
      }
      if (jr % 2) {
        jr--; jr_l -= w;
        res += value(jr_l, jr_l + w, jr);
      }
      if (jl % 2) { jl_l -= w; }
      if (jr % 2) { jr_l -= w; }
      jl /= 2;
      jr /= 2;
      w *= 2;
    }
    return res;
  }

  ll reduce(int ql, int qr) {
    return reduce_v2(ql, qr);
  }

  ll get(int i) {
    pushToLeaf(i);
    return value(i, i + 1, i + n);
  }
};

// Main
void mainCase() {
  int n; // [1, 5 x 10^5]
  cin >> n;
  string s;
  cin >> s;

  // Segment tree to hold cummax of "1...1" length
  SegmentTree tree(n);

  // Find min { j | x >= tree[j] }
  auto search = [&](int x, int i) -> int {
    int j0 = -1; int j1 = i; // (j0, j1]
    while (j0 + 1 < j1) {
      int j = (j0 + j1 + 1) / 2;
      int y = tree.get(j);
      if (x >= y) {
        j1 = j;
      } else {
        j0 = j;
      }
    }
    return j1;
  };

  ll res = 0;
  ll last = 0;
  int len = 0;
  FOR(i, 0, n) {
    if (s[i] == '0') {
      len = 0;
    }
    if (s[i] == '1') {
      // Update cummax
      int j = search(len, i);
      tree.incr(j, i + 1, 1);
      len++;
      last = tree.reduce(0, i + 1);
    }
    res += last;
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1428/f/main.cpp

%%%% begin
4
0110
%%%%
12
%%%% end

%%%% begin
7
1101001
%%%%
30
%%%% end

%%%% begin
12
011100011100
%%%%
156
%%%% end
*/
