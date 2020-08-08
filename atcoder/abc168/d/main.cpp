// Virtual, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
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
void mainCase() {
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> edges(m, {0, 0});
  cin >> edges;

  vector<vector<int>> adj(n, vector<int>(0, 0));
  RANGE(i, 0, m) {
    auto [x, y] = edges[i];
    adj[x - 1].push_back(y - 1); // zero-based index
    adj[y - 1].push_back(x - 1);
  }

  vector<int> distances(n, -1);
  vector<int> parents(n, -1);

  // Min heap
  set<tuple<int, int, int>> heap; // (distance, vertex, parent)
  heap.insert({0, 0, -1});
  while (!heap.empty()) {
    auto top = heap.begin();
    auto [dist, v0, p0] = *top;  heap.erase(top);
    if (distances[v0] != -1) { continue; }
    distances[v0] = dist;
    parents[v0] = p0;
    for (auto v1 : adj[v0]) {
      if (distances[v1] != -1) { continue; }
      heap.insert({dist + 1, v1, v0});
    }
  }
  // DD(adj);
  // DD(edges);
  // DD(distances);
  // DD(parents);

  bool disconn = false;
  RANGE(i, 0, n) {
    if (distances[i] == -1) {
      disconn = true;
      break;
    }
  }

  if (disconn) {
    cout << "No" << endl;
    return;
  }

  cout << "Yes" << endl;
  RANGE(i, 1, n) {
    int j = parents[i] + 1; // one-based index
    cout << j << endl;
  }
}

int main() {
  mainCase();
  return 0;
}

/*
python misc/run.py atcoder/abc168/d/main.cpp --check

%%%% begin
4 4
1 2
2 3
3 4
4 2
%%%%
Yes
1
2
2
%%%% end

%%%% begin
6 9
3 4
6 1
2 4
5 3
4 6
1 5
6 2
4 5
5 6
%%%%
Yes
6
5
5
1
1
%%%% end
*/
