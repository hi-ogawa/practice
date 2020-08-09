// AFTER EDITORIAL, WIP

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
  int n, k, nq;
  cin >> n >> k >> nq;

  string s;
  cin >> s;

  vector<tuple<int, int>> qs(nq, {0, 0});
  RANGE(i, 0, nq) cin >> get<0>(qs[i]) >> get<1>(qs[i]);

  // [ left/right-maximal segments, which doesn't seem to be useful ]
  // // Enumerate "maximal" segments
  // vector<tuple<int, int>> segs(0, {0, 0});
  // {
  //   int i = 0;
  //   int j = 0;
  //   int c0 = 0;
  //   int c1 = 0;
  //   // Maximize [0, j)
  //   while (j < n) {
  //     if (c0 == k && s[j] == '0') { break; };
  //     if (c1 == k && s[j] == '1') { break; };
  //     if (s[j] == '0') { c0++; }
  //     if (s[j] == '1') { c1++; }
  //     j++;
  //   }
  //   segs.push_back({i, j});

  //   while (j < n) {
  //     // Progress [i, j) -> [i+1, j)
  //     if (s[i] == '0') { c0--; }
  //     if (s[i] == '1') { c1--; }
  //     i++;

  //     // Maximize [i, j)
  //     bool progress = 0;
  //     while (j < n) {
  //       if (c0 == k && s[j] == '0') { break; };
  //       if (c1 == k && s[j] == '1') { break; };
  //       if (s[j] == '0') { c0++; }
  //       if (s[j] == '1') { c1++; }
  //       j++;
  //       progress = 1;
  //     }
  //     if (progress) {
  //       segs.push_back({i, j});
  //     }
  //   }
  // }
  // DD(segs);


  for (auto q : qs) {
    int ql, qr;
    tie(ql, qr) = q;
    // DD(tie(ql, qr));
  }
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
python misc/run.py codechef/LRNDSA04/STRSUB/main.cpp --check

%%%% begin
1
8 2 3
01110000
1 4
2 4
5 8
%%%%
8
5
7
%%%% end
*/
