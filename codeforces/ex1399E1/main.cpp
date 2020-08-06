// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts> istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T>     istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
int solve(ll score_goal, vector<tuple<int, int, int>>& edges) {
  int n = edges.size() + 1;

  // Adjacency list
  vector<vector<tuple<int, int>>> adj(n, vector<tuple<int, int>>());
  RANGE(i, 0, n - 1) {
    auto [u, v, _w] = edges[i];
    adj[u - 1].push_back({v - 1, i}); // Zero-based index
    adj[v - 1].push_back({u - 1, i});
  }

  // Count each leaf's contribution to the score
  vector<ll> edge_leaf_counts(n - 1, 0);
  vector<bool> visited(n, 0);
  function<int(int)> dfsRec = [&](int u) {
    int c = 0;
    bool is_leaf = true;
    for (auto [v, e] : adj[u]) {
      if (visited[v]) { continue; }
      visited[v] = 1;
      int ce = dfsRec(v);
      edge_leaf_counts[e] = ce;
      c += ce;
      is_leaf = false;
    }
    return is_leaf ? 1 : c;
  };
  visited[0] = 1;
  dfsRec(0);
  #ifdef DEBUG
    DD(adj);
    DD(edge_leaf_counts);
  #endif

  // "Gain" when chosen edge is halved
  ll score = 0;
  vector<int> edge_weights(n - 1, 0);
  set<tuple<ll, int>, greater<tuple<ll, int>>> edge_gains; // balanced tree
  RANGE(i, 0, n - 1) {
    auto [_u, _v, w] = edges[i];
    edge_weights[i] = w;
    score += edge_leaf_counts[i] * w;
    ll gain = edge_leaf_counts[i] * ((w + 1) / 2);
    edge_gains.insert({gain, i});
  }
  #ifdef DEBUG
    DD(score);
    DD(edge_gains);
    DD(*edge_gains.begin());
  #endif

  // Repeatedly choose edge with maximul gain
  int num_ops = 0;
  while (score > score_goal) {
    num_ops++;
    // Pick max gain
    auto top = edge_gains.begin();
    auto [gain, e] = *top;
    edge_gains.erase(top);
    score -= gain;

    // Update data
    int w = edge_weights[e];
    int new_w = w / 2;
    ll new_gain = edge_leaf_counts[e] * ((new_w + 1) / 2);
    edge_weights[e] = new_w;
    edge_gains.insert({new_gain, e});
  }
  return num_ops;
}

void mainCase() {
  int n;
  ll s;
  cin >> n >> s;
  vector<tuple<int, int, int>> edges(n - 1, {0, 0, 0});
  cin >> edges;
  cout << solve(s, edges) << endl;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codeforces/ex1399E1/main.cpp --check

%%%% begin
1
5 50
1 3 100
1 5 10
2 3 123
5 4 55
%%%%
8
%%%% end

%%%% begin
3
3 20
2 1 8
3 1 7
5 50
1 3 100
1 5 10
2 3 123
5 4 55
2 100
1 2 409
%%%%
0
8
3
%%%% end
*/
