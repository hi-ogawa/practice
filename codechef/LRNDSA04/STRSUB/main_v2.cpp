// AFTER EDITORIAL, AC

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
  int n, k, nq; // <= 10^5
  cin >> n >> k >> nq;

  string s;
  cin >> s;

  vector<tuple<int, int>> qs(nq, {0, 0});
  RANGE(i, 0, nq) cin >> get<0>(qs[i]) >> get<1>(qs[i]);

  // Make "right-maximal" infixes
  vector<int> segs(n, 0);
  {
    int j = 0;
    int c0 = 0;
    int c1 = 0;
    RANGE(i, 0, n) {
      if (i - 1 >= 0 && s[i - 1] == '0') { c0--; }
      if (i - 1 >= 0 && s[i - 1] == '1') { c1--; }
      while (j < n) {
        if (c0 == k && s[j] == '0') { break; };
        if (c1 == k && s[j] == '1') { break; };
        if (s[j] == '0') { c0++; }
        if (s[j] == '1') { c1++; }
        j++;
      }
      segs[i] = j;
    }
  }
  // DD(segs);

  // Cumsum interval length
  vector<ll> seglength_cumsum(n + 1, 0);
  RANGE(i, 0, n) {
    seglength_cumsum[i + 1] = seglength_cumsum[i] + (segs[i] - i);
  }
  // DD(seglength_cumsum);

  // Binary search max { x | segs(x) <= r }
  auto search = [&](auto r) {
    // [x0, x1)
    int x0 = 0;
    int x1 = n;
    while (x0 + 1 < x1) {
      int x = (x0 + x1) / 2;
      if (segs[x] <= r) {
        x0 = x;
      } else {
        x1 = x;
      }
    }
    return x0;
  };

  // Answer queries
  for (auto q : qs) {
    int ql, qr;
    tie(ql, qr) = q;
    ql--; // zero-based, half-open [ql, qr)
    // DD(tie(ql, qr));

    if (qr < segs[ql]) {
      // Take all substrings
      ll c = qr - ql;
      ll res = c * (c + 1) / 2;
      cout << res << endl;
      continue;
    }

    int x = search(qr);
    // DD(tie(qr, x, segs[x]));

    // TODO: is this sketchy when x <= ql ??
    // Segments covered by [ql, qr)
    ll res0 = seglength_cumsum[x + 1] - seglength_cumsum[ql];

    // Segments chopped at qr
    ll c = qr - (x + 1);
    ll res1 = c * (c + 1) / 2;

    // DD(tie(res0, res1));
    ll res = res0 + res1;
    cout << res << endl;
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
python misc/run.py codechef/LRNDSA04/STRSUB/main_v2.cpp --check

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
