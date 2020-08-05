// AFTER CONTEST, WA

#include <bits/stdc++.h>

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (decltype(X) I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
namespace std { template<class ...Ts> ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "{"; apply([&](auto&&... ys){ ((o << ys << ", "), ...); }, x); o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; } }
namespace std { template<class T> ostream& operator<<(ostream& o, const vector<T>& x) { o << "{"; for (auto& y : x) { o << y << ", "; } o << "}"; return o; } }
namespace std { template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x) { o << "{"; for (auto& yz : x) { o << yz << ", "; } o << "}"; return o; } }

// Main
using namespace std;

vector<ll> solve(const vector<tuple<int, int>>& edges) {
  int n = edges.size() + 1;
  vector<ll> values(n, 1);
  vector<vector<int>> adj(n, vector<int>(0, 0));
  for (auto [x, y] : edges) {
    adj[x - 1].push_back(y - 1); // Zero-based index
    adj[y - 1].push_back(x - 1);
  }
  #ifdef DEBUG
    DD(adj);
  #endif

  // TODO:
  // 1. this approach doesn't guarantee bound
  // 2. this counts all maximul path twice, which is redundant.

  // Enumerate all maximul path (i.e. leaf-to-leaf path)
  RANGE(i, 0, n) {
    if (adj[i].size() > 1) { continue; }

    // Assign value for each path as sequence 1, 2, ...
    vector<tuple<int, int, int>> stack(0);
    stack.push_back({i, -1, 1});
    while (!stack.empty()) {
      #ifdef DEBUG
        DD(stack);
      #endif
      auto [j1, j0, p] = stack.back();
      values[j1] = lcm(values[j1], p);
      stack.pop_back();
      for (auto k : adj[j1]) {
        if (k == j0) { continue; }
        stack.push_back({k, j1, p + 1});
      }
    }
  }

  return values;
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
python misc/run.py codechef/COOK120/PATHETIC/main.cpp --check

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
