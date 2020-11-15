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

// Segment tree for maximum
struct SegmentTree {
  int n = 1;
  int m;
  using Node = vector<int>;
  Node kZero;
  vector<Node> data;

  SegmentTree(int _n, int m) : m{m} {
    while (n < _n) { n *= 2; }
    kZero.resize(m);
    data.assign(2 * n, kZero);
  }

  void join(const Node& lhs, const Node& rhs, Node& res) {
    FOR(i, 0, m) {
      res[i] = max(lhs[i], rhs[i]);
    }
  }

  void set(int qi, const Node& qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      join(data[2 * j], data[2 * j + 1], data[j]);
    }
  }

  Node reduce(int ql, int qr) {
    Node res = kZero;
    int jl = ql + n, jr = qr + n;
    for (; jl < jr; jl /= 2, jr /= 2) {
      if (jl % 2) { join(res, data[jl++], res); }
      if (jr % 2) { join(res, data[--jr], res); }
    }
    return res;
  }
};

// Main
void mainCase() {
  int n, m, k; // n \in [1, 10^5], m \in [1, 5], k \in [0, 10^9]
  cin >> n >> m >> k;
  vector<vector<int>> ls(n, vector<int>(m)); // [0, 10^8]
  cin >> ls;

  // Range maximum
  SegmentTree tree(n, m);
  FOR(i, 0, n) {
    tree.set(i, ls[i]);
  }

  // max { j | segment [i, j] is destroyable }
  auto search = [&](int i) -> int {
    int j0 = i, j1 = n; // [j0, j1)
    while (j0 + 1 < j1) {
      int j = (j0 + j1) / 2;
      auto res = tree.reduce(i, j + 1);
      if (accumulate(ALL(res), 0) <= k) {
        j0 = j;
      } else {
        j1 = j;
      }
    }
    return j0;
  };

  int res1 = 0;
  vector<int> res2(m);
  res2[0] = k;

  FOR(i, 0, n) {
    bool ok = accumulate(ALL(ls[i]), 0) <= k;
    if (!ok) { continue; }
    int j = search(i);
    int t = j - i + 1;
    if (t > res1) {
      res1 = t;
      res2 = tree.reduce(i, j + 1);
    }
  }
  dbg(res1, res2);

  FOR(i, 0, m) {
    cout << res2[i] << " \n"[i == m - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/514D/main.cpp

%%%% begin
5 2 4
4 0
1 2
2 1
0 2
1 3
%%%%
2 2
%%%% end

%%%% begin
3 2 4
1 2
1 3
2 2
%%%%
1 3
%%%% end
*/
