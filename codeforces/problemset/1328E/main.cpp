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
  int n, nq;
  cin >> n >> nq;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;
  vector<vector<int>> qs(nq);
  FOR(i, 0, nq) {
    int k;
    cin >> k;
    qs[i].resize(k);
    cin >> qs[i];
  }
  for (auto& [x, y] : edges) { x--; y--; }
  for (auto& vs : qs) { for (auto& x : vs) { x--; }}

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // BFS for depth/parent
  int root = 0;
  vector<int> depths(n);
  vector<int> parents(n, -1);
  {
    deque<int> q;
    q.push_back(root);
    parents[root] = root;
    depths[root] = 0;
    while(!q.empty()) {
      int v = q.front(); q.pop_front();
      for (auto u : adj[v]) {
        if (parents[u] == -1) {
          parents[u] = v;
          depths[u] = depths[v] + 1;
          q.push_back(u);
        }
      }
    }
  }
  dbg(depths);
  dbg(parents);

  // Binary lifting
  int b_lim = 0; // n < 2^b
  while ((1 << b_lim) <= n) { b_lim++; }
  vector<vector<int>> table(b_lim, vector<int>(n));
  table[0] = parents;
  FOR(b, 1, b_lim) {
    FOR(v, 0, n) {
      table[b][v] = table[b - 1][table[b - 1][v]];
    }
  }
  auto lift = [&](int v, int e) -> int {
    int b = 0;
    while (e > 0) {
      if (e & 1) { v = table[b][v]; }
      e >>= 1; b++;
    }
    return v;
  };

  // Answer query
  auto solve = [&](const vector<int>& vs) -> bool {
    // depth to vertices
    map<int, vector<int>> d2vs;
    for (auto v : vs) { d2vs[depths[v]].push_back(v); }

    bool ok = 1;
    while (!d2vs.empty()) {
      auto [d, us] = *d2vs.rbegin(); // TODO: if we use "auto&", then "d2vs.erase(d)" gets sketchy...
      if (d == 0) { break; }

      if (us.size() == 1) {
        // Lift to next depth as an optimization (Time = |vs|)
        if (d2vs.size() == 1) { break; }
        int v = us[0];
        int dd = next(d2vs.rbegin())->first;
        int vv = lift(v, d - dd);
        d2vs.erase(d);
        d2vs[dd].push_back(vv);
        continue;
      }

      // Check they have same parent
      int p = parents[us[0]];
      for (auto v : us) {
        if (parents[v] != p) { ok = 0; break; }
      }
      if (!ok) { break; }

      // Push to next
      d2vs.erase(d);
      d2vs[d - 1].push_back(p);
    }
    return ok;
  };

  // Answer queries
  for (auto& vs : qs) {
    bool res = solve(vs);
    cout << (res ? "YES" : "NO") << endl;
  }
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
python misc/run.py codeforces/problemset/1328E/main.cpp --check

%%%% begin
10 6
1 2
1 3
1 4
2 5
2 6
3 7
7 8
7 9
9 10
4 3 8 9 10
3 2 4 6
3 2 1 5
3 4 8 2
2 6 10
3 5 4 7
%%%%
YES
YES
YES
YES
NO
NO
%%%% end
*/
