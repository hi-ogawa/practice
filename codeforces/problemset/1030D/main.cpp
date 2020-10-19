// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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

// Main
void mainCase() {
  ll n, m, k; // [1, 10^9]
  cin >> n >> m >> k;

  //
  // CLAIM.
  //   WLOG, we can always take (x0, y0) = (0, 0)
  //
  // PROP.
  //   Triangle-Area((x1, y1), (x2, y2))
  //    = 1/2 * | x1 x2 |  (|..| means determinant)
  //            | y1 y2 |
  //
  // PROP.
  //    1/2 * | x1 x2 |  = n m / k
  //          | y1 y2 |
  //    <=>
  //    | x1 x2 | = 2 n m / k
  //    | y1 y2 |
  //
  // PROP.
  //   Given z \in [0, nm] with z = a n - c (a <= m and c < n), then
  //   z = | n   0  |
  //       | 0  z/n |
  //
  //     = | n   0  |
  //       | 1  z/n |
  //
  //     = | n   0      |
  //       | 1  a - c/n |
  //
  //     = | n  c |
  //       | 1  a |
  //

  bool ok = (2 * n * m) % k == 0;
  if (!ok) { cout << "NO" << "\n"; return; }

  ll z = 2 * n * m / k;
  ll c = (n - (z % n)) % n;
  ll a = (z + c) / n;

  array<ll, 2> p = {n, 1}, q = {c, a};
  dbg(p, q, p[0] * q[1] - p[1] * q[0]);

  vector<array<ll, 2>> res(3);
  res[1] = p;
  res[2] = q;

  cout << "YES" << "\n";
  FOR(i, 0, 3) {
    FOR(j, 0, 2) {
      cout << res[i][j] << " \n"[j == 1];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1030D/main.cpp

%%%% begin
4 3 3
%%%%
YES
1 0
2 3
4 1
%%%% end

%%%% begin
4 4 7
%%%%
NO
%%%% end
*/
