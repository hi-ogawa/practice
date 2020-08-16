// AC

// TODO: Find simpler DP solution

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

// Segment tree for prefix maximum
struct SegmentTree {
  int depth_;
  vector<ll> data_;

  SegmentTree(int n) {
    depth_ = 0;
    while ((1 << depth_) < n) { depth_++; }
    data_.resize(1 << (depth_ + 1));
  }

  ll get(int qi) {
    int i0 = (1 << depth_) - 1 + qi;
    return data_[i0];
  }

  void set(int qi, ll qv) {
    int i0 = (1 << depth_) - 1 + qi;
    data_[i0] = qv;
    int i = i0;
    while (i > 0) {
      i = ((i + 1) / 2) - 1;
      data_[i] = max(data_[2 * i + 1], data_[2 * i + 2]);
    }
  }

  ll reduce(int ql, int qr) {
    ll result = 0;
    vector<tuple<int, int, int>> stack(depth_ + 1, {0, 0, 0});
    int ptr = 0;
    stack[ptr++] = {0, 0, 1 << depth_};
    while (ptr > 0) {
      auto [i, l, r] = stack[--ptr];
      if (ql <= l && r <= qr) {
        result = max(result, data_[i]);
        continue;
      }
      if (qr <= l || r <= ql) {
        continue;
      }
      stack[ptr++] = {2 * i + 1, l, (l + r) / 2};
      stack[ptr++] = {2 * i + 2, (l + r) / 2, r};
    }
    return result;
  }
};

// Main
void mainCase() {
  ll n; // <= 10^6
  cin >> n;
  vector<ll> ls(n, 0); // <= 10^9
  cin >> ls;

  // Compress domain
  vector<ll> ps(n, 0);
  {
    map<ll, vector<int>> xs;
    FOR(i, 0, n) { xs[ls[i]].push_back(i); }
    ll i = 0;
    for (auto [_k, ys] : xs) {
      for (auto j : ys) { ps[j] = i; }
      i++;
    }
  }
  // DD(ls);
  // DD(ps);

  ll k = *max_element(ALL(ps));
  SegmentTree tree(k + 1);
  FOR(i, 0, n) {
    ll x = ps[i];
    ll y = tree.get(x);
    ll z = tree.reduce(0, x); // prefix maximum
    tree.set(x, max(y, z + 1));
    // DD(tie(x, y, z));
  }
  ll res = tree.data_[0];
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
python misc/run.py cses/dynamic_programming/task1145/main.cpp --check

%%%% begin
8
7 3 5 3 6 2 9 8
%%%%
4
%%%% end
*/
