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

// Main
void mainCase() {
  int n; // [1, 5e5]
  cin >> n;
  ll k; // [0, 1e9]
  cin >> k;
  vector<ll> ls(n);
  cin >> ls;

  sort(ALL(ls));

  // Cum sum
  vector<ll> ps(n + 1);
  FOR(i, 0, n) { ps[i + 1] = ps[i] + ls[i]; }

  // f(x) = ...
  auto evaluate = [&](ll x) -> ll {
    auto it = upper_bound(ALL(ls), x);
    int m = distance(ls.begin(), it);
    return m * x - ps[m];
  };

  // Max { x | f(x) <= k }
  auto search = [&]() -> ll {
    // [x0, x1)
    ll x0 = ls[0];
    ll x1 = (ps[n] / n) + 1;
    while (x0 + 1 < x1) {
      ll x = (x0 + x1) / 2;
      if (evaluate(x) <= k) {
        x0 = x;
      } else {
        x1 = x;
      }
    }
    return x0;
  };

  // g(x) = ...
  auto evaluate2 = [&](ll x) -> ll {
    auto it = lower_bound(ALL(ls), x);
    int m = distance(it, ls.end());
    return (ps[n] - ps[n - m]) - m * x;
  };

  // Min { x | g(x) <= k }
  auto search2 = [&]() -> ll {
    // (x0, x1]
    ll x0 = ((ps[n] + n - 1) / n) - 1;
    ll x1 = ls[n - 1];
    while (x0 + 1 < x1) {
      ll x = (x0 + x1 + 1) / 2;
      if (evaluate2(x) <= k) {
        x1 = x;
      } else {
        x0 = x;
      }
    }
    return x1;
  };

  auto x_min = search();
  auto x_max = search2();
  dbg(x_min, evaluate(x_min));
  dbg(x_max, evaluate2(x_max));
  auto res = x_max - x_min;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/671B/main.cpp

%%%% begin
4 1
1 1 4 2
%%%%
2
%%%% end

%%%% begin
3 1
2 2 2
%%%%
0
%%%% end
*/
