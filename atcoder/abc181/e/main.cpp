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
  int n, m; // [1, 2 x 10^5]
  cin >> n >> m;
  vector<ll> xs(n), ys(m); // [1, 10^9]
  cin >> xs >> ys;

  const ll kInf = 1e18;

  sort(ALL(xs));
  sort(ALL(ys));

  // Cumsum for each position parity
  vector<ll> ls0(n + 1), ls1(n + 1);
  FOR(i, 0, n) {
    ls0[i + 1] += ls0[i];
    ls1[i + 1] += ls1[i];
    if (i % 2 == 0) {
      ls0[i + 1] += xs[i];
    } else {
      ls1[i + 1] += xs[i];
    }
  }

  // f(x) = min_j |x - yj|
  auto findMin = [&](ll x) -> ll {
    auto it = lower_bound(ALL(ys), x);
    ll res = kInf;
    if (it != ys.begin()) {
      res = min(res, abs(x - *prev(it)));
    }
    if (it != ys.end()) {
      res = min(res, abs(x - *it));
    }
    if (it != ys.end() && next(it) != ys.end()) {
      res = min(res, abs(x - *next(it)));
    }
    return res;
  };

  ll res = kInf;

  FOR(i, 0, n) {
    ll t = findMin(xs[i]);
    if (i % 2 == 0) {
      // (0, 1), (2, 3), ..., (i-2, i-1), | (i+1, i+2), ...
      t += ls1[i] - ls0[i];
      t += (ls0[n] - ls0[i + 1]) - (ls1[n] - ls1[i + 1]);
    } else {
      // (0, 1), (2, 3), ..., (i-3, i-2), | (i-1, i+1) | (i+2, i+3), ...
      t += ls1[i - 1] - ls0[i - 1];
      t += xs[i + 1] - xs[i - 1];
      t += (ls0[n] - ls0[i + 2]) - (ls1[n] - ls1[i + 2]);
    }
    res = min(res, t);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc181/e/main.cpp

%%%% begin
5 3
1 2 3 4 7
1 3 8
%%%%
3
%%%% end

%%%% begin
7 7
31 60 84 23 16 13 32
96 80 73 76 87 57 29
%%%%
34
%%%% end

%%%% begin
15 10
554 525 541 814 661 279 668 360 382 175 833 783 688 793 736
496 732 455 306 189 207 976 73 567 759
%%%%
239
%%%% end
*/
