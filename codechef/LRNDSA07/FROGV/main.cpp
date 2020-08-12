// AFTER CONTEST, AC

// NOTE
// Since "k" doesn't change between queries,
// we can simply use precompute connectivity without computing max for each query.
// See main_v2.cpp

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
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Segment tree (cf. codeforces/edu/ex273169A/main.cpp)
struct SegmentTree {
  int n_;
  function<ll(ll, ll)> reducer_;
  ll init_value_;
  int depth_ = 0;
  vector<ll> data_ = {};

  SegmentTree(int x, const function<ll(ll, ll)>& y, ll z = 0)
    : n_{x}, reducer_{y}, init_value_{z} {
    while ((1 << depth_) < n_) { depth_++; }
    data_.assign(1 << (depth_ + 1), init_value_);
  }

  void set(int qi, ll qv) {
    int i0 = (1 << depth_) - 1 + qi;
    data_[i0] = qv;
    int i = i0;
    while (i > 0) {
      i = ((i + 1) / 2) - 1;
      data_[i] = reducer_(data_[2 * i + 1], data_[2 * i + 2]);
    }
  }

  ll reduce(int ql, int qr) {
    ll result = init_value_;
    vector<tuple<int, int, int>> stack(depth_ + 1, {0, 0, 0});
    int ptr = 0;
    stack[ptr++] = {0, 0, 1 << depth_};
    while (ptr > 0) {
      // auto [i, l, r] = stack[--ptr]; // c++17
      int i, l, r;
      tie(i, l, r) = stack[--ptr];
      if (ql <= l && r <= qr) {
        result = reducer_(result, data_[i]);
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
  ll n, k, nq; // n, nq <= 10^5,  k <= 10^9
  cin >> n >> k >> nq;

  vector<ll> ls(n, 0); // <= 10^9
  cin >> ls;

  vector<tuple<ll, ll>> qs(nq, {0, 0});
  // cin >> qs; // c++17
  RANGE(i, 0, nq) { cin >> get<0>(qs[i]) >> get<1>(qs[i]); }

  // Sort ls
  vector<ll> ls_arg(n, 0);
  iota(ALL(ls_arg), 0);
  sort(ALL(ls_arg), [&](auto x, auto y) { return ls[x] < ls[y]; });

  vector<ll> ls_arg_inv(n, 0);
  RANGE(i, 0, n) { ls_arg_inv[ls_arg[i]] = i; }

  // Initialize max segment tree for neighbor distance
  SegmentTree st(n - 1, [](ll x, ll y) { return max(x, y); });
  RANGE(i, 0, n - 1) {
    st.set(i, ls[ls_arg[i + 1]] - ls[ls_arg[i]]);
  }

  // Answer queries
  RANGE(iq, 0, nq) {
    // auto [i0, i1] = qs[iq]; // c++17
    int i0, i1;
    tie(i0, i1) = qs[iq];
    i0--; i1--;  // zero-based index
    int l = ls_arg_inv[i0];
    int r = ls_arg_inv[i1];
    if (l > r) { swap(l, r); }

    // Maximum distance between ls[i0], ls[i1]
    ll maxi = st.reduce(l, r);
    // DD(tie(i0, i1, l, r, maxi));

    cout << (maxi <= k ? "Yes" : "No") << endl;
  }
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
python misc/run.py codechef/LRNDSA07/FROGV/main.cpp --check

%%%% begin
6 8 1
0 1 10 11 21 22
2 6
%%%%
No
%%%% end

%%%% begin
4 1 1
0 0 0 0
3 4
%%%%
Yes
%%%% end

%%%% begin
3 1 1
1 1 1
1 3
%%%%
Yes
%%%% end

%%%% begin
5 3 3
0 3 8 5 12
1 2
1 3
2 5
%%%%
Yes
Yes
No
%%%% end
*/
