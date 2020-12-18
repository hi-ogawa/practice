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

template<class T>
T getKthRoot(int k, T y) {
  assert(k >= 1 && y >= 0);
  if (k == 1 || y <= 1) { return y; }

  const T kInf = numeric_limits<T>::max();

  // x^k ≤ y
  auto evaluate = [&](T x) -> bool {
    int e = k;
    T res = 1;
    bool overflow_x = 0;
    while (e > 0) {
      if (e & 1) {
        if (overflow_x || res > kInf / x) { return 0; }
        res *= x;
      }
      e >>= 1;
      if (overflow_x || (overflow_x = x > kInf / x)) { continue; }
      x *= x;
    }
    return res <= y;
  };

  // max { x | x^k ≤ y }
  T x0 = 1, x1 = y; // [x0, x1)
  while (x0 + 1 < x1) {
    T x = x0 + (x1 - x0) / 2;
    if (evaluate(x)) {
      x0 = x;
    } else {
      x1 = x;
    }
  }
  return x0;
}

// Main
void mainCase() {
  ull a; // [0, 2^64)
  int k; // [1, 64]
  cin >> a >> k;
  auto res = getKthRoot(k, a);
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t; // [1, 5 x 10^5]
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py library_checker/kth_root_integer/main_v2.cpp

%%%% begin
10
215 3
216 3
217 3
9999999999 10
10000000000 10
10000000001 10
18446744073709551615 1
18446744073709551615 2
18446744073709551615 63
18446744073709551615 64
%%%%
5
6
6
9
10
10
18446744073709551615
4294967295
2
1
%%%% end
*/
