
// NOTE: here, only theory and optimal value

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
  int n, m; // [0, 3 x 10^5]
  cin >> n >> m;
  vector<array<int, 3>> edges(m);
  cin >> edges;

  //
  // CLAIM.
  //   If a vertex has both in/out edges, then it can always reduce to
  //   single in or out edge depending on debt.
  //   Thus, it always possible to reach "minimal state" where each vertex has single edge,
  //   which is clearly "minimum state" as well.
  //

  vector<ll> ls(n);
  for (auto [x, y, w] : edges) {
    x--; y--;
    ls[x] += w;
    ls[y] -= w;
  }
  dbg(ls);

  ll res = 0;
  for (auto w : ls) {
    res += abs(w);
  }
  res /= 2; // Remove double count
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1266D/main.cpp

%%%% begin
3 2
1 2 10
2 3 5
%%%%
2
1 2 5
1 3 5
%%%% end

%%%% begin
3 3
1 2 10
2 3 15
3 1 10
%%%%
1
2 3 5
%%%% end

%%%% begin
4 2
1 2 12
3 4 8
%%%%
2
1 2 12
3 4 8
%%%% end

%%%% begin
3 4
2 3 1
2 3 2
2 3 4
2 3 8
%%%%
1
2 3 15
%%%% end
*/
