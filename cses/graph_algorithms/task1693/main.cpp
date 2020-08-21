// WIP

// Cf. task1691

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
  int n, m; // <= 10^6
  cin >> n >> m;

  vector<tuple<int, int>> edges(m, {0, 0});
  cin >> edges;

  int v_beg = 0, v_end = n - 1;
  edges.push_back({v_end + 1, v_beg + 1});

  // Adjacency and degrees
  vector<vector<int>> adj(n);
  vector<array<int, 2>> degs(n, {0, 0}); // in-out
  for (auto [x, y] : edges) {
    x--; y--;
    adj[x].push_back(y);
    degs[x][1]++; degs[y][0]++;
  }

  // Check solvability
  bool ok1 = 1;
  FOR(i, 0, n) { ok1 = ok1 && (degs[i][0] == degs[i][1]); }
  if (!ok1) { cout << "IMPOSSIBLE" << endl; return; }

  // Euler tour
  vector<int> tour;
  {
    vector<int> st;
    st.push_back(v_beg);
    while (!st.empty()) {
      int v = st.back();
      if (adj[v].empty()) {
        tour.push_back(v);
        st.pop_back();
        continue;
      }
      int u = adj[v].back(); adj[v].pop_back();
      st.push_back(u);
    }
    reverse(ALL(tour));
  }
  // DD(tour);

  // Check no edges left (i.e. check connected component)
  bool ok2 = 1;
  FOR(i, 0, n) { ok2 = ok2 && adj[i].empty(); }
  if (!ok2) { cout << "IMPOSSIBLE" << endl; return; }

  // Split tour to path
  vector<int> res;
  {
    int k = -1;
    FOR(i, 0, m + 1) {
      if (tour[i] == v_end && tour[i + 1] == v_beg) {
        k = i + 1;
        break;
      }
    }
    assert(k >= 0);
    FOR(i, k, m + 1) { res.push_back(tour[i]); }
    FOR(i, 0, k)     { res.push_back(tour[i]); }
  }
  // DD(res);

  FOR(i, 0, m + 1) {
    if (i) cout << " ";
    cout << (res[i] + 1);
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
python misc/run.py cses/graph_algorithms/task1693/main.cpp --check

%%%% begin
5 6
1 2
1 3
2 4
2 5
3 1
4 2
%%%%
1 3 1 2 4 2 5
%%%% end
*/
