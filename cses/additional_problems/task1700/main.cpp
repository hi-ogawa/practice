// WIP

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
  int n;
  cin >> n;
  vector<tuple<int, int>> edges1(n - 1, {0, 0});
  vector<tuple<int, int>> edges2(n - 1, {0, 0});
  cin >> edges1 >> edges2;
  for (auto& [x, y] : edges1) { x--; y--; }
  for (auto& [x, y] : edges2) { x--; y--; }

  vector<vector<int>> adj1(n);
  vector<vector<int>> adj2(n);
  for (auto [x, y] : edges1) {
    adj1[x].push_back(y); swap(x, y);
    adj1[x].push_back(y);
  }
  for (auto [x, y] : edges2) {
    adj2[x].push_back(y); swap(x, y);
    adj2[x].push_back(y);
  }

  // BFS with each depth layer ordered by degree,
  // then check degree matches.
  // TODO: this is only necessary condition for isomorphism...
  set<tuple<int, int>> q1, q1_next;
  set<tuple<int, int>> q2, q2_next;
  q1.insert({adj1[0].size(), 0});
  q2.insert({adj2[0].size(), 0});
  // bool res = 1;
  // while (true) {
  //   swap(q1, q1_next);
  //   swap(q2, q2_next);
  // }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py cses/additional_problems/task1700/main.cpp --check

%%%% begin
2
3
1 2
2 3
1 2
1 3
3
1 2
2 3
1 3
3 2
%%%%
NO
YES
%%%% end
*/
