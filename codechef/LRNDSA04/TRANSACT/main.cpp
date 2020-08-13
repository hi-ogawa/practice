// AFTER EDITORIAL, WIP, WA

// TODO: Implement "evaluate"

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
  int n, R; // n <= 10^5, r <= 10^3
  cin >> n >> R;

  vector<ll> ls(n, 0); // <= 10^9
  cin >> ls;
  sort(ALL(ls));

  //
  // DEF.
  //   B(R) = max { minimum after R-restricted distributions }
  //

  // Check if b <= B(r)
  auto evaluate = [&](ll b, ll r) -> bool {
    // TODO:
    //   This is incorrect since
    //     1. Trade doesn't have to be r-"chunk".
    //     2. Only single chunk can be passed between two.

    // The number of "receive-chunks" needed
    ll k0 = 0;
    FOR(i, 0, n) {
      if (ls[i] >= b) { break; }
      k0 += ((b - ls[i]) + r - 1) / r; // ceil(deficiency / r)
    }

    // The number of maximum "give-chunks"
    auto xs = ls;
    ll k1 = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (xs[i] <= b) { break; }
      ll quo = (xs[i] - b) / r;
      ll rem = (xs[i] - b) % r;
      k1 += quo;

      // Push remainder to the next
      if (i - 1 >= 0) {
        xs[i - 1] += rem;
      }
    }

    return k1 >= k0;
  };

  // Binary search max { b | b <= B(r) }
  auto search = [&](ll r) -> ll {
    // [b0, b1)
    ll b0 = 0;
    ll b1 = ls.back() + 1;
    while (b0 + 1 < b1) {
      ll b = (b0 + b1) / 2;
      if (evaluate(b, r)) {
        b0 = b;
      } else {
        b1 = b;
      }
    }
    return b0;
  };

  ll res = search(R);
  cout << res << endl;
}

int main() {
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
python misc/run.py codechef/LRNDSA04/TRANSACT/main.cpp --check

%%%% begin
3 1
1 3 5
%%%%
3
%%%% end
*/
