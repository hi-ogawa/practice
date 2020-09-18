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
  int n; // < 10^6
  cin >> n;
  vector<array<ll, 3>> ls(n);
  cin >> ls;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  ll res = 0;
  vector<array<array<int, 2>, 2>> cnts(n); // count 0/1 -> 0/1 in subtree
  vector<ll> cost(n);
  cost[0] = ls[0][0];

  function<void(int, int)> dfs = [&](int v, int parent) {
    cnts[v][ls[v][1]][ls[v][2]]++;
    for (auto u : adj[v]) {
      if (u == parent) { continue; }
      cost[u] = min(cost[v], ls[u][0]); // We can fix subtree by cumulative minimum along ancestors
      dfs(u, v);
      for (auto b : {0, 1}) {
        for (auto c : {0, 1}) {
          cnts[v][b][c] += cnts[u][b][c];
        }
      }
    }
    // Fix as much as possible
    int k = min(cnts[v][0][1], cnts[v][1][0]);
    cnts[v][0][0] += k;
    cnts[v][0][1] -= k;
    cnts[v][1][0] -= k;
    cnts[v][1][1] += k;
    res += 2 * k * cost[v];
  };
  dfs(0, 0);
  dbg(cost);
  dbg(cnts);

  // Check 0/1 balance is correct
  bool ok = cnts[0][0][1] == 0 && cnts[0][1][0] == 0;
  if (!ok) { cout << -1 << endl; return; }

  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1363E/main_v2.cpp --check

%%%% begin
5
1 0 1
20 1 0
300 0 1
4000 0 0
50000 1 0
1 2
2 3
2 4
1 5
%%%%
4
%%%% end

%%%% begin
5
10000 0 1
2000 1 0
300 0 1
40 0 0
1 1 0
1 2
2 3
2 4
1 5
%%%%
24000
%%%% end

%%%% begin
2
109 0 1
205 0 1
1 2
%%%%
-1
%%%% end
*/
