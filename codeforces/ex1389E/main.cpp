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
  ll m, d, w; // <= 10^9
  cin >> m >> d >> w;

  //
  // PROP.
  //   (x - 1).d + y = (y - 1).d + x ∈ Zw
  //   <=> (y - x) (d - 1) = 0 ∈ Zw
  //   <=> w | (y - x) (d - 1)
  //   <=> (w / gcd(w, d - 1)) | (y - x)
  //

  ll k = w / gcd(w, d - 1);
  ll l = min(m, d);
  // DD(tie(m, d, w, k, l));

  // [ Show pairs ]
  // FOR(x, 1, l + 1) {
  //   ll y = x + k;
  //   while (y <= l) {
  //     DD(tie(x, y));
  //     y += k;
  //   }
  // }

  // ∑_{1 ≤ x ≤ l} ⌊(l - x) / k⌋ = ⌊0/k⌋ + ⌊1/k⌋ + .. + ⌊(l-1)/k⌋
  // [ by brute force ]
  // ll res = 0;
  // FOR(x, 1, l + 1) {
  //   res += ((l - x) / k);
  // }
  // DD(res);
  // [ by triangle number etc... ]
  ll p = l - 1;
  ll q = p / k;
  ll res = 0;
  res += k * (((q - 1) * q) / 2);
  res += (1 + (p % k)) * q;
  // DD(res);

  cout << res << endl;
}

int main() {
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
python misc/run.py codeforces/ex1389E/main.cpp --check

%%%% begin
1
6 7 4
%%%%
6
%%%% end

%%%% begin
5
6 7 4
10 7 12
12 30 7
1 1 1
3247834 10298779 625324
%%%%
6
9
5
0
116461800
%%%% end
*/
