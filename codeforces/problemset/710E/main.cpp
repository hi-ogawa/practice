// AFTER EDITORIAL, TLE

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
  ll n, x, y; // n \in [1, 10^7], x, y \in [1, 10^9]
  cin >> n >> x >> y;

  //
  // PROP.
  //   Shortest path doesn't need consecutive back edges.
  //   Especially, "2k <--x-- 2k+1" edge is not necessarily.
  //

  // Dijkstra's shortest path
  const ll kInf = 1e18;
  vector<ll> dists(n + 2, kInf);
  set<tuple<ll, int>> heap; // (distance, n)
  heap.insert({dists[1] = x, 1});
  while (true) {
    auto [d, m] = *heap.begin(); heap.erase(heap.begin());
    if (m == n) { break; }
    tuple<ll, int> nexts[] = {{d + x, m + 1}, {d + x, m - 1}, {d + y, 2 * m}};
    for (auto [dd, mm] : nexts) {
      if ((m & 1) && mm == m - 1) { continue; } // No back edge from odd to even
      if (mm <= 0 || n + 1 < mm) { continue; }
      if (dd >= dists[mm]) { continue; }
      heap.erase({dists[mm], mm});
      heap.insert({dists[mm] = dd, mm});
    }
  }
  ll res = dists[n];
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/710E/main.cpp --check

// 2.3 sec
%%%% begin
10000000 1000000000 1
%%%%
8000000023
%%%% end

%%%% begin
4528217 187553422 956731625
%%%%
21178755627
%%%% end

%%%% begin
8 1 1
%%%%
4
%%%% end

%%%% begin
8 1 10
%%%%
8
%%%% end
*/
