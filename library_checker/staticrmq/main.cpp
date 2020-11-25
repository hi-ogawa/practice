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

// Sparse table for minimum
struct SparseTable {
  int n;
  int logn = 0;
  int zero = 1 << 30;
  vector<vector<int>> data;

  SparseTable(int n) : n{n} {
    while ((1 << logn) < n) { logn++; }
    data.assign(logn + 1, vector<int>(1 << logn, zero));
  }

  int join(int lhs, int rhs) { return min(lhs, rhs); }

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

// Main
void mainCase() {
  int n, nq; // [1, 5 x 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [0, 10^9]
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  SparseTable st(n);
  FOR(i, 0, n) { st.data[0][i] = ls[i]; }
  st.build();

  for (auto [l, r] : qs) {
    auto res = st.reduce(l, r);
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/staticrmq/main.cpp

%%%% begin
4 10
2 10 1 100
0 1
0 2
0 3
0 4
1 2
1 3
1 4
2 3
2 4
3 4
%%%%
2
2
1
1
10
1
1
1
1
100
%%%% end
*/
