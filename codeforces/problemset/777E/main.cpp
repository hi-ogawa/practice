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

// Segment tree for range maximum
struct SegmentTree {
  using T = ll;
  static inline T zero = 0;
  static T join(T lhs, T rhs) { return max(lhs, rhs); }

  int n = 1;
  vector<T> data;

  SegmentTree(int n_orig) {
    while (n < n_orig) { n *= 2; }
    data.assign(2 * n, zero);
  }

  void set(int qi, T qv) {
    int j = qi + n;
    data[j] = qv;
    while (j > 1) {
      j /= 2;
      data[j] = join(data[2 * j], data[2 * j + 1]);
    }
  }

  T reduce(int ql, int qr) {
    int jl = ql + n, jr = qr + n;
    T res_l = zero, res_r = zero;
    for (; jl < jr; jl /= 2, jr /= 2) {
      if (jl % 2) { res_l = join(res_l, data[jl++]); }
      if (jr % 2) { res_r = join(data[--jr], res_r); }
    }
    return join(res_l, res_r);
  }
};

// Main
void mainCase() {
  int n; // [1, 10^5]
  cin >> n;
  vector<array<int, 3>> ls(n); // [1, 10^9]
  cin >> ls;

  // (b, a) < (b', a')
  auto compare = [](auto x, auto y) { return make_tuple(x[1], x[0]) < make_tuple(y[1], y[0]); };
  sort(ALL(ls), compare);
  dbg(ls);

  // dp(i) = c(i) + max_{j < i and a(i) < b(j)} f(j)
  SegmentTree dp(n);

  FOR(i, 0, n) {
    auto [a, b, c] = ls[i];
    array<int, 3> q = {0, a + 1, 0};
    int i0 = lower_bound(ALL(ls), q, compare) - ls.begin();
    ll f = c + dp.reduce(i0, i);
    dbg(i, i0, f);
    dp.set(i, f);
  }

  ll res = dp.reduce(0, n);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/777E/main.cpp

%%%% begin
3
1 5 1
2 6 2
3 7 3
%%%%
6
%%%% end

%%%% begin
4
1 2 1
1 3 3
4 6 2
5 7 1
%%%%
4
%%%% end
*/
