// WA

// TODO: Prove "incorrectness" of this approach (i.e. small counter example)

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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, m; // n, m <= 10^6
  cin >> n >> m;

  vector<array<ll, 2>> edges(m, {0, 0});
  cin >> edges;

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
  }
  int v_beg = 0, v_end = n - 1;

  // BFS
  // TODO: For DAG, find bound of the size of queue
  vector<int> parents(n, -1);
  deque<int> queue;
  queue.push_back(v_beg);
  while (!queue.empty()) {
    // DD(queue);
    auto v = queue.front(); queue.pop_front();
    for (auto u : adj[v]) {
      // If already visited, only update parents, which always makes longer path.
      if (parents[u] == -1) {
        queue.push_back(u);
      }
      parents[u] = v;
    }
  }
  // DD(parents);

  if (parents[v_end] == -1) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }

  vector<int> res;
  int v = v_end;
  while (v != v_beg) {
    res.push_back(v);
    v = parents[v];
  }
  res.push_back(v_beg);
  reverse(ALL(res));
  // DD(res);

  cout << res.size() << endl;
  FOR(i, 0, (int)res.size()) {
    if (i) cout << " ";
    cout << (res[i] + 1);
  }
  cout << endl;
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
python misc/run.py cses/graph_algorithms/task1680/main.cpp --check

%%%% begin
5 5
1 2
2 5
1 3
3 4
4 5
%%%%
4
1 3 4 5
%%%% end
*/
