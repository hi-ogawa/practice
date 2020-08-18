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
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// DSU
struct Dsu {
  vector<int> data_;
  vector<int> size_;
  Dsu(int n) {
    data_.resize(n);
    iota(ALL(data_), 0);
    size_.assign(n, 1);
  }
  int find(int x) {
    if (data_[x] == x) { return x; }
    return data_[x] = find(data_[x]);
  }
  void merge(int dst, int src) {
    dst = find(dst);
    src = find(src);
    data_[src] = dst;
    size_[dst] += size_[src];
  }
};

// Main
void mainCase() {
  ll n, m; // <= 10^6
  cin >> n >> m;

  vector<array<ll, 2>> edges(m, {0, 0});
  cin >> edges;

  Dsu dsu(n);
  int num_compos = n;
  int max_size = 1;
  for (auto [x, y] : edges) {
    x--; y--;
    x = dsu.find(x); y = dsu.find(y);
    if (x != y) {
      dsu.merge(x, y);
      num_compos--;
      max_size = max(max_size, dsu.size_[x]);
    }
    cout << num_compos << " " << max_size << endl;
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
python misc/run.py cses/graph_algorithms/task1676/main.cpp --check

%%%% begin
5 3
1 2
1 3
4 5
%%%%
4 2
3 3
2 3
%%%% end
*/
