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
  ll n, k, z;
  cin >> n >> k >> z;
  // n <= 10^5
  // z <= 5

  vector<ll> ls(n, 0);
  cin >> ls;

  // cumsum
  vector<ll> ps(n + 1, 0);
  FOR(i, 0, n) { ps[i + 1] = ps[i] + ls[i]; }

  // ls[i] + ls[i+1] (bonus for single turn at "i")
  vector<ll> qs(n - 1, 0);
  FOR(i, 0, n - 1) { qs[i] = ls[i] + ls[i + 1]; }
  // DD(ls);
  // DD(ps);
  // DD(qs);

  // Brute-force (enumerate the right-most index to reach)
  // 0 .. k-2, k-1, k
  // 0 .. k-2, k-1,
  // ...
  // 0 .. k-2z+1
  // 0 .. k-2z
  ll res = ps[k + 1];
  FOR(i, 1, z + 1) {
    // All full turns
    {
      ll w = k - 2 * i;
      if (0 <= w) {
        ll x = ps[w + 1]; // sum single path
        ll y = *max_element(qs.begin(), qs.begin() + w); // turn at maximum
        res = max(res, x + i * y);
      }
    }
    // End by half turn
    {
      ll w = k - 2 * i + 1;
      if (0 < w) {
        ll x = ps[w + 1]; // sum single path
        ll y = *max_element(qs.begin(), qs.begin() + w); // turn at maximum
        ll yy = ls[w - 1]; // end by half turn
        res = max(res, x + (i - 1) * y + yy);
      }
    }
  }
  cout << res << endl;
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
python misc/run.py codeforces/edu92/b/main.cpp --check

%%%% begin
1
5 4 4
10 20 30 40 50
%%%%
150
%%%% end

%%%% begin
4
5 4 0
1 5 4 3 2
5 4 1
1 5 4 3 2
5 4 4
10 20 30 40 50
10 7 3
4 6 8 2 9 9 7 4 10 9
%%%%
15
19
150
56
%%%% end
*/
