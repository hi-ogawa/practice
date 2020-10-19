// AFTER EDITORIAL, AC

// NOTE: bits independedence

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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

// Segment tree for sum
struct FenwickTree {
  int n;
  vector<int> data;
  FenwickTree(int n) : n{n} { data.resize(n); }
  void incr(int qi, int qv) {
    int i = qi;
    while (i < n) {
      data[i] += qv;
      i = (i | (i + 1));
    }
  }
  int reduce(int qr) {
    int i = qr - 1;
    int res = 0;
    while (i >= 0) {
      res += data[i];
      i = (i & (i + 1)) - 1;
    }
    return res;
  }
  int reduce(int ql, int qr) {
    return reduce(qr) - reduce(ql);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  const int b_lim = 30;
  vector<vector<int>> ls(b_lim, vector<int>(n + 1));

  // Assign "1" segment via difference array
  FOR(b, 0, b_lim) {
    for (auto [l, r, x] : qs) {
      l--;
      if ((x >> b) & 1) {
        ls[b][l]++;
        ls[b][r]--;
      }
    }
    FOR(i, 1, n + 1) {
      ls[b][i] += ls[b][i - 1];
    }
    FOR(i, 0, n) {
      ls[b][i] = bool(ls[b][i]); // to 0/1
    }
  }

  // Check "0" segment via fenwick tree
  vector<FenwickTree> tree(b_lim, FenwickTree(n));
  FOR(b, 0, b_lim) {
    FOR(i, 0, n) {
      tree[b].incr(i, ls[b][i]);
    }
  }

  bool ok = 1;
  FOR(b, 0, b_lim) {
    for (auto [l, r, x] : qs) {
      l--;
      if (((x >> b) & 1) == 0) {
        int c = tree[b].reduce(l, r);
        if (c == r - l) { // unsatisfied if segment is all "1"
          ok = 0;
          break;
        }
      }
    }
    if (!ok) { break; }
  }

  cout << (ok ? "YES" : "NO") << "\n";
  if (!ok) { return; }

  vector<int> res(n);
  FOR(b, 0, b_lim) {
    FOR(i, 0, n) {
      res[i] |= ls[b][i] << b;
    }
  }
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
python misc/run.py codeforces/problemset/482B/main.cpp

%%%% begin
3 1
1 3 3
%%%%
YES
3 3 3
%%%% end

%%%% begin
3 2
1 3 3
1 3 2
%%%%
NO
%%%% end
*/
