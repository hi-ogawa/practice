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

struct Dsu {
  int n;
  vector<int> parents;
  vector<int> sizes;

  Dsu(int _n): n{_n} {
    parents.resize(n);
    sizes.resize(n);
    iota(ALL(parents), 0);
    fill(ALL(sizes), 1);
  }

  int find(int x) {
    if (parents[x] == x) {
      return x;
    }
    return parents[x] = find(parents[x]);
  }

  void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (sizes[x] > sizes[y]) {
      swap(x, y);
    }
    parents[x] = y;
    sizes[y] += sizes[x];
  }
};

// Main
void mainCase() {
  int n, d; // [2, 10^3], d < n  (O(n^2) solution is ok)
  cin >> n >> d;
  vector<tuple<int, int>> constraints(d);
  cin >> constraints;

  Dsu dsu(n);

  // Incrementally compute
  int num_components = n;
  multiset<int> component_sizes;
  for (int i = 0; i < n; i++) {
    component_sizes.insert(1);
  }

  // PROP.
  //   Maximum possible degree = |Largest possible components| - 1

  for (int i = 0; i < d; i++) {
    auto [x, y] = constraints[i];
    x--;
    y--;
    x = dsu.find(x);
    y = dsu.find(y);
    if (x != y) {
      num_components--;
      component_sizes.erase(component_sizes.find(dsu.sizes[x]));
      component_sizes.erase(component_sizes.find(dsu.sizes[y]));
      component_sizes.insert(dsu.sizes[x] + dsu.sizes[y]);
      dsu.merge(x, y);
    }
    dbg(num_components, component_sizes);

    int num_edges = i + 1;
    int num_edges_used = n - num_components;
    int num_edges_left = num_edges - num_edges_used;
    dbg(num_edges, num_edges_used, num_edges_left);

    // Connect "num_edges_left" components from larger ones
    auto it = component_sizes.rbegin();
    int answer = *(it++) -1;
    for (int j = 0; j < num_edges_left; j++, it++) {
      answer += *it;
    }
    cout << answer << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py experiment/cf1609d/main.cpp

%%%% begin
7 6
1 2
3 4
2 4
7 6
6 5
1 7
%%%%
1
1
3
3
3
6
%%%% end

%%%% begin
10 8
1 2
2 3
3 4
1 4
6 7
8 9
8 10
1 4
%%%%
1
2
3
4
5
5
6
8
%%%% end
*/
