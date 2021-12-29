// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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

constexpr ll kInf = 1e18;

struct SegmentTree1 {
  int n;
  vector<ll> data;

  SegmentTree1(const vector<ll>& ls) {
    int n_orig = ls.size();
    for (n = 1; n < n_orig; ) {
      n *= 2;
    }
    data.assign(2 * n, 0);
    for (int i = 0; i < n_orig; i++) {
      data[i + n] = ls[i];
    }
    for (int i = n - 1; i > 0; i--) {
      data[i] = data[2 * i] + data[2 * i + 1];
    }
  }

  void set(int i, ll x) {
    i += n;
    data[i] = x;
    i /= 2;
    while (i > 0) {
      data[i] = data[2 * i] + data[2 * i + 1];
      i /= 2;
    }
  }

  ll sum(int l, int r) {
    l += n;
    r += n;
    ll res = 0;
    while (l < r) {
      if (l & 1) {
        res += data[l++];
      }
      if (r & 1) {
        res += data[--r];
      }
      l /= 2;
      r /= 2;
    }
    return res;
  }
};

struct SegmentTree2 {
  int n;
  vector<ll> data;
  vector<ll> lazy;

  SegmentTree2(const vector<ll>& ls) {
    int n_orig = ls.size();
    for (n = 1; n < n_orig; ) {
      n *= 2;
    }
    data.assign(2 * n, -kInf);
    lazy.assign(2 * n, 0);
    for (int i = 0; i < n_orig; i++) {
      data[i + n] = ls[i];
    }
    for (int i = n - 1; i > 0; i--) {
      data[i] = std::max(data[2 * i], data[2 * i + 1]);
    }
  }

  ostream& print(ostream& ostr) const {
    int j = 1;
    for (int k = 1; k <= n; k *= 2) {
      for (int i = 0; i < k; i++, j++) {
        auto x = data[j];
        auto y = lazy[j];
        string x_str = x == -kInf ? "!" : to_string(x);
        ostr << (x == -kInf ? "!" : to_string(x)) << "[" << y << "]";
        ostr << "\t";
      }
      ostr << "\n";
    }
    return ostr;
  }

  friend ostream& operator<<(ostream& ostr, const SegmentTree2& self) {
    ostr << "\n";
    return self.print(ostr);
  }

  void push(int j) {
    lazy[2 * j] += lazy[j];
    lazy[2 * j + 1] += lazy[j];
    lazy[j] = 0;
  }

  ll value(int j) {
    return data[j] + lazy[j];
  }

  void refresh(int ql, int qr) {
    function<ll(int, int, int)> rec = [&](int l, int r, int j) -> ll {
      if (qr <= l || r <= ql) {
        return value(j);
      }
      if (ql <= l && r <= qr) {
        return value(j);
      }
      push(j);
      int m = (l + r) / 2;
      return data[j] = std::max(rec(l, m, 2 * j), rec(m ,r, 2 * j + 1));
    };
    rec(0, n, 1);
  }

  void add(int ql, int qr, ll qx) {
    function<void(int, int, int)> rec = [&](int l, int r, int j) -> void {
      if (qr <= l || r <= ql) {
        return;
      }
      if (ql <= l && r <= qr) {
        lazy[j] += qx;
        return;
      }
      int m = (l + r) / 2;
      rec(l, m, 2 * j);
      rec(m ,r, 2 * j + 1);
    };
    rec(0, n, 1);
    refresh(ql, qr);
  }

  ll max(int ql, int qr) {
    function<ll(int, int, int)> rec = [&](int l, int r, int j) -> ll {
      if (qr <= l || r <= ql) {
        return -kInf;
      }
      if (ql <= l && r <= qr) {
        return value(j);
      }
      int m = (l + r) / 2;
      return std::max(rec(l, m, 2 * j), rec(m, r, 2 * j + 1));
    };
    refresh(ql, qr);
    ll res = rec(0, n, 1);
    return res;
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<ll> ls(n); // [-10^9, 10^9]
  cin >> ls;
  vector<array<ll, 3>> qs(nq);
  cin >> qs;

  auto cum_ls = ls;
  for (int i = 1; i < n; i++) {
    cum_ls[i] += cum_ls[i - 1];
  }

  dbg(ls);
  dbg(cum_ls);

  // For "range sum" and "point set"
  SegmentTree1 tree1(ls);

  // For "range add" and "range max"
  SegmentTree2 tree2(cum_ls);

  dbg("---------");
  dbg(tree2);

  for (auto [t, a, b]: qs) {
    dbg("---------");
    dbg(t, a, b);

    if (t == 1) {
      a--;
      ll delta = b - ls[a];
      ls[a] = b;
      tree1.set(a, ls[a]);
      tree2.add(a, n, delta);
    }

    if (t == 2) {
      a--;
      ll z = tree1.sum(0, a);
      ll w = tree2.max(a, b);
      ll res = std::max(ll(0), w - z);
      dbg(z, w, res);
      cout << res << "\n";
    }

    dbg(tree2);
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/range_queries/task2166/main.cpp

%%%% begin
8 4
1 2 -1 3 1 -5 1 4
2 2 6
1 4 -2
2 2 6
2 3 4
%%%%
5
2
0
%%%% end
*/
