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

// Fenwick tree for sum
struct FenwickTree {
  int n_;
  vector<int> data_;
  FenwickTree(int n) { n_ = n; data_.resize(n); }
  void incr(int qi, int qv) {
    while (qi < n_) {
      data_[qi] += qv;
      qi = (qi | (qi + 1));
    }
  }
  int reduce(int qi) { // [0, qi)
    qi--;
    ll res = 0;
    while (qi >= 0) {
      res += data_[qi];
      qi = (qi & (qi + 1)) - 1;
    }
    return res;
  }
  int reduce(int l, int r) { // [l, r)
    return reduce(r) - reduce(l);
  }
  int get(int qi) { return reduce(qi, qi + 1); }
  void set(int qi, int qv) { incr(qi, qv - get(qi)); }
};

// Main
void mainCase() {
  int n, m; // [0, 10^5]
  cin >> n >> m;
  vector<array<int, 3>> ls1(n), ls2(m);
  cin >> ls1 >> ls2;

  enum { kV1, kHin, kV2, kHout }; // event processing steps
  int lim = 1000000;
  ls1.push_back({0, 0, lim});
  ls1.push_back({lim, 0, lim});
  ls2.push_back({0, 0, lim});
  ls2.push_back({lim, 0, lim});

  vector<array<int, 4>> events; // (x, type, y1, y2)
  for (auto [y, x1, x2] : ls1) {
    events.push_back({x1, kHin, y, -1});
    events.push_back({x2, kHout, y, -1});
  }
  for (auto [x, y1, y2] : ls2) {
    // Separete into two steps for simplicity
    events.push_back({x, kV1, y1, y2});
    events.push_back({x, kV2, y1, y2});
  }
  sort(ALL(events));
  dbg(events);

  FenwickTree tree(lim + 1);
  set<int> ys;
  ll res = 0;
  for (auto [x, t, y1, y2] : events) {
    dbgv(x, t, res);
    if (t == kV1) {
      if (x == 0) { continue; } // Skip square left boundary

      // Count closed regions
      res += tree.reduce(y1, y2 + 1) - 1;
      continue;
    }
    if (t == kHin) {
      ys.insert(y1);
      continue;
    }
    if (t == kV2) {
      // Create new candidate regions
      if (y1 == 0) {
        auto itupp = ys.upper_bound(y2);
        for (auto it = ys.begin(); it != itupp; it++) {
          tree.set(*it, 1);
        }
        ys.erase(ys.begin(), itupp);
        continue;
      }
      if (y2 == lim) {
        auto itlow = ys.lower_bound(y1);
        for (auto it = itlow; it != ys.end(); it++) {
          tree.set(*it, 1);
        }
        ys.erase(itlow, ys.end());
        continue;
      }
    }
    if (t == kHout) {
      ys.erase(y1);
      tree.set(y1, 0);
      continue;
    }
  }
  cout << res << endl;
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
python misc/run.py codeforces/contest665/e/main.cpp --check

%%%% begin
3 3
2 3 1000000
4 0 4
3 0 1000000
4 0 1
2 0 5
3 1 1000000
%%%%
7
%%%% end
*/
