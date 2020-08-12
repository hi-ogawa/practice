// AFTER CONTEST, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T, size_t N>  ostream& operator<<(ostream& o, const array<T, N>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}
}


// DSU
struct Dsu {
  vector<int> data_;
  Dsu(int size) {
    data_.resize(size);
    iota(ALL(data_), 0);
  }
  int find(int a) {
    if (data_[a] == a) { return a; }
    return data_[a] = find(data_[a]);
  }
  void merge(int a, int b) {
    data_[find(a)] = find(b);
  }
  map<int, vector<int>> components() {
    map<int, vector<int>> res;
    RANGE(i, 0, (int)data_.size()) {
      res[find(i)].push_back(i);
    }
    return res;
  }
};

// Main
void mainCase() {
  ll nv, ne; // <= 10^5
  cin >> nv >> ne;

  vector<tuple<ll, ll>> es(ne, {0, 0});
  cin >> es;
  // DD(es);

  Dsu dsu(nv);
  vector<vector<ll>> adj(nv, vector<ll>(0, 0)); // later for BFS
  for (auto [x, y] : es) {
    x--; y--; // to zero-based
    dsu.merge(x, y);
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  // DD(dsu.data_);
  // DD(adj);
  cout << adj[0] << endl;

  auto compos = dsu.components();
  // DD(compos);

  // BFS
  vector<int> depths(nv, -1);
  deque<int> queue;
  for (auto& [_x, c] : compos) {
    int root;
    if (c.size() % 2 == 0) { root = *min_element(ALL(c)); }
    if (c.size() % 2 == 1) { root = *max_element(ALL(c)); }
    queue.push_back(root);
    depths[root] = 0;
  }
  while (!queue.empty()) {
    int i = queue.front();  queue.pop_front();
    for (auto j : adj[i]) {
      if (depths[j] != -1) { continue; }
      depths[j] = depths[i] + 1;
      queue.push_back(j);
    }
  }
  // DD(depths);

  array<ll, 2> scores = {{0, 0}};
  for (auto& [_x, c] : compos) {
    for (auto i : c) {
      scores[c.size() % 2] += (depths[i] + 1);
    }
  }
  cout << scores[0] << " " << scores[1] << endl;
}

int main() {
  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA08/INOI2001/main.cpp --check

%%%% begin
1
3 2
1 2
2 3
%%%%
0 6
%%%% end

%%%% begin
1
2 1
1 2
%%%%
3 0
%%%% end

%%%% begin
1
9 7
1 6
5 3
1 2
9 5
3 7
4 5
5 8
%%%%
14 6
%%%% end
*/
