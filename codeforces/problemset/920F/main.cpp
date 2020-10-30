// AFTER EDITORIAL, AC

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

// Segment tree for range sum with multiple versions
struct SegmentTree {
  int n = 1, m;
  vector<ll> data;
  vector<vector<ll>> data_version;
  vector<int> min_version;

  SegmentTree(int _n, int _m) {
    m = _m;
    while (n < _n) { n *= 2; }
    data.assign(2 * n, 0);
    data_version.assign(m, data);
    min_version.assign(2 * n, 0);
  }

  ostream& print(ostream& ostr) const {
    for (int k = 1; k <= n; k *= 2) {
      for (int i = 0; i < k; i++) {
        int j = i + k;
        ostr << data[j] << " \n"[i == k - 1];
      }
    }
    return ostr;
  }

  friend ostream& operator<<(ostream& ostr, const SegmentTree& self) {
    return self.print(ostr);
  }

  void set(int version, int i, ll x) {
    int j = i + n;
    data_version[version][j] = x;
  }

  void init() {
    FOR(i, 0, m) {
      auto& ls = data_version[i];
      for (int j = n - 1; j >= 1; j--) {
        ls[j] = ls[2 * j] + ls[2 * j + 1];
      }
    }
    data = data_version[0];
  }

  void incrementVersion(int ql, int qr) {
    function<ll(int, int, int)> rec = [&](int l, int r, int j) -> ll {
      if (qr <= l || r <= ql) { return data[j]; }
      if (ql <= l && r <= qr) {
        // When the query covers a node, the node recurses to children at most "m" times
        // and when it recurses it can take at most |segment| time.
        // Also, each query can cover at most log(n) nodes,
        // thus, when #{queries} = Q ~ n, we have at most Q log(n) ~ n log(n) segments covered in total.
        // Thus, in worst case, total time for this "incrementVersion" becomes
        //   ∑_{seg} m. |seg| = m n log(n)
        int v = ++min_version[j];
        if (v >= m) { return data_version[m - 1][j]; }

        // Leaf node
        if (r == l + 1) {
          return data[j] = data_version[v][j];
        }
      }
      auto xl = rec(l, (l + r) / 2, 2 * j);
      auto xr = rec((l + r) / 2, r, 2 * j + 1);
      min_version[j] = min(min_version[2 * j], min_version[2 * j + 1]);
      return data[j] = xl + xr;
    };
    rec(0, n, 1);
  }

  ll reduce(int ql, int qr) {
    function<ll(int, int, int)> rec = [&](int l, int r, int j) -> ll {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return data[j]; }
      return rec(l, (l + r) / 2, 2 * j) + rec((l + r) / 2, r, 2 * j + 1);
    };
    return rec(0, n, 1);
  }
};

vector<int> makeDivisorFunction(int n) {
  vector<int> sieve(n + 1, 1);
  vector<int> res(n + 1, 1);
  for (int p = 2; p <= n; p++) {
    if (!sieve[p]) { continue; }
    int e = 1;
    ll pe = p;
    for (; pe <= n; e++, pe *= p) {
      int i = 1;
      int x = pe;
      for (; x <= n; i++, x += pe) {
        if (i % p == 0) { continue; }
        sieve[x] = 0;
        res[x] *= (e + 1);
      }
    }
  }
  return res;
};

// Main
void mainCase() {
  int n, nq; // [1, 3 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  int k = *max_element(ALL(ls));
  auto divisor = makeDivisorFunction(k);

  // cf. experiment.cpp
  const int m = 7;
  vector<vector<int>> repeats(m, ls);
  FOR(i, 0, m - 1) {
    FOR(j, 0, n) {
      repeats[i + 1][j] = divisor[repeats[i][j]];
    }
  }
  dbg2(repeats);

  SegmentTree tree(n, m);
  FOR(i, 0, m) {
    FOR(j, 0, n) {
      tree.set(i, j, repeats[i][j]);
    }
  }
  tree.init();

  for (auto [t, l, r] : qs) {
    l--;
    dbg(tree);
    if (t == 1) {
      tree.incrementVersion(l, r);
    }
    if (t == 2) {
      ll res = tree.reduce(l, r);
      cout << res << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/920F/main.cpp

%%%% begin
7 6
6 4 1 10 3 2 4
2 1 7
2 4 5
1 3 5
2 4 4
1 5 7
2 1 7
%%%%
30
13
4
22
%%%% end
*/
