// AC

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y){X}; I < (Y); ++I)
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
  int n; // [1, 2 x 10^5]
  cin >> n;
  vector<array<int, 2>> edges(n - 1);
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y]: edges) {
    x--;
    y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }

  // Subtree sizes wrt arbitrary root (here x = 0)
  vector<bool> visited(n, false);
  vector<int> centroids;

  function<int(int)> runDFS = [&](int x) -> int {
    assert(!visited[x]);
    visited[x] = true;
    int size = 1;
    bool is_centroid = true;

    for (auto y: adj[x]) {
      if (visited[y]) continue;
      int y_size = runDFS(y);
      is_centroid = is_centroid && y_size <= n / 2;
      size += y_size;
    }

    is_centroid = is_centroid && size > n / 2;
    if (is_centroid) {
      centroids.push_back(x);
    }
    return size;
  };
  runDFS(0);

  assert(!centroids.empty());
  int res = centroids[0] + 1;
  cout << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py cses/tree_algorithms/task2079/main.cpp

%%%% begin
5
1 2
2 3
3 4
3 5
%%%%
3
%%%% end
*/
