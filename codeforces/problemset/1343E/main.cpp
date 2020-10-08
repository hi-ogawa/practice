// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
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
  int n, m, a, b, c; // [2, 2 x 10^5]
  cin >> n >> m >> a >> b >> c;
  vector<int> ps(m); // [1, 10^9]
  cin >> ps;
  vector<array<int, 2>> edges(m); // connected
  cin >> edges;
  a--; b--; c--;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  auto bfs = [&](int root, vector<int>& dists) {
    deque<int> q;
    q.push_back(root);
    fill(ALL(dists), 1e9);
    dists[root] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop_front();
      int d = dists[v] + 1;
      for (auto u : adj[v]) {
        if (d < dists[u]) {
          dists[u] = d;
          q.push_back(u);
        }
      }
    }
  };

  // Get d(v, a), d(v, b), d(v, c)
  vector<int> a_dists(n), b_dists(n), c_dists(n);
  bfs(a, a_dists);
  bfs(b, b_dists);
  bfs(c, c_dists);

  // From smaller ones, take d(v, b) x 2, d(v, a) + d(v, c)
  sort(ALL(ps));
  vector<ll> qs(m + 1); // cumsum
  FOR(i, 0, m) { qs[i + 1] = qs[i] + ps[i]; }

  ll res = 1e18;
  FOR(v, 0, n) {
    int da = a_dists[v], db = b_dists[v], dc = c_dists[v];
    if (da + db + dc > m) { continue; } // TODO: really???
    ll t = qs[da + db + dc] + qs[db];
    res = min(res, t);
  }
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1343E/main.cpp

%%%% begin
2
4 3 2 3 4
1 2 3
1 2
1 3
1 4
7 9 1 5 7
2 10 4 8 5 6 7 3 3
1 2
1 3
1 4
3 2
3 5
4 2
5 6
1 7
6 7
%%%%
7
12
%%%% end
*/
