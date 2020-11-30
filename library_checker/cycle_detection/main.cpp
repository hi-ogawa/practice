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
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Main
void mainCase() {
  int n, m;
  cin >> n >> m;
  vector<array<int, 2>> edges(m); // [0, n)
  cin >> edges;

  vector<vector<array<int, 2>>> adj(n);
  FOR(i, 0, m) {
    auto [x, y] = edges[i];
    adj[x].push_back({y, i});
  }

  // DFS tree
  vector<array<int, 2>> parents(n, {-1, -1}); // (parent vertex, edge)
  vector<int> out_times(n);
  vector<bool> done(n);
  int time = 0;
  function<void(int)> dfs = [&](int v) {
    done[v] = 1;
    for (auto [u, e] : adj[v]) {
      if (done[u]) { continue; }
      parents[u] = {v, e};
      dfs(u);
    }
    out_times[v] = time++;
  };
  FOR(i, 0, n) {
    if (done[i]) { continue; }
    dfs(i);
  }

  // Find back edge by out-time
  int found = -1;
  FOR(i, 0, m) {
    auto [x, y] = edges[i];
    if (out_times[y] > out_times[x]) {
      found = i;
      break;
    }
  }
  if (found == -1) { cout << -1 << "\n"; return; }

  // Back track parents
  vector<int> res;
  auto [x0, y0] = edges[found];
  int x = x0;
  while (x != y0) {
    auto [xp, e] = parents[x];
    assert(xp != -1);
    x = xp;
    res.push_back(e);
  }
  res.push_back(found);
  reverse(ALL(res));

  cout << res.size() << "\n";
  for (auto r : res) {
    cout << r << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/cycle_detection/main.cpp

%%%% begin
5 7
0 3
0 4
4 2
4 3
4 0
2 1
1 0
%%%%
4
1
2
5
6
%%%% end

%%%% begin
2 1
1 0
%%%%
-1
%%%% end

%%%% begin
4 6
0 1
1 2
2 0
0 1
1 3
3 0
%%%%
3
0
1
2
%%%% end
*/
