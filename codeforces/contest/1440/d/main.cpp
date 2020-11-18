// CONTEST, WA

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
  int n, m, k; // [1, 10^5]
  cin >> n >> m >> k;
  vector<array<int, 2>> edges(m);
  cin >> edges;

  vector<vector<int>> adj(n);
  vector<int> degs(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
    degs[x]++;
    degs[y]++;
  }

  // Heap of vertices by thier degree
  set<array<int, 2>> heap; // (degree, vertex)
  FOR(i, 0, n) {
    heap.insert({degs[i], i});
  }

  // Remove until degree >= k - 1
  bool ok1 = 0;
  while (!heap.empty()) {
    auto [d, v] = *heap.begin();
    if (d >= k - 1) {
      ok1 = 1;
      break;
    }
    heap.erase(heap.begin());
    degs[v] = 0;
    for (auto u : adj[v]) {
      if (degs[u] == 0) { continue; }
      heap.erase({degs[u], u});
      heap.insert({degs[u] -= 1, u});
    }
  }
  if (!ok1) { cout << -1 << "\n"; return; }

  auto heap2 = heap;

  // Remove until degree >= k
  bool ok2 = 0;
  while (!heap2.empty()) {
    auto [d, v] = *heap2.begin();
    if (d >= k) {
      ok2 = 1;
      break;
    }
    heap2.erase(heap2.begin());
    degs[v] = 0;
    for (auto u : adj[v]) {
      if (degs[u] == 0) { continue; }
      heap2.erase({degs[u], u});
      heap2.insert({degs[u] -= 1, u});
    }
  }

  if (ok2) {
    cout << 1 << " " << heap2.size() << "\n";
    auto sep = "";
    for (auto [d, v] : heap2) {
      cout << sep << (v + 1); sep = " ";
    }
    cout << "\n";
    return;
  }

  // Remove again
  auto heap3 = heap;
  bool ok3 = 0;
  while (!heap3.empty()) {
    auto [d, v] = *heap3.begin();
    if (d == k - 1 && heap3.size() == k) {
      ok3 = 1;
      break;
    }
    heap3.erase(heap3.begin());
    degs[v] = 0;
    for (auto u : adj[v]) {
      if (degs[u] == 0) { continue; }
      heap3.erase({degs[u], u});
      heap3.insert({degs[u] -= 1, u});
    }
  }
  if (!ok3) { cout << -1 << "\n"; return; }

  {
    cout << 2 << "\n";
    auto sep = "";
    for (auto [d, v] : heap3) {
      cout << sep << (v + 1); sep = " ";
    }
    cout << "\n";
    return;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest/1440/d/main.cpp

%%%% begin
3
5 9 4
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
10 15 3
1 2
2 3
3 4
4 5
5 1
1 7
2 8
3 9
4 10
5 6
7 10
10 8
8 6
6 9
9 7
4 5 4
1 2
2 3
3 4
4 1
1 3
%%%%
2
4 1 2 3
1 10
1 2 3 4 5 6 7 8 9 10
-1
%%%% end
*/
