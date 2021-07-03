// AFTER CONTEST, AC

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

using Real = double;
constexpr Real kInf = 1e18;

// Main
void mainCase() {
  ll n; // [1, 10^5]
  cin >> n;
  vector<ll> ls(n); // [1, 10^9]
  cin >> ls;

  // WLOG, points are ordered
  sort(ALL(ls));

  // Cumsum
  vector<ll> cs(n + 1);
  FOR(i, 0, n) {
    cs[i + 1] = cs[i] + ls[i];
  }

  //
  // Find min f(x)
  //   where
  //     x ≥ 0
  //     f(x) = E[x + A - min(A, 2x)]
  //          = E[A] + x - E[min(A, 2x)]
  //
  // Note that E[min(A, 2x)] is piecewise linear with knots at 2x \in [A1, A2, ..],
  // so we can enumerate possible minimum value easily.
  //


  //
  // min_x { x - E[min(A, 2x)] }
  //

  // x = 0
  Real res = 0;
  FOR(i, 0, n) {
    // x = a / 2
    Real x = Real(ls[i]) / 2;
    Real emin = (cs[i] + (n - i) * 2 * x) / n;
    res = min(res, x - emin);
  }

  // += E[A]
  res += Real(cs[n]) / n;

  cout << fixed << setprecision(15) << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/arc122/b/main.cpp

%%%% begin
3
3 1 4
%%%%
1.83333333333333333333
%%%% end

%%%% begin
10
866111664 178537096 844917655 218662351 383133839 231371336 353498483 865935868 472381277 579910117
%%%%
362925658.10000000000000000000
%%%% end
*/
