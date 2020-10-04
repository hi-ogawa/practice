// TLE

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

// SegmentTree for sum
struct SegmentTree {
  int n = 1;
  vector<int> data;
  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.resize(2 * n);
  }
  void set(int iq, int iv) {
    int j = iq + n;
    data[j] = iv;
    while (j > 1) {
      j /= 2;
      data[j] = data[2 * j] + data[2 * j + 1];
    }
  }
  int reduce(int ql, int qr) {
    function<int(int, int, int)> rec = [&](int l, int r, int j) -> int {
      if (qr <= l || r <= ql) { return 0; }
      if (ql <= l && r <= qr) { return data[j]; }
      int mid = (l + r) / 2;
      return rec(l, mid, 2 * j) + rec(mid, r, 2 * j + 1);
    };
    return rec(0, n, 1);
  }
};

// Main
void mainCase() {
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 10^6]
  cin >> ls;
  sort(ALL(ls));
  ls.erase(unique(ALL(ls)), ls.end());

  // Time ~ ∑_{a} log(a) k/a log(k) ~ k log(k)^3
  int k = *max_element(ALL(ls));
  SegmentTree tree(k + 1);
  for (auto x : ls) { tree.set(x, 1); }

  // f(x, y) = 1 \iff  ∃z. z % x >= y
  auto evaluate = [&](int x, int y) -> bool {
    // Check [x + y, 2x), [2x + y, 3x), ...
    bool ok = 0;
    for (int i = 1; i * x + y <= k; i++) {
      if (tree.reduce(i * x + y, (i + 1) * x)) {
        ok = 1;
        break;
      }
    }
    return ok;
  };

  // max { y % x | y >= x }
  auto search = [&](int x) -> int {
    int y0 = 0, y1 = x; // [y0, y1)
    while (y0 + 1 < y1) {
      int y = (y0 + y1) / 2;
      if (evaluate(x, y)) {
        y0 = y;
      } else {
        y1 = y;
      }
    }
    return y0;
  };

  int res = 0;
  sort(ALL(ls), std::greater<int>());
  for (auto x : ls) {
    if (x <= res) { break; }
    res = max(res, search(x));
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/484B/main.cpp --check

%%%% begin
3
3 4 5
%%%%
2
%%%% end
*/
