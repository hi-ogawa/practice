// TLE

// TODO: faster than main.cpp but still TLE

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

// Segment tree for sum
struct SegmentTree {
  int depth_ = 0;
  vector<ll> data_;
  SegmentTree(int n) {
    while ((1 << depth_) < n) { depth_++; }
    data_.resize(1 << (depth_ + 1));
  }
  int index(int qi) {
    return (1 << depth_) - 1 + qi;
  }
  ll get(int qi) {
    return data_[index(qi)];
  }
  void incr(int qi, ll qv) {
    set(qi, get(qi) + qv);
  }
  void set(int qi, ll qv) {
    int j = index(qi);
    data_[j] = qv;
    while (j > 0) {
      j = (j - 1) / 2;
      data_[j] = data_[2 * j + 1] + data_[2 * j + 2];
    }
  }
  ll _reduce(int ql, int qr, int l, int r, int j) {
    if (ql <= l && r <= qr) { return data_[j]; }
    if (qr <= l || r <= ql) { return 0; }
    int mid = (l + r) / 2;
    ll v1 = _reduce(ql, qr, l, mid, 2 * j + 1);
    ll v2 = _reduce(ql, qr, mid, r, 2 * j + 2);
    return v1 + v2;
  }
  ll reduce(int ql, int qr) { return _reduce(ql, qr, 0, 1 << depth_, 0); }
};

// Main
void mainCase() {
  int n, nq; // <= 10^6
  cin >> n >> nq;
  vector<int> ls(n, 0); // <= 10^9
  vector<tuple<char, int, int>> qs(nq, {'0', 0, 0});
  cin >> ls >> qs;

  // Compress domain ~ 10^6
  auto ls2 = ls;
  auto qs2 = qs;
  int v_max = 0;
  {
    map<int, vector<tuple<int, int>>> vals;
    FOR(i, 0, n) {
      vals[ls[i]].push_back({0, i});
    }
    FOR(i, 0, nq) {
      auto [t, a, b] = qs[i];
      if (t == '!') { vals[b].push_back({2, i}); }
      if (t == '?') {
        vals[a].push_back({1, i});
        vals[b].push_back({2, i});
      }
    }
    int i = 0;
    for (auto [_v, ks] : vals) {
      for (auto [t, k] : ks) {
        if (t == 0) { ls2[k] = i; }
        if (t == 1) {
          auto [s, _a, b] = qs2[k];
          qs2[k] = {s, i, b};
        }
        if (t == 2) {
          auto [s, a, _b] = qs2[k];
          qs2[k] = {s, a, i};
        }
      }
      i++;
    }
    v_max = i;
  }
  // DD(ls2);
  // DD(qs2);

  SegmentTree tree(v_max);
  for (auto x : ls2) { tree.incr(x, 1); }

  for (auto [t, a, b] : qs2) {
    if (t == '!') {
      a--;
      tree.incr(ls2[a], -1);
      tree.incr(b, 1);
      ls2[a] = b;
    }
    if (t == '?') {
      ll res = tree.reduce(a, b + 1);
      cout << res << endl;
    }
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
python misc/run.py cses/range_queries/task1144/main_v2.cpp --check

%%%% begin
5 3
3 7 2 2 5
? 2 3
! 3 6
? 2 3
%%%%
3
2
%%%% end
*/
