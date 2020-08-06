// AFTER EDITORIAL, WIP

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
int solve(ll score_goal, vector<tuple<int, int, int, int>>& edges) {
  int n = edges.size() + 1;

  // Adjacency list
  vector<ll> costs(n - 1, 0);
  vector<ll> weights(n - 1, 0);
  vector<vector<tuple<int, int>>> adj(n, vector<tuple<int, int>>());
  RANGE(i, 0, n - 1) {
    auto [u, v, w, c] = edges[i];
    adj[u - 1].push_back({v - 1, i}); // Zero-based index
    adj[v - 1].push_back({u - 1, i});
    weights[i] = w;
    costs[i] = c;
  }

  // Count leaf path per edge
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

  // "Gain" when chosen edge is halved
  ll score = 0; // Initial score
  set<tuple<ll, int>, greater<tuple<ll, int>>> gains; // for single cost
  set<tuple<ll, int>, greater<tuple<ll, int>>> gains2; // for double cost
  RANGE(i, 0, n - 1) {
    int w0 = weights[i];
    int w1 = w0 / 2;
    int w2 = w1 / 2;
    score += edge_leaf_counts[i] * w0;
    ll gain = edge_leaf_counts[i] * (w0 - w1);
    ll gain2 = edge_leaf_counts[i] * (w0 - w2);
    if (costs[i] == 1) {
      gains.insert({gain, i});
      gains2.insert({gain2, i});
    }
    if (costs[i] == 2) {
      gains2.insert({gain, i});
    }
  }

  DD(adj);
  DD(costs);

  // Repeat operations
  int total_cost = 0;
  while (score > score_goal) {
    DD(score);
    DD(weights);
    DD(gains);
    DD(gains2);

    // Check if single op gain suffices
    if (!gains.empty()) {
      auto [gain, e] = *gains.begin();
      if (score - gain <= score_goal) {
        total_cost++;
        score -= gain;
        break;
      }
    }

    // Otherwise pick double op
    total_cost += 2;
    auto top = gains2.begin();
    auto [gain2, i] = *top;
    gains2.erase(top);
    score -= gain2;

    // Update gains
    int w0 = weights[i];
    int w1 = w0 >> 1;
    int w2 = w0 >> 2;
    int w3 = w0 >> 3;
    int w4 = w0 >> 4;
    if (costs[i] == 1) {
      ll old_gain = edge_leaf_counts[i] * (w0 - w1);
      ll new_gain = edge_leaf_counts[i] * (w2 - w3);
      ll new_gain2 = edge_leaf_counts[i] * (w2 - w4);
      weights[i] = w2;
      gains.erase({old_gain, i});
      gains.insert({new_gain, i});
      gains2.insert({new_gain2, i});
    }
    if (costs[i] == 2) {
      weights[i] = w1;
      ll new_gain = edge_leaf_counts[i] * (w1 - w2);
      gains2.insert({new_gain, i});
    }
  }

  return total_cost;
}

void mainCase() {
  int n;
  ll s;
  cin >> n >> s;
  vector<tuple<int, int, int, int>> edges(n - 1, {0, 0, 0, 0});
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
python misc/run.py codeforces/ex1399E2/main.cpp --check

%%%% begin
1
5 50
1 3 100 1
1 5 10 2
2 3 123 2
5 4 55 1
%%%%
11
%%%% end

%%%% begin
1
2 100
1 2 409 2
%%%%
6
%%%% end

%%%% begin
4
4 18
2 1 9 2
3 2 4 1
4 1 1 2
3 20
2 1 8 1
3 1 7 2
5 50
1 3 100 1
1 5 10 2
2 3 123 2
5 4 55 1
2 100
1 2 409 2
%%%%
0
0
11
6
%%%% end
*/
