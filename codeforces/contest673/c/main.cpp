// TLE

// NOTE: TLE but the algorithm doesn't even look correct.

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

// Order statistics tree (cf. https://codeforces.com/blog/entry/11080 by adamant)
#include <ext/pb_ds/assoc_container.hpp>
template<class Key, class Compare = std::less<Key>>
using ordered_set = __gnu_pbds::tree<
  Key, __gnu_pbds::null_type, Compare,
  __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

// Main
void mainCase() {
  int n; // [1, 3 x 10^5]
  cin >> n;
  #define ull uint32_t
  vector<ull> ls(n); // [0, 10^9]
  cin >> ls;

  ordered_set<pair<ull, int>> ms; // (value, id)
  FOR(i, 0, n) {
    ms.insert({ls[i], i});
  }

  // Count "critical pairs" for each bit
  const int k = 30;
  vector<array<ll, 2>> cnts(k);
  FOR(i, 0, n) {
    ull x = ls[i];
    ms.erase({x, i});
    dbgv(i, x, ms);
    FOR(b, 0, k) {
      ull lo = x & ((~0U) << (b + 1)); // TODO: probably you need to take higher bits into account
      ull mi = lo | (1U << b);
      ull hi = mi + (1U << b);
      if (x & (1 << b)) {
        int c = ms.order_of_key({mi, -1}) - ms.order_of_key({lo, -1});
        cnts[b][0] += c;
      } else {
        int c = ms.order_of_key({hi, -1}) - ms.order_of_key({mi, -1});
        cnts[b][1] += c;
      }
    }
  }
  dbg(cnts);

  // Flip bit where it gains
  int res = 0;
  FOR(b, 0, k) {
    if (cnts[b][0] > cnts[b][1]) {
      res |= (1 << b);
    }
  }
  dbg(res);

  // Count inversions
  ordered_set<pair<int, int>> ms2;
  FOR(i, 0, n) {
    ms2.insert({ls[i] ^ res, i});
  }
  ll res2 = 0;
  FOR(i, 0, n) {
    ms2.erase({ls[i] ^ res, i});
    res2 += ms2.order_of_key({ls[i] ^ res, -1});
  }

  cout << res2 << " " << res << "\n";
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/contest673/c/main.cpp --check

%%%% begin
5
1000000000 1000000000 1000000000 0 0
%%%%
0 536870912
%%%% end

%%%% begin
4
0 1 3 2
%%%%
1 0
%%%% end

%%%% begin
9
10 7 9 10 7 5 5 3 5
%%%%
4 14
%%%% end

%%%% begin
3
8 10 3
%%%%
0 8
%%%% end
*/
