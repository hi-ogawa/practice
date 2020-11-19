// WIP

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
  using Node = int;
  static inline Node kZero = 0;
  vector<Node> data;

  void init(int _n) {
    while (n < _n) { n *= 2; }
    data.assign(2 * n, kZero);
  }

  Node join(const Node& lhs, const Node& rhs) {
    return max(lhs, rhs);
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

// DSU
struct Dsu {
  SegmentTree parents;
  set<int> segs;

  Dsu(int n) {
    parents.init(n);
    FOR(i, 0, n) {
      parents.set(i, i);
      segs.insert(i);
    }
  }

  // Segment max as representative
  int getParent(int i) {
    auto it = segs.lower_bound(i);
    int i0 = it == segs.begin() ? 0 : *prev(it);
    int i1 = *it;
    return parents.reduce(i0, i1 + 1);
  }

  void mergeRange(int i, int j) {
    auto it = segs.lower_bound(i);
    while (*it < j) {
      it = segs.erase(it);
    }
  }

  int find(int i) {
    int ip = getParent(i);
    if (i == ip) { return i; }
    int res = find(ip);
    parents.set(ip, res);
    return res;
  }

  void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) { return; }
    if (x > y) { swap(x, y); }
    parents.set(x, y);
  }
};

// Main
void mainCase() {
  int n; // [1, 2e5]
  cin >> n;
  int nq; // [1, 5e5]
  cin >> nq;
  vector<array<int, 3>> qs(nq);
  cin >> qs;

  Dsu dsu(n);

  for (auto [t, x, y] : qs) {
    x--; y--;

    if (t == 1) {
      dsu.merge(x, y);
    }

    if (t == 2) {
      dsu.mergeRange(x, y);
    }

    if (t == 3) {
      bool res = dsu.find(x) == dsu.find(y);
      cout << (res ? "YES" : "NO") << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/dsu/2/c/main.cpp

%%%% begin
8 6
3 2 5
1 2 5
3 2 5
2 4 7
2 1 2
3 1 7
%%%%
NO
YES
YES
%%%% end
*/
