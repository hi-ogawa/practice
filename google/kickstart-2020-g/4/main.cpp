// AFTER EDITORIAL, AC

// Cf. Errichto's commentary https://www.youtube.com/watch?v=RpyWh424VCE

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

using Real = double;

// Main
void mainCase() {
  int n; // [2, 5000]
  cin >> n;
  vector<Real> ls(n); // [1, 10^9]
  cin >> ls;

  Real res = 0;
  FOR(k, 0, n - 1) {
    FOR(i, 0, k + 1) {
      // Prob(separators at i, .., k-1 removed before separator at k)
      //   = (k - i)! / (k - i + 1)!
      //   = 1 / (k - i + 1)
      res += ls[i] / (k - i + 1);
    }
    FOR(i, k + 1, n) {
      // Prob(separators at k+1, .., i-1 removed before separator at k)
      res += ls[i] / (i - k);
    }
  }
  cout << setprecision(numeric_limits<Real>::digits10 + 1) << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) {
    cout << "Case #" << (i + 1) << ": ";
    mainCase();
  }
  return 0;
}

/*
python misc/run.py google/kickstart-2020-g/4/main.cpp

%%%% begin
2
3
2 1 10
5
19 3 78 2 31
%%%%
Case #1: 20.000000
Case #2: 352.33333333
%%%% end
*/
