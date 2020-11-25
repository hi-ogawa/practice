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

// Sparse table
template<class T, class JoinT>
struct SparseTable {
  int n;
  int logn = 0;
  JoinT join;
  T zero;
  vector<vector<int>> data;

  SparseTable(int n, JoinT join, T zero) : n{n}, join{join}, zero{zero} {
    while ((1 << logn) < n) { logn++; }
    data.assign(logn + 1, vector<int>(1 << logn, zero));
  }

  void build() {
    FOR(b, 1, logn + 1) {
      FOR(i, 0, n - (1 << (b - 1))) {
        data[b][i] = join(data[b - 1][i], data[b - 1][i + (1 << (b - 1))]);
      }
    }
  }

  int reduce(int ql, int qr) {
    if (ql >= qr) { return zero; }
    int b = 31 - __builtin_clz(qr - ql);
    return join(data[b][ql], data[b][qr - (1 << b)]);
  }
};

// Binary search
//   max { x \in [x0, x1) | f(x) = 1 } or
//   min { x \in (x0, x1] | f(x) = 1 }
template<class T, class FuncT>
T binarySearch(T x0, T x1, FuncT f, bool min_mode = 0) {
  if (min_mode) { tie(x0, x1) = make_tuple(-x1, -x0); }
  int s = min_mode ? -1 : 1;
  assert(x0 < x1);
  assert(f(s * x0));
  while (x0 + 1 < x1) {
    T x = (x0 + x1) / 2;
    if (f(s * x)) { x0 = x; } else { x1 = x; }
  }
  return s * x0;
}

// Main
void mainCase() {
  int n; // [3, 2 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, 10^9]
  cin >> ls;

  auto join1 = [](int x, int y) { return min(x, y); };
  auto join2 = [](int x, int y) { return max(x, y); };
  SparseTable<int, decltype(join1)> st_min(n, join1, 1 << 30);
  SparseTable<int, decltype(join2)> st_max(n, join2, 0);
  FOR(i, 0, n) {
    st_min.data[0][i] = ls[i];
    st_max.data[0][i] = ls[i];
  }
  st_min.build();
  st_max.build();

  bool ok = 0;
  array<int, 3> res;
  FOR(x, 1, n - 1) {
    int a = st_max.reduce(0, x);
    auto evaluate = [&](int y) -> bool {
      int b = st_min.reduce(x, y);
      int c = st_max.reduce(y, n);
      dbg(x, y, a, b, c);
      return make_tuple(b, c) >= make_tuple(a, a);
    };
    auto y = binarySearch(x, n, evaluate);
    int b = st_min.reduce(x, y);
    int c = st_max.reduce(y, n);
    bool found = a == b && b == c;
    if (found) {
      ok = 1;
      res[0] = x;
      res[1] = y - x;
      res[2] = n - res[0] - res[1];
      break;
    }
  }

  cout << (ok ? "YES" : "NO") << "\n";
  if (!ok) { return; }
  FOR(i, 0, 3) {
    cout << res[i] << " \n"[i == 2];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1454/f/main_v4.cpp

%%%% begin
1
9
2 1 4 2 4 3 3 1 2
%%%%
YES
2 5 2
%%%% end

%%%% begin
6
11
1 2 3 3 3 4 4 3 4 2 1
8
2 9 1 7 3 9 4 1
9
2 1 4 2 4 3 3 1 2
7
4 2 1 1 4 1 4
5
1 1 1 1 1
7
4 3 4 3 3 3 4
%%%%
YES
6 1 4
NO
YES
2 5 2
YES
4 1 2
YES
1 1 3
YES
2 1 4
%%%% end
*/
