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

// Cf. codeforces/edu/dsu/3/a/main.cpp
struct Dsu {
  vector<int> parents;
  vector<int> sizes;
  vector<array<int, 2>> history;
  vector<int> checkpoints;

  Dsu(int n) {
    parents.resize(n);
    iota(ALL(parents), 0);
    sizes.assign(n, 1);
  }

  int find(int x) {
    if (x == parents[x]) { return x; }
    return parents[x] = find(parents[x]);
  }

  void merge(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) { return; }
    if (sizes[x] > sizes[y]) { swap(x, y); }

    parents[x] = y;
    sizes[y] += sizes[x];
    history.push_back({x, y});
  }

  void persist() {
    checkpoints.push_back(history.size());
  }

  void rollback() {
    int c = checkpoints.back(); checkpoints.pop_back();
    while ((int)history.size() > c) {
      auto [x, y] = history.back(); history.pop_back();
      parents[x] = x;
      sizes[y] -= sizes[x];
    }
  }
};


// Main
void mainCase() {
  int n, nq; // [1, 2 x 10^5]
  cin >> n >> nq;
  vector<array<int, 4>> qs(nq);
  cin >> qs;

  // Offset by one to eliminate "-1"
  for (auto& [t, k, x, y] : qs) { k++;}
  qs.insert(qs.begin(), {-1});
  nq++;

  // Query dependency tree
  vector<vector<int>> adj(nq);
  FOR(i, 1, nq) {
    adj[qs[i][1]].push_back(i);
  }

  // Answer query along DFS tree
  Dsu dsu(n);
  vector<int> res(nq);

  function<void(int)> dfs = [&](int v) {
    for (auto u : adj[v]) {
      auto [t, _k, x, y] = qs[u];
      if (t == 0) {
        dsu.persist();
        dsu.merge(x, y);
        dfs(u);
        dsu.rollback();
      }
      if (t == 1) {
        res[u] = (dsu.find(x) == dsu.find(y));
      }
    }
  };
  dfs(0);

  FOR(i, 1, nq) {
    if (qs[i][0] == 1) {
      cout << res[i] << "\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/persistent_unionfind/main.cpp

%%%% begin
5 12
0 -1 0 1
0 0 0 2
1 -1 0 1
1 0 0 1
1 1 0 1
0 1 3 4
0 1 2 3
1 5 1 4
0 5 2 3
1 8 1 4
0 6 3 4
1 10 1 4
%%%%
0
1
1
0
1
1
%%%% end
*/
