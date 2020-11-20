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

struct Dsu {
  vector<int> parents;
  Dsu(int n) {
    parents.assign(n, 0);
    iota(ALL(parents), 0);
  }
  int find(int x) {
    if (x == parents[x]) { return x; }
    return parents[x] = find(parents[x]);
  }
  void merge(int x, int y) {
    parents[find(x)] = find(y);
  }
};

// Main
void mainCase() {
  int n, m; // [1, 10^5]
  cin >> n >> m;
  ll s; // [0, 10^18]
  cin >> s;
  vector<array<ll, 3>> edges(m);
  cin >> edges;
  for (auto& [x, y, w] : edges) { x--; y--; }

  vector<int> order(m);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return edges[x][2] > edges[y][2]; });

  //
  // CLAIM.
  //   G' ⊆ G: connected
  //     maximize |edges(G)| - |edges(G')|
  //       s.t. weight(G) - weight(G') ≤ s
  //
  //   \iff
  //
  //   G' ⊆ G: connected
  //     minimize |edges(G')|
  //       s.t. weight(G') ≥ weight(G) - s
  //

  ll w_total = 0;
  for (auto [x, y, w] : edges) {
    w_total += w;
  }
  ll w_lim = max((ll)0, w_total - s);

  // Max spanning tree
  vector<int> used(m);
  Dsu dsu(n);
  ll w_cur = 0;
  FOR(o, 0, m) {
    int i = order[o];
    auto [x, y, w] = edges[i];
    x = dsu.find(x);
    y = dsu.find(y);
    if (x != y) {
      dsu.merge(x, y);
      used[i] = 1;
      w_cur += w;
    }
  }

  // Add remaining edges
  FOR(o, 0, m) {
    int i = order[o];
    if (w_cur >= w_lim) { break; }
    if (used[i]) { continue; }
    auto [x, y, w] = edges[i];
    used[i] = 1;
    w_cur += w;
  }

  vector<int> res;
  FOR(i, 0, m) {
    if (!used[i]) { res.push_back(i); }
  }

  int k = res.size();
  cout << k << "\n";
  FOR(i, 0, k) {
    cout << (res[i] + 1) << " \n"[i == k - 1];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu/dsu/2/h/main.cpp

%%%% begin
6 7 10
1 2 3
1 3 3
2 3 3
3 4 1
4 5 5
5 6 4
4 6 5
%%%%
2
1 6
%%%% end
*/
