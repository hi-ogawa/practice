// AFTER CONTEST, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define RANGE(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
namespace std {
template<class ...Ts> istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T>     istream& operator>>(istream& i, vector<T>& x)    { for (auto& y : x) { i >> y; } return i; }
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

//
// PROP.
//   Noting
//     d_i+2 = 2^i.a ∈ Z_10
//     2^1 = 2 ∈ Z_10
//     2^2 = 4
//     2^3 = 8
//     2^4 = 6
//     2^5 = 2
//     ...
//   we have,
//     d3 = 2a ∈ Z_10
//     d4 = 4a
//     d5 = 8a
//     d6 = 6a
//     d7 = 2a
//     ...
//

bool solve(ll k, ll d0, ll d1) {
  if (k == 2) {
    return (d0 + d1) % 3 == 0;
  }

  ll a = (d0 + d1) % 10;
  ll a2 = (2 * a) % 10;
  ll a4 = (4 * a) % 10;
  ll a8 = (8 * a) % 10;
  ll a6 = (6 * a) % 10;
  ll ls[4] = {a2, a4, a8, a6};
  // DD(tie(d0, d1, a, a2, a4, a8, a6));

  ll n = k - 3;
  ll x = 0;
  x += d0 + d1 + a;
  x += (n / 4) * (a2 + a4 + a8 + a6);
  RANGE(i, 0, n % 4) {
    x += ls[i];
  }
  return x % 3 == 0;
}

void mainCase() {
  ll k, d0, d1;
  cin >> k >> d0 >> d1;
  bool res = solve(k, d0, d1);
  cout << (res ? "YES" : "NO") << endl;
}

int main() {
  int t;
  cin >> t;
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA01/MULTHREE/main.cpp --check

%%%% begin
3
5 3 4
13 8 1
760399384224 5 1
%%%%
NO
YES
YES
%%%% end
*/
