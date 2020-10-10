// AFTER EDITORIAL, AC

// Cf. https://codeforces.com/blog/entry/13112?#comment-179029

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
  int n, nx, ny; // [1, 3 x 10^5]
  cin >> n >> nx >> ny;
  vector<array<int, 3>> xs(nx);
  vector<array<int, 2>> ys(ny); // [1, 10^9]
  cin >> xs >> ys;

  vector<vector<array<int, 3>>> adj(n); // (weight, type, vertex)
  for (auto [u, v, x] : xs) {
    u--; v--;
    adj[u].push_back({x, 0, v});
    adj[v].push_back({x, 0, u});
  }
  for (auto [u, y] : ys) {
    u--;
    adj[0].push_back({y, 1, u});
  }

  // Modified Dijkstra
  const ll kInf = 1e18;
  int num_used = 0;
  vector<array<ll, 2>> dists(n, {kInf, 0}); // (distance, type)
  set<array<ll, 3>> heap; // (distance, type, vertex)
  dists[0] = {0, 0};
  heap.insert({0, 0, 0});
  while (!heap.empty()) {
    dbg(heap);
    auto [d, t, v] = *heap.begin(); heap.erase(heap.begin());
    num_used += t;
    for (auto [w, tt, u] : adj[v]) {
      if (array<ll, 2>({d + w, tt}) >= dists[u]) { continue; }
      heap.erase({dists[u][0], dists[u][1], u});
      dists[u] = {d + w, tt};
      heap.insert({d + w, tt, u});
    }
  }
  dbg(dists);

  int res = ny - num_used;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/449B/main_v2.cpp

%%%% begin
3 2 1
1 2 1
2 3 1
3 10
%%%%
1
%%%% end

%%%% begin
5 5 3
1 2 1
2 3 2
1 3 3
3 4 4
1 5 5
3 5
4 5
5 5
%%%%
2
%%%% end

%%%% begin
2 2 3
1 2 2
2 1 3
2 1
2 2
2 3
%%%%
2
%%%% end
*/
