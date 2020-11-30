// AFTER EDITORIAL, WIP

// NOTE: this is incorrect.

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

// Main
void mainCase() {
  int n, k; // [0, 5 x 10^5]
  cin >> n >> k;
  vector<int> ls(n); // [-10^6, 10^6]
  cin >> ls;
  sort(ALL(ls));

  // Count negatives
  int n0 = count_if(ALL(ls), [](auto x) { return x < 0; });

  dbg(ls, n0);

  // Cum sum
  vector<ll> ps(n + 1);
  FOR(i, 0, n) { ps[i + 1] = ps[i] + ls[i]; }

  // Sum of cum sums for positives
  // 0 * p0 + 1 * p1 + 2 * p2 + ...
  ll pos = 0;
  FOR(i, n0, n) { pos += (i - n0) * ls[i]; }

  const ll kInf = 1e18;

  // Maximum gain when partitioning to "m"
  auto solve = [&](int m) -> ll {
    ll res = 0;
    // Accumulate negatives
    for (int i = 0; i < n0; i += m) {
      res += i * (ps[min(i + m, n0)] - ps[i]);
    }

    // Accumulate positives
    int h = (n0 + (m - 1)) / m;
    res += h * (ps[n] - ps[n0]) + pos;

    return res;
  };

  ll res = -kInf;
  FOR(m, 1, k + 2) {
    ll t = solve(m);
    dbg(m, t);
    res = max(res, t);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1457/e/main.cpp

%%%% begin
3 0
1 1 1
%%%%
3
%%%% end

%%%% begin
5 1
-1 -2 -3 -4 5
%%%%
11
%%%% end

%%%% begin
13 2
3 1 4 1 5 -9 -2 -6 -5 -3 -5 -8 -9
%%%%
71
%%%% end
*/
