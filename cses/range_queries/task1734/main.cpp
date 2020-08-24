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

// Prefix sum
struct FenwickTree {
  int n_;
  vector<ll> data_;
  FenwickTree(int n) { n_ = n; data_.resize(n); }
  void incr(int qi, ll qv) {
    while (qi < n_) {
      data_[qi] += qv;
      qi = (qi | (qi + 1));
    }
  }
  ll reduce(int qi) {
    ll res = 0;
    while (qi >= 0) {
      res += data_[qi];
      qi = (qi & (qi + 1)) - 1;
    }
    return res;
  }
};

// Main
void mainCase() {
  int n, nq;
  cin >> n >> nq;
  vector<int> ls(n, 0);
  cin >> ls;
  vector<tuple<int, int>> qs(nq, {0, 0});
  cin >> qs;
  for (auto& [x, y] : qs) { x--; y--; }

  // Sort by right-end
  vector<int> qs_order(nq, 0);
  iota(ALL(qs_order), 0);
  sort(ALL(qs_order), [&](auto x, auto y) { return get<1>(qs[x]) < get<1>(qs[y]); });

  // Track each value's right-most index up to "b"
  int i = 0;
  map<int, int> indices;
  FenwickTree tree(n); // holds 0/1-flag for "unique" index

  vector<int> res(nq, 0);
  FOR(iq, 0, nq) {
    auto [a, b] = qs[qs_order[iq]];
    while (i <= b) {
      int x = ls[i];
      if (indices.count(x)) {
        tree.incr(indices[x], -1);
      }
      indices[x] = i;
      tree.incr(i, 1);
      i++;
    }
    int tmp = tree.reduce(b) - tree.reduce(a - 1);
    res[qs_order[iq]] = tmp;
  }

  for (auto x : res) { cout << x << endl; }
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
python misc/run.py cses/range_queries/task1734/main.cpp --check

%%%% begin
5 3
3 2 3 1 2
1 3
2 4
1 5
%%%%
2
3
3
%%%% end
*/
