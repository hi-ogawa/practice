// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
template<class T, size_t N>  istream& operator>>(istream& i, array<T, N>& x)  { for (auto& y : x) { i >> y; } return i; }
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

// DSU
struct Dsu {
  vector<int> data_;
  Dsu(int n) {
    data_.resize(n);
    iota(ALL(data_), 0);
  }
  int find(int a) {
    if (data_[a] == a) { return a; }
    return data_[a] = find(data_[a]);
  }
  void merge(int a, int b) {
    data_[find(b)] = find(a);
  }
};

// Main
void mainCase() {
  ll n, m;
  cin >> n >> m;

  vector<ll> ls(n, 0);
  cin >> ls;
  for (auto& x : ls) { x--; }

  vector<tuple<ll, ll>> qs(m - 1, {0, 0});
  cin >> qs;
  for (auto& [x, y] : qs) { x--; y--; }

  // Groups
  map<int, set<int>> groups;
  FOR(i, 0, n) {
    groups[ls[i]].insert(i);
  }

  // Initialize dsu
  Dsu dsu(n);
  Dsu dsu2(m);
  FOR(i, 0, n) {
    dsu.merge(i, *groups[ls[i]].begin());
  }

  // Count initial distinct neighbor
  ll res = n - 1;
  FOR(i, 0, n - 1) {
    if (ls[i] == ls[i + 1]) {
      res--;
    }
  }

  // Befor query
  // DD(groups);
  // DD(dsu.data_);
  // DD(dsu2.data_);
  cout << res << endl;

  // Answer queries
  for (auto [a, b] : qs) {
    int ra = dsu2.find(a);
    int rb = dsu2.find(b);
    if (groups[ra].size() < groups[rb].size()) { swap(ra, rb); }

    auto& ga = groups[ra];
    auto& gb = groups[rb];
    // DD(tie(ra, rb));
    // DD(tie(ga, gb));
    int ia = dsu.find(*ga.begin());
    for (auto i : gb) {
      if (i - 1 >= 0 && dsu.find(i - 1) == ia) { res--; }
      if (i + 1 < n  && dsu.find(i + 1) == ia) { res--; }
    }
    for (auto i : gb) {
      ga.insert(i);
      dsu.merge(ia, i); // ia = i's parent
    }
    dsu2.merge(ra, rb); // ra = rb's parent

    // DD(dsu.data_);
    // DD(dsu2.data_);
    cout << res << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

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
python misc/run.py codeforces/edu91/e/main_v3.cpp --check

%%%% begin
7 4
1 2 3 3 1 4 3
3 1
2 3
2 4
%%%%
5
4
2
0
%%%% end
*/
