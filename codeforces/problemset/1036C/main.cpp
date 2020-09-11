// AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// High dimentional vector
template<class T, size_t Rank>
struct Tensor {
  using idx_t = array<int, Rank>;
  idx_t shape_;
  vector<T> data_;
  Tensor(const idx_t& shape, T init_value) : shape_{shape} {
    data_.assign(flatIndex(shape_), init_value);
  }
  int flatIndex(const idx_t& idx) {
    int res = idx[0];
    for (int i = 1; i < (int)Rank; i++) { res += res * shape_[i] + idx[i]; }
    return res;
  }
  template<class ...Is>
  T& operator()(Is... i) {
    static_assert(Rank == sizeof...(i));
    return data_[flatIndex(idx_t{i...})];
  }
};

// Main
ll solve(const vector<int>& x) {
  int n = x.size();
  Tensor<ll, 3> dp({n, 2, 4}, -1);

  // p : (reversed) digit positioin
  // b : bounded by x[p] or not
  // c : non-zero digit count at most
  function<ll(int p, int b, int c)> dpRec;
  dpRec = [&](int p, int b, int c) -> ll {
    if (c < 0) { return 0; }
    if (p == n) { return c >= 0; }
    if (dp(p, b, c) != -1) { return dp(p, b, c); }
    ll res = 0;
    FOR(d, 0, (b ? x[p] : 9) + 1) {
      int bb = b && d == x[p];
      int cc = c - (d > 0);
      res += dpRec(p + 1, bb, cc);
    }
    dbgv(p, b, c, res);
    return dp(p, b, c) = res;
  };

  return dpRec(0, true, 3);
}

void mainCase() {
  ll x, y;
  cin >> x >> y;
  x--;

  vector<int> p, q;
  while (x > 0) { p.push_back(x % 10); x /= 10; }
  while (y > 0) { q.push_back(y % 10); y /= 10; }
  reverse(ALL(p));
  reverse(ALL(q));

  ll res1 = solve(p);
  ll res2 = solve(q);
  ll res = res2 - res1;
  dbgv(res1, res2, res);
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1036C/main.cpp --check

%%%% begin
1
1000000000000000000 1000000000000000000
%%%%
1
%%%% end

%%%% begin
1
1 1000
%%%%
1000
%%%% end

%%%% begin
4
1 1000
1024 1024
65536 65536
999999 1000001
%%%%
1000
1
0
2
%%%% end
*/
