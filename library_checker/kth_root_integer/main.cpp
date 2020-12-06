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

// Binary search
//   min { x ∈ [x0, x1) | y ≤ f(x) } (f : increasing)
//   max { x ∈ (x1, x0] | f(x) ≥ y } (f : decreasing) (reverse = 1)
template<class T, class U, class FuncT>
T binarySearch(T x0, T x1, U y, FuncT f, bool reverse = 0) {
  int s = reverse ? -1 : 1;
  T count = s * (x1 - x0);
  while (count > 0) {
    T step = count / 2;
    T x = x0 + s * step;
    if (f(x) < y) {
      x0 = x + s;
      count -= (step + 1);
    } else {
      count = step;
    }
  }
  return x0;
}

// Main
void mainCase() {
  ull a; // [0, 2^64)
  int k; // [1, 64]
  cin >> a >> k;
  if (a <= 1 || k == 1) { cout << a << "\n"; return; }

  auto evaluate = [&](ull x) -> bool {
    ull y = 1;
    int e = k;
    int overflow_x = 0;
    while (e > 0) {
      if (e & 1) {
        if (overflow_x | (x > ull(-1) / y)) { return false; }
        y *= x;
      }
      e >>= 1;
      overflow_x |= (x > ull(-1) / x);
      x *= x;
    }
    return y <= a;
  };

  ull x0 = 0;
  ull x1 = a;
  auto res = binarySearch(x1, x0, true, evaluate, /* reverse */ 1);
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
python misc/run.py library_checker/kth_root_integer/main.cpp

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
