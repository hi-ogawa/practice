// AC

// NOTE: Same approach as task1145/main.cpp

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

// Modulo op
constexpr ll modulo = 1000'000'000 + 7;
ll madd(ll x, ll y) { return (x + y) % modulo; }

// Segment tree for prefix sum
struct SegmentTree {
  int depth_ = 0;
  vector<ll> data_;
  SegmentTree(int n) {
    while ((1 << depth_) < n) { depth_++; }
    data_.resize(1 << (depth_ + 1));
  }
  int index(int i) {
    return (1 << depth_) - 1 + i;
  }
  ll get(int i) {
    return data_[index(i)];
  }
  void incr(int qi, ll qv) {
    // set(qi, get(qi) + qv);
    set(qi, madd(get(qi), qv)); // Modulo op
  }
  void set(int qi, ll qv) {
    int j = index(qi);
    data_[j] = qv;
    while (j > 0) {
      j = ((j + 1) / 2) - 1;
      // data_[j] = data_[2 * j + 1] + data_[2 * j + 2];
      data_[j] = madd(data_[2 * j + 1], data_[2 * j + 2]); // Modulo op
    }
  }
  ll _reduce(int ql, int qr, int l, int r, int j) {
    if (ql <= l && r <= qr) { return data_[j]; }
    if (qr <= l || r <= ql) { return 0; }
    ll mid = (l + r) / 2;
    ll x = _reduce(ql, qr, l, mid, 2 * j + 1);
    ll y = _reduce(ql, qr, mid, r, 2 * j + 2);
    // return x + y;
    return madd(x, y); // Modulo op
  }
  ll reduce(int ql, int qr) {
    return _reduce(ql, qr, 0, 1 << depth_, 0);
  }
};

// Main
void mainCase() {
  int n; // <= 10^6
  cin >> n;
  vector<int> ls(n, 0); // <= 10^9
  cin >> ls;

  // Compress domain to [0, n)
  vector<int> ps(n, 0);
  {
    map<int, vector<int>> xs;
    FOR(i, 0, n) { xs[ls[i]].push_back(i); }
    int i = 0;
    for (auto [_v, ks] : xs) {
      for (auto k : ks) { ps[k] = i; }
      i++;
    }
  }
  // DD(ps);

  // Prefix DP
  int k = *max_element(ALL(ps));
  SegmentTree tree(k + 1);
  FOR(i, 0, n) {
    int x = ps[i];
    ll y = tree.reduce(0, x);
    // DD(tie(i, x, y));
    tree.incr(x, madd(y, 1));
  }
  ll res = tree.reduce(0, k + 1);
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
python misc/run.py cses/additional_problems/task1748/main.cpp --check

%%%% begin
3
2 1 3
%%%%
5
%%%% end
*/
