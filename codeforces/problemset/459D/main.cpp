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
  void incr(int i, int v) {
    while (i < n_) {
      data_[i] += v;
      i = (i | (i + 1));
    }
  }
  int reduce(int r) { // [0, r)
    int i = r - 1;
    int res = 0;
    while (i >= 0) {
      res += data_[i];
      i = (i & (i + 1)) - 1;
    }
    return res;
  }
};

// Main
void mainCase() {
  int n;
  cin >> n;
  vector<int> ls(n);
  cin >> ls;

  //
  // PROP.
  //   g(i) = #{j <= i | ls[j] = ls[i]}
  //   h(i) = #{j >= i | ls[j] = ls[i]}
  //   res = #{ (i, j) | g(i) > h(j) }
  //

  map<int, int> cnts;
  vector<int> gs(n);
  vector<int> hs(n);
  FOR(i, 0, n) {
    cnts[ls[i]]++;
    gs[i] = cnts[ls[i]];
  }
  cnts.clear();
  for (int i = n - 1; i >= 0; i--) {
    cnts[ls[i]]++;
    hs[i] = cnts[ls[i]];
  }

  int h_max = *max_element(ALL(hs));
  FenwickTree h_cnts(h_max + 1);
  for (auto h : hs) { h_cnts.incr(h, 1); }

  ll res = 0;
  FOR(i, 0, n) {
    h_cnts.incr(hs[i], -1);
    res += h_cnts.reduce(gs[i]);
  }
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/459D/main.cpp --check

%%%% begin
7
1 2 1 1 2 2 1
%%%%
8
%%%% end

%%%% begin
3
1 1 1
%%%%
1
%%%% end

%%%% begin
5
1 2 3 4 5
%%%%
0
%%%% end
*/
