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

const ll kInf = 1e18;

// Segment tree for range increment and minimum
struct SegmentTree {
  int n = 1;
  vector<ll> data, lazy;
  ll kZero = kInf;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, kZero);
    lazy.assign(2 * n, 0);
  }

  ostream& print(ostream& ostr) const {
    for (int k = 1; k <= n; k *= 2) {
      for (int i = 0; i < k; i++) {
        ostr << data[i + k] << "#" << lazy[i + k] << " \n"[i == k - 1];
      }
    }
    return ostr;
  }

  ll join(ll lhs, ll rhs) { return min(lhs, rhs); }

  ll value(int j) {
    return data[j] + lazy[j];
  }

  void push(int j) {
    if (lazy[j] == 0) { return; }
    data[j] = value(j);
    lazy[2 * j] += lazy[j];
    lazy[2 * j + 1] += lazy[j];
    lazy[j] = 0;
  }

  // Only for initialization
  void set(int qi, ll qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  void incr(int ql, int qr, ll qv) {
    function<ll(int, int, int)> rec = [&](int l, int r, int j) -> ll {
      if (qr <= l || r <= ql) { return value(j); }
      if (ql <= l && r <= qr) { lazy[j] += qv; return value(j); }
      push(j);
      int m = (l + r) / 2;
      return data[j] = join(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    rec(0, n, 1);
  }

  ll reduce(int ql, int qr) {
    function<ll(int, int, int)> rec = [&](int l, int r, int j) -> ll {
      if (qr <= l || r <= ql) { return kZero; }
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
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [-10^6, 10^6]
  cin >> ls;
  int nq; // [1, 2 x 10^5]
  cin >> nq;
  vector<array<int, 4>> qs(nq); // (type, l, r, x)
  for (auto& q : qs) {
    string s;
    cin >> ws; // newline
    getline(cin, s);
    q[0] = count(ALL(s), ' ');
    stringstream sstr(s);
    if (q[0] == 1) {
      sstr >> q[1] >> q[2];
    }
    if (q[0] == 2) {
      sstr >> q[1] >> q[2] >> q[3];
    }
  }
  dbg(qs);

  SegmentTree tree(n);
  FOR(i, 0, n) {
    tree.set(i, ls[i]);
  }

  for (auto [t, l, r, x] : qs) {
    r++;
    if (t == 1) {
      ll res;
      if (r <= l) {
        ll res1 = tree.reduce(l, n);
        ll res2 = tree.reduce(0, r);
        res = min(res1, res2);
      } else {
        res = tree.reduce(l, r);
      }
      cout << res << "\n";
    }
    if (t == 2) {
      if (r <= l) {
        tree.incr(l, n, x);
        tree.incr(0, r, x);
      } else {
        tree.incr(l, r, x);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/52C/main.cpp

%%%% begin
4
1 2 3 4
4
3 0
3 0 -1
0 1
2 1
%%%%
1
0
0
%%%% end
*/
