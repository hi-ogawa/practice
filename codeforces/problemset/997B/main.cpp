// AFTER EDITORIAL, AC

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

// Main
void mainCase() {
  int n; // [1, 10^9]
  cin >> n;

  // Pair-wise coprime
  const int x1 = 4;
  const int x2 = 9;
  const int x3 = 49;

  const int kInf = 1e9 + 1;
  const int m = x2 * x1 + x3 * x2;

  // f(y) = min {i1 + i2 | y = i1 x1 + i2 x2 }
  vector<int> ls(m, kInf);
  FOR(i1, 0, x2) {
    FOR(i2, 0, x3) {
      auto& f = ls[i1 * x1 + i2 * x2];
      f = min(f, i1 + i2);
    }
  }
  dbg(ls);

  // Fix redundancy
  // TODO: Prove correctness i.e. i1 x1 + i2 x2 + i3 x3 = j1 x1 + j2 x2  =>  i1 + i2 ≤ j1 + j2
  //       (maybe this holds only for the given constants??)
  FOR(r, 0, x3) {
    int k = kInf;
    for (int y = r; y < m; y += x3) {
      if (k != kInf && ls[y] != kInf) {
        assert(ls[y] >= k); // This asserts above proposition's correctness
        ls[y] = kInf;
      }
      k = min(k, ls[y]);
      if (k != kInf) { k++; }
    }
  }
  dbg(ls);

  ll res = 0;
  FOR(y, 0, m) {
    if (ls[y] <= n) {
      res += n - ls[y] + 1;
    }
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/997B/main.cpp

%%%% begin
1000000000
%%%%
%%%% end

%%%% begin
1
%%%%
4
%%%% end

%%%% begin
2
%%%%
10
%%%% end

%%%% begin
10
%%%%
244
%%%% end
*/
