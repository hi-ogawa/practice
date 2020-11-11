// AC

// TODO: how to solve without relying on randomize trick??

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

// Hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
uint32_t hash32(uint32_t x) {
  x ^= x >> 16;
  x *= 0x7feb352dU;
  x ^= x >> 15;
  x *= 0x846ca68bU;
  x ^= x >> 16;
  return x;
}
struct Hash32 { size_t operator()(int x) const { return hash32(x); }; };

// Main
void mainCase() {
  int n, m; // [0, 3 x 10^5]
  cin >> n >> m;
  vector<array<ll, 3>> edges(m); // weight \in [1, 10^18]
  cin >> edges;

  // Optimization
  using xmap = unordered_map<int, ll, Hash32>;
  // using xmap = map<int, ll>;

  vector<xmap> adj(n), adjT(n);
  for (auto [x, y, w] : edges) {
    x--; y--;
    adj[x][y] += w;
    adjT[y][x] += w;
  }

  // Randomize resolution order
  vector<int> order(n);
  iota(ALL(order), 0);
  auto rng = mt19937((ull)&mainCase);
  shuffle(ALL(order), rng);

  // Resolve debt for each vertex
  FOR(i, 0, n) {
    int v = order[i];
    while (!adj[v].empty() && !adjT[v].empty()) {
      //
      // u1 --w1--> v --w2--> u2
      //
      auto [u1, w1] = *adjT[v].begin();
      auto [u2, w2] = *adj[v].begin();
      assert(u1 != v);
      assert(u2 != v);
      auto w = min(w1, w2);
      assert(w > 0);
      adj[u1][v] -= w;   if (adj[u1][v] == 0) { adj[u1].erase(v); }
      adj[v][u2] -= w;   if (adj[v][u2] == 0) { adj[v].erase(u2); }
      adjT[v][u1] -= w;  if (adjT[v][u1] == 0) { adjT[v].erase(u1); }
      adjT[u2][v] -= w;  if (adjT[u2][v] == 0) { adjT[u2].erase(v); }
      if (u1 != u2) { // Add if not self loop
        adj[u1][u2] += w;
        adjT[u2][u1] += w;
      }
    }
  }

  vector<array<ll, 3>> res;
  FOR(v, 0, n) {
    if (adj[v].empty()) { continue; }
    for (auto [u, w] : adj[v]) {
      res.push_back({v, u, w});
    }
  }

  cout << res.size() << "\n";
  for (auto [x, y, w] : res) {
    x++; y++;
    cout << x << " " << y << " " << w << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1266D/main_v2.cpp

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
