// AC

// TODO: this solution completely relies on there's no hash collision

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

  // 64bit hash by Chris Wellons https://nullprogram.com/blog/2018/07/31/
  auto hash = [](ull x) -> ull {
    x ^= x >> 30;
    x *= 0xbf58476d1ce4e5b9ULL;
    x ^= x >> 27;
    x *= 0x94d049bb133111ebULL;
    x ^= x >> 31;
    return x;
  };

  // Take hash of path by degree (and just wish no hash collision...)
  auto solve = [&](const vector<vector<int>>& adj) -> vector<ull> {
    vector<ull> res(n, 0);
    vector<bool> done(n, 0);
    deque<tuple<int, ull>> q;
    q.push_back({0, 0});
    done[0] = 1;
    while (!q.empty()) {
      auto [v, h] = q.front(); q.pop_front();
      res[v] = h = hash(h ^ adj[v].size());
      for (auto u : adj[v]) {
        if (!done[u]) {
          done[u] = 1;
          q.push_back({u, h});
        }
      }
    }
    return res;
  };

  auto hs1 = solve(adj1);
  auto hs2 = solve(adj2);
  sort(ALL(hs1));
  sort(ALL(hs2));
  dbg(hs1);
  dbg(hs2);

  bool res = hs1 == hs2;
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
python misc/run.py cses/additional_problems/task1700/main.cpp --check

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
NO
YES
%%%% end
*/
