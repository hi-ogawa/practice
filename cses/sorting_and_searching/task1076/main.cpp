// AC

// NOTE: Domain compression + (value-domain) range-cumsum
// TODO: Find a simpler way

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
    set(qi, get(qi) + qv);
  }
  void set(int qi, ll qv) {
    int j = index(qi);
    data_[j] = qv;
    while (j > 0) {
      j = ((j + 1) / 2) - 1;
      data_[j] = data_[2 * j + 1] + data_[2 * j + 2];
    }
  }
  ll _reduce(int ql, int qr, int l, int r, int j) {
    if (ql <= l && r <= qr) { return data_[j]; }
    if (qr <= l || r <= ql) { return 0; }
    ll mid = (l + r) / 2;
    ll x = _reduce(ql, qr, l, mid, 2 * j + 1);
    ll y = _reduce(ql, qr, mid, r, 2 * j + 2);
    return x + y;
  }
  ll reduce(int ql, int qr) {
    return _reduce(ql, qr, 0, 1 << depth_, 0);
  }
};

// Main
void mainCase() {
  ll n, k; // <= 10^6
  cin >> n >> k;
  vector<ll> ls(n, 0);
  cin >> ls;

  // Compress domain
  vector<ll> ps(n, 0);
  vector<ll> qs;
  {
    map<ll, vector<int>> xs;
    FOR(i, 0, n) { xs[ls[i]].push_back(i); }
    ll j = 0;
    for (auto& [k, ys] : xs) {
      qs.push_back(k);
      for (auto y : ys) { ps[y] = j; }
      j++;
    }
  }
  // DD(ps);
  // DD(qs);

  ll km = (k + 1) / 2;
  ll p_max = *max_element(ALL(ps));
  SegmentTree tree(p_max + 1);

  // min { y | cumsum(y) >= km }
  auto search = [&]() -> int {
    // (y0, y1]
    int y0 = -1;
    int y1 = p_max;
    while (y0 + 1 < y1) {
      int y = (y0 + y1 + 1) / 2;
      ll fy = tree.reduce(0, y + 1);
      if (fy >= km) {
        y1 = y;
      } else {
        y0 = y;
      }
    }
    return y1;
  };

  vector<ll> res;

  // Initial k-segment
  FOR(i, 0, k) {
    tree.incr(ps[i], 1);
  }
  res.push_back(search());

  // More k-segments
  FOR(i, 0, n - k) {
    tree.incr(ps[i], -1);
    tree.incr(ps[i + k], 1);
    res.push_back(search());
  }

  FOR(i, 0, (int)res.size()) {
    if (i) cout << " ";
    cout << qs[res[i]];
  }
  cout << endl;
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
python misc/run.py cses/sorting_and_searching/task1076/main.cpp --check

%%%% begin
8 3
2 4 3 5 8 1 2 1
%%%%
3 4 5 5 2 1
%%%% end
*/
