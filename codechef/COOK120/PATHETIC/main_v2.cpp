// AFTER EDITORIAL

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
template<class ...Ts> ostream&        operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T> ostream&            operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }

// Main
vector<ll> solve(const vector<tuple<int, int>>& edges) {
  int n = edges.size() + 1;
  vector<vector<int>> adj(n, vector<int>(0, 0));
  for (auto [x, y] : edges) {
    adj[x - 1].push_back(y - 1); // Zero-based index
    adj[y - 1].push_back(x - 1);
  }

  // cf. main_v2_precompute.cpp
  ll q1 = 1416919933790871510; // product of {2, 3, 5, 7, 11, 13, 17, 19, 29, 31, 37, 41, 43, 47, 53}
  ll q2 = 1627168839228008057; // product of {23, 59, 61, 67, 71, 73, 79, 83, 89, 97}

  // Traverse graph and assign q1 or q2 alternatingly
  vector<ll> result(n, 1);
  vector<bool> visited(n, 0);
  vector<int> stack(0, 0);
  stack.push_back(0);
  visited[0] = 1;
  result[0] = q1;
  while (!stack.empty()) {
    auto u = stack.back();
    stack.pop_back();
    for (auto v : adj[u]) {
      if (visited[v]) { continue; }
      stack.push_back(v);
      visited[v] = 1;
      result[v] = (result[u] == q1) ? q2 : q1;
    }
  }
  return result;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) {
    int n;
    cin >> n;
    vector<tuple<int, int>> ls(n - 1, {0, 0});
    RANGE(j, 0, n - 1) {
      cin >> get<0>(ls[j]) >> get<1>(ls[j]);
    }
    auto result = solve(ls);
    RANGE(j, 0, n) {
      if (j > 0) cout << " ";
      cout << result[j];
    }
    cout << endl;
  }
  return 0;
}

/*
python misc/run.py codechef/COOK120/PATHETIC/main_v2.cpp --check

%%%% begin
2
6
1 2
2 3
1 4
5 1
6 5
2
1 2
%%%%
2 3 2 4 6 5
1 2
%%%% end
*/
