// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T>            istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#define DD(X) std::cout << #X ": " << (X) << std::endl << std::flush
#define DD2(X) std::cout << #X ":" << std::endl; for (auto x : (X)) { std::cout << x << std::endl << std::flush; }
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T>            ostream& operator<<(ostream& o, const vector<T>& x)    { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const set<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const map<T1, T2>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
template<class T, size_t N>  ostream& operator<<(ostream& o, const array<T, N>& x)  { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n, k;
  cin >> n >> k;
  // n <= 10^6
  // k <= 10^9

  ll a1, a2, b1, b2;
  cin >> a1 >> a2 >> b1 >> b2;

  // WLOG, a1 <= b1
  if (a1 > b1) {
    swap(a1, b1);
    swap(a2, b2);
  }
  // DD(tie(a1, a2, b1, b2));

  // Case 1. initially intersected
  if (b1 <= a2) {
    // Case 1.1.
    // +=======+
    //     +======+
    //
    // Case 1.2.
    // +=============+
    //     +======+
    //
    ll lo = min(a2, b2) - b1; // overwrap
    ll lu = max(a2, b2) - a1; // union
    // DD(tie(lo, lu));

    auto solve = [&]() -> ll {
      // Initial gain
      if (k <= n * lo) { return 0; }
      k -= n * lo;

      // "Gain per step" = 1
      ll g = lu - lo;
      if (k <= n * g) { return k; }
      k -= n * g;
      ll res = n * g;

      // "Gain per step" = 1/2
      return res + 2 * k;
    };
    cout << solve() << endl;
    return;
  }

  //
  // Case 2. initially no intersection
  //
  // PROP. (Average gain per step)
  //   Given segments like
  //     +====+-----+======+
  //       l1    l     l2
  //
  //   Then, to making them overwrap it goes like
  //     l steps => 0
  //     l + l1 + l2 steps => 1
  //
  //   Thus, average "gain per step" is
  //      (l + l1 + l2) / (2l + l1 + l2) >= 1/2
  //
  // N.B.
  //   Thus, "making two pair overwrap" is optimal strategy at "initial stage".
  //
  ll l = b1 - a2;
  ll l1 = a2 - a1;
  ll l2 = b2 - b1;
  // DD(tie(l1, l, l2));

  auto solve = [&]() -> ll {
    // "Gain per step" >= 1/2
    ll g = l + l1 + l2;
    // DD(tie(k, n, g));
    if (k <= n * g) {
      ll q = k / g;
      ll r = k % g;
      // DD(tie(q, r));

      // Complete overwrap q times
      ll res = q * (2 * l + l1 + l2);
      if (r == 0) {
        return res;
      }

      // Better to take "Gain per step" = 1/2
      if (0 < q && r <= l) {
        return res + 2 * r;
      }

      // Or, take partial overwrap
      return res + r + l;
    }
    k -= n * g;
    ll res = n * (2 * l + l1 + l2);
    // DD(tie(k, res));

    // "Gain per step" = 1/2
    return res + 2 * k;
  };
  cout << solve() << endl;
}

int main() {
  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codeforces/edu92/d/main.cpp --check

%%%% begin
1
10 5647
984 986
427 782
%%%%
7724
%%%% end

%%%% begin
3
3 5
1 2
3 4
2 1000000000
1 1
999999999 999999999
10 3
5 10
7 8
%%%%
7
2000000000
0
%%%% end
*/
