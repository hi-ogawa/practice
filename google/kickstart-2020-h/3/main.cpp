// CONTEST, AC

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

// Main
void mainCase() {
  int n; // [1,10^5]
  cin >> n;
  vector<array<ll, 2>> ls(n); // [-10^9, 10^9]
  cin >> ls;

  vector<ll> xs(n), ys(n);
  FOR(i, 0, n) {
    xs[i] = ls[i][0];
    ys[i] = ls[i][1];
  }

  sort(ALL(xs));
  FOR(i, 0, n) { xs[i] -= i; } // "bias" for position
  sort(ALL(xs));

  sort(ALL(ys));

  // Median problem
  auto solve = [&](const vector<ll>& xs) -> ll {
    int m = n / 2;
    ll res = 0;
    FOR(i, 0, n) {
      res += abs(xs[i] - xs[m]);
    }
    return res;
  };

  dbg(xs, solve(xs));
  dbg(ys, solve(ys));

  ll res = solve(xs) + solve(ys);
  cout << res << "\n";
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
python misc/run.py google/kickstart-2020-h/3/main.cpp

%%%% begin
2
2
1 1
4 4
3
1 1
1 2
1 3
%%%%
Case #1: 5
Case #2: 4
%%%% end
*/
