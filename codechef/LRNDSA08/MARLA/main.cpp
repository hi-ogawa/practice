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
}

// Dsu
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
  void merge(int a, int b) { data_[find(a)] = find(b); }
};

// Main
void mainCase() {
  ll n, m; // <= 10^3
  cin >> n >> m;

  vector<vector<ll>> data(n, vector<ll>(m, 0)); // <= 10^9
  cin >> data;
  // DD2(data);

  Dsu dsu(n * m);
  auto _ = [&](int i, int j) { return i * m + j; };
  auto _inv = [&](int k) { return make_tuple(k / m, k % m); };
  RANGE(i, 0, n) {
    RANGE(j, 0, m) {
      if (i + 1 < n && data[i][j] == data[i + 1][j]) {
        dsu.merge(_(i, j), _(i + 1, j));
      }
      if (j + 1 < m && data[i][j] == data[i][j + 1]) {
        dsu.merge(_(i, j), _(i, j + 1));
      }
    }
  }

  map<int, int> component_sizes;
  RANGE(k, 0, n * m) {
    component_sizes[dsu.find(k)]++;
  }
  // DD(component_sizes);

  vector<tuple<int, ll>> states; // (size, NEG-strength)
  for (auto [root, size] : component_sizes) {
    auto [i, j] = _inv(root);
    states.push_back({size, -data[i][j]});
  }
  // DD(states);

  auto [x, y] = *max_element(ALL(states));
  cout << (- y) << " " << x << endl;
}

int main() {
  // [ Single case ]
  mainCase();
  return 0;

  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // RANGE(i, 0, t) mainCase();
  // return 0;
}

/*
python misc/run.py codechef/LRNDSA08/MARLA/main.cpp --check

%%%% begin
5 5
1 1 1 1 1
2 2 2 2 2
3 3 3 3 3
4 4 4 4 4
5 5 5 5 5
%%%%
1 5
%%%% end
*/
