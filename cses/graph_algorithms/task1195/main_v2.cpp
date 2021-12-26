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

constexpr ll kInf = 1e18;

// Main
void mainCase() {
  int n, m; // ~ 10^5
  cin >> n >> m;
  vector<tuple<int, int, int>> edges(m); // weight ~ 10^9
  cin >> edges;
  for (auto& [a, b, _]: edges) {
    a--;
    b--;
  }

  using Adj = vector<vector<tuple<int, int>>>;
  Adj adj(n);
  Adj adj_inv(n);
  for (auto [a, b, c]: edges) {
    adj[a].push_back({b, c});
    adj_inv[b].push_back({a, c});
  }

  // Find shortes paths from two start points ("0" and "n-1")
  auto solve = [&](int start, Adj& adj) -> vector<ll> {
    vector<ll> costs(n, kInf);
    set<tuple<ll, int>> heap;
    heap.insert({0, start});
    while (!heap.empty()) {
      auto [w, a] = *heap.begin();
      heap.erase(heap.begin());
      if (costs[a] != kInf) continue;
      costs[a] = w;
      for (auto [b, c]: adj[a]) {
        if (costs[b] != kInf) continue;
        heap.insert({ w + c, b });
      }
    }
    return costs;
  };

  auto costs1 = solve(0, adj);
  auto costs2 = solve(n - 1, adj_inv);

  // Find discounted shortest path of these forms
  //  "0" ... "a" - "b" ... "n-1"
  ll result = kInf;
  for (auto [a, b, c]: edges) {
    result = min(result, costs1[a] + costs2[b] + c / 2);
  }
  cout << result << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py /home/hiroshi/code/personal/practice/cses/graph_algorithms/task1195/main_v2.cpp

%%%% begin
3 4
1 2 3
2 3 1
1 3 7
2 1 5
%%%%
2
%%%% end
*/
