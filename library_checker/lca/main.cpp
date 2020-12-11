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

struct HeavyLightDecomposition {
  vector<int> depths;
  vector<int> sizes;
  vector<int> parents;
  vector<int> klasses;

  HeavyLightDecomposition(const vector<vector<int>>& adj, int root) {
    int n = adj.size();
    depths.assign(n, 0);
    sizes.assign(n, 0);
    parents.assign(n, 0);
    klasses.assign(n, 0);

    function<void(int, int)> dfs = [&](int v, int vp) {
      sizes[v] = 1;
      for (auto u : adj[v]) {
        if (u == vp) { continue; }
        depths[u] = depths[v] + 1;
        parents[u] = v;
        dfs(u, v);
        sizes[v] += sizes[u];
      }
    };
    dfs(root, -1);

    function<void(int, int, int)> dfs2 = [&](int v, int vp, int klass) {
      klasses[v] = klass;
      for (auto u : adj[v]) {
        if (u == vp) { continue; }
        dfs2(u, v, (2 * sizes[u] < sizes[v]) ? u : klass);
      }
    };
    dfs2(root, -1, root);
  }

  int getLCA(int x, int y) {
    while (klasses[x] != klasses[y]) {
      if (depths[klasses[x]] > depths[klasses[y]]) { swap(x, y); }
      y = parents[klasses[y]];
    }
    if (depths[x] > depths[y]) { swap(x, y); }
    return x;
  }
};

// Main
void mainCase() {
  int n, nq; // <= 5 x 10^5
  cin >> n >> nq;
  vector<int> parents(n - 1);
  cin >> parents;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  vector<vector<int>> adj(n);
  FOR(i, 1, n) {
    adj[parents[i - 1]].push_back(i);
  }

  HeavyLightDecomposition hld(adj, 0);

  for (auto [x, y] : qs) {
    auto res = hld.getLCA(x, y);
    cout << res << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/lca/main.cpp

%%%% begin
5 5
0 0 2 2
0 1
0 4
1 2
2 3
3 4
%%%%
0
0
0
2
2
%%%% end
*/
