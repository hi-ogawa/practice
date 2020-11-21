// CONTEST, AC

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
  int n, m; // [1, 2 x 10^5]
  cin >> n >> m;
  vector<array<int, 3>> edges(m); // label \in [1, n], connected
  cin >> edges;

  vector<vector<array<int, 2>>> adj(n);
  for (auto [x, y, z] : edges) {
    x--; y--;
    adj[x].push_back({y, z});
    adj[y].push_back({x, z});
  }

  vector<int> res(n, -1);
  vector<int> done(n);

  // Find DFS tree edges
  function<void(int)> dfs = [&](int v) {
    done[v] = 1;
    for (auto [u, c] : adj[v]) {
      if (done[u]) { continue; }
      // Assign tree edge when it's different from parent
      if (res[v] != c) {
        res[u] = c;
      }
      dfs(u);
    }
  };
  dfs(0);

  dbg(res);

  // Assign remaining number if not assigned yet
  set<int> used(ALL(res));
  int rem = -1;
  FOR(i, 1, n + 1) {
    if (!used.count(i)) {
      rem = i;
      break;
    }
  }
  assert(rem != -1);

  FOR(i, 0, n) {
    auto x = res[i];
    if (x == -1) { x = rem; }
    cout << x << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/arc108/c/main.cpp

%%%% begin
3 4
1 2 1
2 3 2
3 1 3
1 3 1
%%%%
1
2
1
%%%% end
*/
