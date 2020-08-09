// AFTER CONTEST, AC

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

// Main
void mainCase() {
  // Input
  ll X;
  cin >> X;

  ll B;
  cin >> B;
  vector<tuple<ll, ll>> ls1(B, {0, 0});
  // cin >> ls1; // c++17
  RANGE(i, 0, B) cin >> get<0>(ls1[i]) >> get<1>(ls1[i]);

  ll C;
  cin >> C;
  vector<tuple<ll, ll, ll>> ls2(C, {0, 0, 0});
  // cin >> ls2; // c++17
  RANGE(i, 0, C) cin >> get<0>(ls2[i]) >> get<1>(ls2[i]) >> get<2>(ls2[i]);

  // Merge ls1 and ls2
  ll n = B + C;
  vector<tuple<ll, int, ll, ll>> ls(n, {0, 0, 0, 0}); // (x, type, arg1, arg2) (NOTE: x is all distince)
  RANGE(i, 0, B) {
    auto t = ls1[i];
    ls[i] = {get<0>(t), 0, get<1>(t), 0};
  }
  RANGE(i, 0, C) {
    auto t = ls2[i];
    ls[i + B] = {get<0>(t), 1, get<1>(t), get<2>(t)};
  }
  sort(ALL(ls));
  // DD(ls);

  // Solve from tail
  ll res = 1;
  for (int i = n - 1; i >= 0; i--) {
    auto t = ls[i];
    if (get<1>(t) == 0) {
      ll y = get<2>(t);
      res += y;
    }
    if (get<1>(t) == 1) {
      ll q = get<2>(t);
      ll r = get<3>(t);
      if (res >= q + r) {
        res -= r;
        continue;
      }
      if (res >= q) {
        res = q;
        continue;
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
  RANGE(i, 0, t) mainCase();
  return 0;
}

/*
python misc/run.py codechef/LRNDSA04/ASHIGIFT/main.cpp --check

%%%% begin
3
10
2 1 3 8 1
0
10
2 1 3 8 5
0
10
2 2 3 8 5
3 1 2 1 4 3 2 9 1 1
%%%%
5
9
6
%%%% end
*/
