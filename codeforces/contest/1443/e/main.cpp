// CONTEST

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
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<array<int, 3>> qs(nq); // x \in [1, 10^5]
  for (auto& q : qs) {
    cin >> q[0];
    if (q[0] == 1) {
      cin >> q[1] >> q[2];
    }
    if (q[0] == 2) {
      cin >> q[1];
    }
  }

  int m = 20; // 20! ~ 10^18
  vector<ll> factorials(m + 1, 1);
  FOR(i, 2, m + 1) {
    factorials[i] = factorials[i - 1] * i;
  }
  dbg(factorials);

  // x = A.a! + B.b! + C.c! + ...
  auto decompose = [&](ll x) -> vector<array<ll, 2>> {
    vector<ll, 2> res;
    while (x > 0) {
      // lower_bound(ALL(factorials)
    }
    return res;
  };

  // State
  ll st_x = 0;

  // Prefix sum
  auto solve = [&](int k) -> ll {
    auto ts = decompose(st_x);
    return 0;
  };

  for (auto [t, x, y] : qs) {
    if (t == 1) {
      x--;
      auto res = solve(y) - solve(x - 1);
      cout << res << "\n";
    }
    if (t == 2) {
      st_x += x;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest/1443/e/main.cpp

%%%% begin
4 4
1 2 4
2 3
1 1 2
1 3 4
%%%%
9
4
6
%%%% end
*/
