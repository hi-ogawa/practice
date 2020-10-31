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

using Real = double;

// Main
void mainCase() {
  int n, l; // n \in [1, 10^5], l \in [1, 10^9]
  cin >> n >> l;
  vector<int> ls(n);
  cin >> ls;

  ls.insert(ls.begin(), 0);
  ls.push_back(l);
  n += 2;
  vector<array<Real, 2>> ts(n); // time at i

  // Left to right
  FOR(i, 1, n) {
    Real v = i;
    Real x = ls[i] - ls[i - 1];
    ts[i][0] = ts[i - 1][0] + x / v;
  }

  // Right to left
  for (int i = n - 2; i >= 0; i--) {
    Real v = n - 1 - i;
    Real x = ls[i + 1] - ls[i];
    ts[i][1] = ts[i + 1][1] + x / v;
  }
  dbg(ts);

  // Find the segment where they meet
  int i0 = -1;
  FOR(i, 0, n - 1) {
    if (ts[i][0] <= ts[i][1] && ts[i + 1][0] >= ts[i + 1][1]) {
      i0 = i;
      break;
    }
  }
  assert(i0 != -1);
  dbg(i0, ls[i0], ls[i0 + 1]);

  // Solve exact time to meet
  //   (t - t0) v0 + (t - t1) v1 = x
  Real x = ls[i0 + 1] - ls[i0];
  Real t0 = ts[i0][0];
  Real t1 = ts[i0 + 1][1];
  Real v0 = i0 + 1;
  Real v1 = n - (i0 + 1);
  Real res = (x + t0 * v0 + t1 * v1) / (v0 + v1);
  dbg(x, t0, t1, v0, v1);

  cout << setprecision(numeric_limits<Real>::digits10 + 1) << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1408/c/main.cpp

%%%% begin
5
2 10
1 9
1 10
1
5 7
1 2 3 4 6
2 1000000000
413470354 982876160
9 478
1 10 25 33 239 445 453 468 477
%%%%
3.000000000000000
3.666666666666667
2.047619047619048
329737645.750000000000000
53.700000000000000
%%%% end
*/
