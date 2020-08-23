// WA

// PROP: It's necessary and sufficient to save all leaves.
// TODO: or maybe not? or some cheap bug?

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
  int n; // <= 10^5, >= 3
  cin >> n;
  vector<tuple<int, int>> edges(n - 1, {0, 0});
  cin >> edges;
  for (auto& [x, y] : edges) { x--; y--; }

  vector<vector<int>> adj(n);
  for (auto [x, y] : edges) {
    adj[x].push_back(y); swap(x, y);
    adj[x].push_back(y);
  }
  // DD2(adj);

  vector<int> ls; // leaves
  FOR(i, 0, n) {
    if (adj[i].size() == 1) {
      ls.push_back(i);
    }
  }
  int k = ls.size();
  // DD(ls);

  vector<tuple<int, int>> new_edges;
  FOR(i, 0, k / 2) {
    new_edges.push_back({ls[i], ls[i + k / 2]});
  }
  if (k % 2 == 1) {
    new_edges.push_back({ls[0], ls.back()});
  }
  // DD(new_edges);

  cout << new_edges.size() << endl;
  for (auto [x, y] : new_edges) {
    x++; y++;
    cout << x << " " << y << endl;
  }
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
python misc/run.py cses/additional_problems/task1704/main.cpp --check

%%%% begin
5
1 2
1 3
3 4
3 5
%%%%
2
2 4
4 5
%%%% end
*/
