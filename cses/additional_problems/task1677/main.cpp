// AC

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

// DSU
struct Dsu {
  vector<int> data_;
  Dsu(int n) { data_.resize(n); iota(ALL(data_), 0); }
  int find(int a) {
    if (data_[a] == a) { return a; }
    return data_[a] = find(data_[a]);
  }
  void merge(int dst, int src) {
    data_[find(src)] = find(dst);
  }
};

// Main
void mainCase() {
  int n, m, nq;
  cin >> n >> m >> nq;
  vector<tuple<int, int>> edges(m, {0, 0});
  cin >> edges;
  vector<tuple<int, int>> qs(nq, {0, 0});
  cin >> qs;
  for (auto& [x, y] : edges) { x--; y--; if (x > y) swap(x, y); }
  for (auto& [x, y] : qs) { x--; y--; if (x > y) swap(x, y); }
  dbg(edges);
  dbg(qs);

  Dsu dsu(n);
  set<tuple<int, int>> qs_set(ALL(qs));
  for (auto [x, y] : edges) {
    if (!qs_set.count({x, y})) { // all broken initially
      dsu.merge(x, y);
    };
  }

  set<int> roots;
  FOR(i, 0, n) { roots.insert(dsu.find(i)); }
  int nc = roots.size(); // number of components

  vector<int> res(nq, 0);
  res[nq - 1] = nc;
  for (int iq = nq - 1; iq >= 1; iq--) { // restore broken edges in reverse order
    auto [x, y] = qs[iq];
    if (dsu.find(x) != dsu.find(y)) {
      dsu.merge(x, y);
      nc--;
    }
    res[iq - 1] = nc;
  }
  dbg(res);

  FOR(i, 0, nq) {
    if (i) cout << " ";
    cout << res[i];
  }
  cout << endl;
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
python misc/run.py cses/additional_problems/task1677/main.cpp --check

%%%% begin
5 5 3
1 2
1 3
2 3
3 4
4 5
3 4
2 3
4 5
%%%%
2 2 3
%%%% end
*/
