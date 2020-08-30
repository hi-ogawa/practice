// AC

// NOTE: After finding "center (centers)" of the tree, use same hash-cheating as task1700.

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

// 64bit hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
ull hash64(ull x) {
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9ULL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebULL;
  x ^= x >> 31;
  return x;
};

// Main
void mainCase() {
  int n;
  cin >> n;
  vector<tuple<int, int>> edges1(n - 1, {0, 0});
  vector<tuple<int, int>> edges2(n - 1, {0, 0});
  cin >> edges1 >> edges2;
  for (auto& [x, y] : edges1) { x--; y--; }
  for (auto& [x, y] : edges2) { x--; y--; }

  vector<vector<int>> adj1(n);
  vector<vector<int>> adj2(n);
  for (auto [x, y] : edges1) {
    adj1[x].push_back(y);
    adj1[y].push_back(x);
  }
  for (auto [x, y] : edges2) {
    adj2[x].push_back(y);
    adj2[y].push_back(x);
  }

  auto getCenters = [&](const vector<vector<int>>& adj) -> vector<int> {
    vector<int> deg(n, 0);
    FOR(v, 0, n) {
      for (auto u : adj[v]) { deg[u]++; }
    }
    set<tuple<int, int>> pq;
    FOR(v, 0, n) { pq.insert({deg[v], v}); }

    while (pq.size() > 2) {
      vector<int> removed;
      set<tuple<int, int>> decreased;
      for (auto [d, v]: pq) {
        if (d > 1) { break; }
        removed.push_back(v);
        for (auto u : adj[v]) {
          if (deg[u] > 0) {
            decreased.insert({deg[u], u});
          }
        }
      }
      for (auto v : removed) {
        pq.erase({1, v});
        deg[v]--;
        for (auto u : adj[v]) {
          if (deg[u] > 0) {
            deg[u]--;
          }
        }
      }
      for (auto [d, v] : decreased) {
        pq.erase({d, v});
        pq.insert({deg[v], v});
      }
    }

    vector<int> res;
    for (auto [_d, v] : pq) { res.push_back(v); }
    return res;
  };

  // Same approach (cheat) as task1700
  auto getHash = [&](int root, const vector<vector<int>>& adj) -> vector<ull> {
    vector<ull> res(n, 0);
    vector<bool> done(n, 0);
    deque<tuple<int, ull>> q;
    q.push_back({root, 0});
    done[root] = 1;
    while (!q.empty()) {
      auto [v, h] = q.front(); q.pop_front();
      res[v] = h = hash64(h ^ adj[v].size());
      for (auto u : adj[v]) {
        if (!done[u]) {
          done[u] = 1;
          q.push_back({u, h});
        }
      }
    }
    return res;
  };

  auto cs1 = getCenters(adj1);
  auto cs2 = getCenters(adj2);
  vector<vector<ull>> hs1, hs2;
  for (auto c : cs1) { hs1.emplace_back() = getHash(c, adj1); }
  for (auto c : cs2) { hs2.emplace_back() = getHash(c, adj2); }
  for (auto& h : hs1) { sort(ALL(h)); }
  for (auto& h : hs2) { sort(ALL(h)); }
  dbg(cs1);
  dbg(cs2);
  dbg2(hs1);
  dbg2(hs2);

  bool res = 0;
  for (auto& h1 : hs1) {
    for (auto& h2 : hs2) {
      if (h1 == h2) { res = 1; break; }
    }
  }
  cout << (res ? "YES" : "NO") << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1701/main.cpp --check

%%%% begin
1
7
5 3
3 1
2 7
2 3
6 1
4 5
4 3
3 5
6 7
3 6
2 4
1 5
%%%%
YES
%%%% end

%%%% begin
2
3
1 2
2 3
1 2
1 3
3
1 2
2 3
1 3
3 2
%%%%
YES
YES
%%%% end
*/
