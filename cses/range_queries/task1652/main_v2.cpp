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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Y combinator (cf. http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html)
template<class FuncT>
struct y_combinator_result {
  FuncT f;
  template<class T>
  explicit y_combinator_result(T&& f) : f{forward<T>(f)} {}
  template<class ...Ts>
  decltype(auto) operator()(Ts&& ...args) { return f(ref(*this), forward<Ts>(args)...); }
};

template<class FuncT>
decltype(auto) y_combinator(FuncT&& f) {
  return y_combinator_result<decay_t<FuncT>>(forward<FuncT>(f));
}

// 2D segment tree
struct SegmentTree {
  using T = int;
  static inline T zero = 0;
  static T join(T lhs, T rhs) { return lhs + rhs; }

  int n = 1, m = 1;
  vector<vector<T>> data;

  SegmentTree(int n_orig, int m_orig) {
    while (n < n_orig) { n *= 2; }
    while (m < m_orig) { m *= 2; }
    data.assign(2 * n, vector<T>(2 * m, zero));
  }

  void incr(int qi, int qj, T qv) {
    for (int it = qi + n; it >= 1; it /= 2) {
      int jt = qj + m;
      data[it][jt] += qv;
      while (jt > 1) {
        jt /= 2;
        data[it][jt] = join(data[it][2 * jt], data[it][2 * jt + 1]);
      }
    }
  }

  T reduce(int qil, int qir, int qjl, int qjr) {
    return y_combinator([&](auto rec, int il, int ir, int jl, int jr, int it, int jt) -> T {
      if (qir <= il || ir <= qil) { return zero; }
      if (qil <= il && ir <= qir) {
        if (qjr <= jl || jr <= qjl) { return zero; }
        if (qjl <= jl && jr <= qjr) { return data[it][jt]; }
        int jm = (jl + jr) / 2;
        T jres = zero;
        jres = join(jres, rec(il, ir, jl, jm, it, 2 * jt    ));
        jres = join(jres, rec(il, ir, jm, jr, it, 2 * jt + 1));
        return jres;
      }
      int im = (il + ir) / 2;
      T ires = zero;
      ires = join(ires, rec(il, im, jl, jr, 2 * it,     jt));
      ires = join(ires, rec(im, ir, jl, jr, 2 * it + 1, jt));
      return ires;
    })(0, n, 0, m, 1, 1);
  }
};

// Main
void mainCase() {
  int n, nq; // [1, 1000], [1, 2 x 10^5]
  cin >> n >> nq;
  vector<vector<char>> board(n, vector<char>(n));
  cin >> board;
  vector<array<int, 4>> qs(nq);
  cin >> qs;

  SegmentTree tree(n, n);
  FOR(i, 0, n) {
    FOR(j, 0, n) {
      tree.incr(i, j, board[i][j] == '*');
    }
  }
  dbg2(tree.data);

  for (auto [i0, j0, i1, j1] : qs) {
    i0--; j0--;
    auto res = tree.reduce(i0, i1, j0, j1);
    dbg(i0, i1, j0, j1, res);
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/range_queries/task1652/main_v2.cpp

%%%% begin
2 1
.*
..
1 2 2 2
%%%%
1
%%%% end

%%%% begin
4 3
.*..
*.**
**..
****
2 2 3 4
3 1 3 1
1 1 2 2
%%%%
3
1
2
%%%% end
*/
