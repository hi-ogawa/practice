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
  int d; // [0, 10^9]
  cin >> d;

  // d = q.x + r
  int x = 1e5 - 2;
  int q = d / x; // [1, 10^4]
  int r = d % x; // [0, 10^5 - 2]

  // (x+1),(x+2)(x+2)...(x+2)  1  (r+1)(r+2)
  // -----x-----                  ----r----
  // --------x------
  // ...
  // -----------x------------
  //           ⇓
  //           q.x

  int n = q + 4; // [1, 10^5]
  vector<int> res(n);

  res[0] = x + 1;
  FOR(i, 0, q) {
    res[i + 1] = x + 2;
  }
  res[q + 1] = 1;
  res[q + 2] = r + 1;
  res[q + 3] = r + 2;

  cout << n << "\n";
  FOR(i, 0, n) {
    cout << res[i] << " \n"[i == n - 1];
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
python misc/run.py codechef/COOK123/DIANE/main.cpp

%%%% begin
4
2
5
200
13
%%%%
3
3 3 2
5
2 8 5 1 10
7
12 10 15 11 19 13 15
4
5 4 4 10
%%%% end
*/
