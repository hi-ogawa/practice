// AFTER EDITORIAL, AC

//
// PROP.
//   degree(v) = Prufer-frequency(v) + 1
//

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
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  int n; // <= 10^6
  cin >> n;
  vector<int> ls(n - 2, 0);
  cin >> ls;
  for (auto& x : ls) { x--; }

  vector<int> deg(n, 1);
  for (auto x : ls) {
    deg[x]++;
  }
  dbg(deg);

  set<tuple<int, int>> deg2;
  FOR(v, 0, n) {
    deg2.insert({deg[v], v});
  }
  dbg(deg2);

  vector<tuple<int, int>> res;
  FOR(i, 0, n - 2) {
    int v = ls[i];
    auto [d, u] = *deg2.begin(); deg2.erase(deg2.begin());
    assert(d == 1);
    deg[u]--;

    res.push_back({v, u});
    deg2.erase({deg[v], v});
    deg2.insert({--deg[v], v});
  }
  res.push_back({ls.back(), n - 1});
  dbg(res);

  FOR(i, 0, n - 1) {
    auto [x, y] = res[i];
    cout << (x + 1) << " " << (y + 1) << endl;
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
python misc/run.py cses/additional_problems/task1134/main.cpp --check

%%%% begin
10
7 2 1 3 8 4 6 9
%%%%
%%%% end

%%%% begin
5
2 2 4
%%%%
1 2
2 3
2 4
4 5
%%%% end
*/
