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

// Segment tree for sum
struct SegmentTree {
  int n = 1;
  using Node = int;
  static inline Node kZero = 0;
  vector<Node> data;

  SegmentTree(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, kZero);
  }

  Node join(const Node& lhs, const Node& rhs) {
    return lhs + rhs;
  }

  void set(int qi, const Node& qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  Node reduce(int ql, int qr) {
    Node res = kZero;
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
  int n, k; // [1, 5 x 10^5]
  cin >> n >> k;
  int d; // [0, 10^9]
  cin >> d;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;
  sort(ALL(ls));

  dbg(ls);

  SegmentTree dp(n + 1);
  dp.set(0, 1);
  FOR(i, 1, n + 1) {
    int x = ls[i - 1];
    auto it = lower_bound(ALL(ls), x - d);
    int n0 = distance(ls.begin(), it);
    int n1 = i - k;
    dbg(i, n0, n1);

    if (n0 > n1) { continue; }
    bool t = dp.reduce(n0, n1 + 1);
    dp.set(i, t);
  }

  bool res = dp.reduce(n, n + 1);
  cout << (res ? "YES" : "NO") << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/985E/main.cpp

%%%% begin
6 3 10
7 2 7 7 4 2
%%%%
YES
%%%% end

%%%% begin
6 2 3
4 5 3 13 4 10
%%%%
YES
%%%% end

%%%% begin
3 2 5
10 16 22
%%%%
NO
%%%% end
*/
