// AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n, m; // <= 10^5
  cin >> n >> m;
  vector<array<int, 3>> edges(m);
  cin >> edges;
  sort(ALL(edges));

  vector<vector<array<int, 2>>> adj(n);
  for (auto [x, y, w] : edges) {
    x--; y--;
    adj[x].push_back({y, w});
    adj[y].push_back({x, w});
  }

  int v_beg = 0, v_end = n - 1;
  ll kInf = 1LL << 60;
  vector<ll> dists(n, kInf);
  vector<int> parents(n, -1);
  set<tuple<ll, int>> heap;
  heap.insert({0, v_beg});
  while (!heap.empty()) {
    auto [d, v] = *heap.begin(); heap.erase(heap.begin());
    if (v == v_end) { break; }
    for (auto [u, w] : adj[v]) {
      if (d + w < dists[u]) {
        if (heap.count({dists[u], u})) { heap.erase({dists[u], u}); }
        dists[u] = d + w;
        parents[u] = v;
        heap.insert({d + w, u});
      }
    }
  }
  dbg(dists);
  dbg(parents);

  if (parents[v_end] == -1) {
    cout << -1 << endl; return;
  }

  vector<int> res;
  int v = v_end;
  while (v != v_beg) {
    res.push_back(v);
    v = parents[v];
  }
  res.push_back(v_beg);
  reverse(ALL(res));

  FOR(i, 0, (int)res.size()) {
    if (i) cout << " ";
    cout << (res[i] + 1);
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py codeforces/problemset/20C/main.cpp --check

%%%% begin
5 6
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1
%%%%
1 4 3 5
%%%% end
*/
