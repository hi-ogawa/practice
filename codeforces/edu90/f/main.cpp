// VC, AC

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
template<class T, size_t N>  istream& operator>>(istream& i, array<T, N>& x)  { for (auto& y : x) { i >> y; } return i; }
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
  int n; // <= 10^6
  cin >> n;

  vector<ll> xs(n, 0); // <= 10^9
  vector<ll> ys(n, 0); // <= 10^9
  cin >> xs >> ys;

  // Distribute y[0] = (z) + (y[0] - z) >= x[0] + x[-1]
  // f(z) = 0, 1, -1
  auto evaluate = [&](ll z) -> ll {
    ll tmp = ys[0] - z;
    FOR(i, 1, n) {
      tmp = ys[i] - max((ll)0, xs[i] - tmp);
      if (tmp < 0) { return -1; }
    }
    return (tmp + z >= xs[0]) ? 0 : 1;
  };

  auto search = [&]() -> bool {
    // [z0, z1)
    ll z0 = 0;
    ll z1 = ys[0] + 1;
    while (true) {
      ll z = (z0 + z1) / 2;
      // DD(z);

      ll fz = evaluate(z);
      if (fz == 0) { return true; }
      if (z0 + 1 == z1) { break; }

      if (fz < 0) {
        z1 = z;
      } else {
        z0 = z;
      }
    }
    return false;
  };
  // DD(search());

  bool res = search();
  cout << (res ? "YES" : "NO") << endl;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  // [ Single case ]
  // mainCase();
  // return 0;

  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/edu90/f/main.cpp --check

%%%% begin
1
4
2 3 4 5
3 7 2 2
%%%%
NO
%%%% end

%%%% begin
5
3
2 3 4
3 3 3
3
3 3 3
2 3 4
4
2 3 4 5
3 7 2 2
4
4 5 2 3
2 3 2 7
2
1 1
10 10
%%%%
YES
YES
NO
YES
YES
%%%% end
*/
