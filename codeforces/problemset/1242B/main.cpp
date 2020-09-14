// AFTER EDITORIAL, AC

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
  int n, m;
  cin >> n >> m;
  vector<array<int, 2>> edges(m);
  cin >> edges;

  // Normalize "1"-edges
  for (auto& [x, y] : edges) {
    x--; y--;
    if (x > y) { swap(x, y); }
  }
  sort(ALL(edges));

  // "0"-edge adjacency
  auto adjacent = [&](int x, int y) -> bool {
    if (x > y) { swap(x, y); }
    return !binary_search(ALL(edges), array{x, y});
  };

  // Not visited list
  list<int> ls(n);
  iota(ALL(ls), 0);

  // DFS "0"-edges
  function<void(int)> dfs = [&](int v) {
    for (auto it = ls.begin(); it != ls.end(); ) {
      int u = *it;
      if (adjacent(v, u)) { // this fails at most "m" times and "ls.erase" happens "n" times. Thus we hit this loop at most (n + m) times.
        ls.erase(it);
        dfs(u);
        it = ls.begin();
      } else {
        it++;
      }
    }
  };

  int res = 0; // number of components
  while (!ls.empty()) {
    res++;
    int v = ls.front(); ls.pop_front();
    dfs(v);
  }
  dbg(res);

  cout << (res - 1) << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1242B/main.cpp --check

%%%% begin
5 10
1 2
2 3
3 4
4 5
5 1
1 3
2 4
3 5
4 1
5 2
%%%%
4
%%%% end

%%%% begin
6 11
1 3
1 4
1 5
1 6
2 3
2 4
2 5
2 6
3 4
3 5
3 6
%%%%
2
%%%% end
*/
