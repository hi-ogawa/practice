// TLE

// NOTE: Use pbds tree

#include <bits/stdc++.h>
using namespace std;

#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (auto I = decltype(Y)(X); I < (Y); ++I)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i,       tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; auto s = ""; apply([&](auto&&... y){ ((o << s << y, s = ", "), ...); }, x); return o << ")"; }
template<class T1, class T2> istream& operator>>(istream& i,       pair<T1, T2>& x) { return i >> tie(x.first, x.second); }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { return o << tie(x.first, x.second); }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
istream& operator>>(istream& i,       T& x) { for (auto& y : x) { i >> y; } return i; }
template<class T, class = decltype(begin(declval<T>())), class = enable_if_t<!is_same<T, string>::value>>
ostream& operator<<(ostream& o, const T& x) { o << "{"; auto s = ""; for (auto& y : x) { o << s << y; s = ", "; } return o << "}"; }
}

#ifdef DEBUG
#define dbg(...) do { cerr << #__VA_ARGS__ ": " << make_tuple(__VA_ARGS__) << endl; } while (0)
#define dbg2(X) do { cerr << #X ":\n"; for (auto& __x : (X)) { cout << __x << endl; } } while (0)
#else
#define dbg(...)
#define dbg2(X)
#endif

// Order statistics tree (cf. https://codeforces.com/blog/entry/11080 by adamant)
#include <ext/pb_ds/assoc_container.hpp>
template<class Key, class Compare = less<Key>>
using ordered_set = __gnu_pbds::tree<
  Key, __gnu_pbds::null_type, Compare,
  __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

// Main
void mainCase() {
  int n, nq; // [1, 10^5]
  cin >> n >> nq;
  vector<int> ls(n); // [0, 10^9]
  cin >> ls;
  vector<array<int, 2>> qs(nq);
  cin >> qs;

  // Mo's algorithm
  int n_blk = sqrt(n);
  auto compare = [&](auto x, auto y) {
    x[0] /= n_blk; y[0] /= n_blk;
    if (x[0] == y[0] && x[0] % 2) { swap(x[1], y[1]); }
    return x < y;
  };
  vector<int> order(nq);
  iota(ALL(order), 0);
  sort(ALL(order), [&](auto x, auto y) { return compare(qs[x], qs[y]); });

  // State
  ll cnt = 0;
  int l = 0, r = 0;
  ordered_set<pair<int, int>> st; // (value, index)

  auto insertL = [&](int i) {
    int x = ls[i];
    cnt += st.order_of_key({x, -1});
    st.insert({x, i});
  };

  auto insertR = [&](int i) {
    int x = ls[i];
    cnt += st.size() - st.order_of_key({x + 1, -1});
    st.insert({x, i});
  };

  auto eraseL = [&](int i) {
    int x = ls[i];
    st.erase({x, i});
    cnt -= st.order_of_key({x, -1});
  };

  auto eraseR = [&](int i) {
    int x = ls[i];
    st.erase({x, i});
    cnt -= st.size() - st.order_of_key({x + 1, -1});
  };

  vector<ll> res(nq);
  FOR(o, 0, nq) {
    int i = order[o];
    auto [ql, qr] = qs[i];
    while (r < qr) { insertR(r++); }
    while (ql < l) { insertL(--l); }
    while (qr < r) { eraseR(--r); }
    while (l < ql) { eraseL(l++); }
    dbg(ql, qr, st);
    res[i] = cnt;
  }

  for (auto x : res) {
    cout << x << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py library_checker/static_range_inversions_query/main.cpp

%%%% begin
4 2
4 1 4 0
1 3
0 4
%%%%
0
4
%%%% end
*/
