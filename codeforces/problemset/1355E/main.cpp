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
  int n, A, R, M; // n \in [1, 10^5], A, R, M \in [0, 10^4]
  cin >> n >> A >> R >> M;
  vector<ll> ls(n); // [0, 10^9]
  cin >> ls;
  sort(ALL(ls));

  // Cumsum
  vector<ll> cs(n + 1);
  FOR(i, 0, n) { cs[i + 1] = cs[i] + ls[i]; }
  ll mean = cs[n] / n;

  // (Piecewise) convex ("turning point" at mean when a + r > m)
  auto evaluate = [&](ll x) -> ll {
    int k = distance(ls.begin(), upper_bound(ALL(ls), x));
    ll sm = k * x - cs[k];
    ll bg = (cs[n] - cs[k]) - (n - k) * x;

    if (A + R <= M) {
      // In this case, "M" and "mean" is irrelavant
      // f(x) = A ∑_{xi ≤ x} (x - xi) + R ∑_{x ≤ xi} (xi - x)
      return A * sm + R * bg;
    }

    // A + R > M
    if (x <= mean) {
      // f(x) = (M - R) ∑_{xi ≤ x} (x - xi) + R ∑_{x ≤ xi} (xi - x)
      return (M - R) * sm + R * bg;
    }
    // x > mean
    // f(x) = A ∑_{xi ≤ x} (x - xi) + (M - A) ∑_{x ≤ xi} (xi - x)
    return A * sm + (M - A) * bg;
  };

  // Debug
  // FOR(x, ls[0], ls[n - 1] + 1) {
  //   dbg(x, evaluate(x));
  // }

  // Find convex minimum
  auto search = [&](ll x0, ll x1) -> ll {
    // [x0, x1)
    while (x0 + 3 <= x1) {
      ll xl = x0 + (x1 - x0) / 3;
      ll xr = x0 + (x1 - x0) / 3 * 2;
      ll fl = evaluate(xl);
      ll fr = evaluate(xr);
      if (fl < fr) {
        x1 = xr;
      } else {
        x0 = xl;
      }
    }
    ll res = evaluate(x0);
    FOR(x, x0 + 1, x1) { res = min(res, evaluate(x)); }
    return res;
  };

  // Find minimum for each piece
  auto search2 = [&]() -> ll {
    ll res1 = search(ls[0], mean + 1);
    ll res2 = search(mean + 1, ls[n - 1] + 2);
    dbg(ls[0], mean + 1, ls[n - 1] + 2, res1, res2);
    return min(res1, res2);
  };

  ll res = search2();
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1355E/main.cpp

%%%% begin
3 1 100 100
1 3 8
%%%%
12
%%%% end

%%%% begin
3 100 1 100
1 3 8
%%%%
9
%%%% end

%%%% begin
3 100 100 1
1 3 8
%%%%
4
%%%% end

%%%% begin
5 1 2 4
5 5 3 6 5
%%%%
4
%%%% end

%%%% begin
5 1 2 2
5 5 3 6 5
%%%%
3
%%%% end
*/
