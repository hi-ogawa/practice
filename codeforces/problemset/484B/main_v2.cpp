// AC

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

// SegmentTree for maximum non zero index
struct SegmentTree {
  using Node = int; // -1 or index
  int n = 1;
  vector<Node> data;
  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, -1);
  }
  Node merge(const Node& x, const Node& y) {
    return y == -1 ? x : y;
  }
  void set(int iq) {
    int j = iq + n;
    data[j] = iq;
    while (j > 1) {
      j /= 2;
      data[j] = merge(data[2 * j], data[2 * j + 1]);
    }
  }
  Node reduce(int ql, int qr) {
    function<Node(int, int, int)> rec = [&](int l, int r, int j) {
      if (qr <= l || r <= ql) { return -1; }
      if (ql <= l && r <= qr) { return data[j]; }
      int mid = (l + r) / 2;
      return merge(rec(l, mid, 2 * j), rec(mid, r, 2 * j + 1));
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

  int k = *max_element(ALL(ls));
  SegmentTree tree(k + 1);
  for (auto x : ls) { tree.set(x); }

  // max { y % x | y >= x }
  auto evaluate = [&](int x) -> int {
    int res = 0;
    for (int mx = x; mx < k; mx += x) {
      int y = tree.reduce(mx, mx + x);
      if (y >= 0) {
        res = max(res, y % x);
      }
    }
    return res;
  };

  int res = 0;
  sort(ALL(ls), std::greater<int>());
  for (auto x : ls) {
    if (x <= res) { break; } // Without this optimization, this gets TLE
    res = max(res, evaluate(x));
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/484B/main_v2.cpp --check

%%%% begin
3
3 4 5
%%%%
2
%%%% end
*/
