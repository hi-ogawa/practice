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
  ll n; // <= 10^5
  cin >> n;

  vector<ll> ls(n, 0); // abs(a) <= 10^9
  cin >> ls;

  // Modified Kadane to track minimum within chosen segment
  ll infix, infix_min;
  ll suffix, suffix_min;
  infix = infix_min = suffix = suffix_min = ls[0];
  RANGE(i, 1, n) {
    // Track minimum for "suffix = max(suffix + ls[i], ls[i])"
    if (suffix < 0) {
      suffix = suffix_min = ls[i];
    } else if (suffix == 0) {
      suffix = ls[i];
      suffix_min = min(suffix_min, ls[i]);
    } else if (suffix > 0) {
      suffix = suffix + ls[i];
      suffix_min = min(suffix_min, ls[i]);
    }

    // Track minimum for "infix = max(infix, suffix)"
    if (infix == suffix) {
      infix_min = min(infix_min, suffix_min);
    }
    if (infix < suffix) {
      infix = suffix;
      infix_min = suffix_min;
    }
  }
  // DD(tie(infix, infix_min));

  ll res = infix;
  if (infix_min < 0) { res -= infix_min; }

  // Correct when infix's length = 1
  ll m = *max_element(ALL(ls));
  if (m < 0) { res = infix; }
  if (m >= 0 && infix == infix_min) { res = infix; }

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
python misc/run.py codechef/LRNDSA07/ATCH/main.cpp --check

%%%% begin
1
3
1 2 3
%%%%
6
%%%% end

%%%% begin
2
5
1 2 3 -2 3
2
-1 -2
%%%%
9
-1
%%%% end
*/
