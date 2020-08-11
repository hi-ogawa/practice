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
  ll n, k; // <= 10^5
  cin >> n >> k;

  vector<ll> ls(n, 0);
  cin >> ls;

  // Maximum prefix/infix/suffix sum (for original ls)
  ll prefix = 0;
  ll infix = 0;
  ll suffix = 0;
  RANGE(i, 0, n) {
    prefix = max((ll)0, prefix + ls[n - 1 - i]);
    suffix = max((ll)0, suffix + ls[i]);
    infix = max(infix, suffix);
  }
  // DD(tie(prefix, infix, suffix));

  // Three possible cases
  //  single copy => infix
  //  2 copy      => suffix + prefix
  //  k copy      => suffix + (k - 2) * sum + prefix
  ll sum = accumulate(ALL(ls), (ll)0);
  ll res = infix;
  if (k >= 2) {
    res = max(res, suffix + prefix + (k - 2) * max((ll)0, sum));
  }

  // Handle all negative case where above produces empty segment
  if (all_of(ALL(ls), [](auto x) { return x < 0; })) {
    res = *max_element(ALL(ls));
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
python misc/run.py codechef/LRNDSA06/KCON/main.cpp --check

%%%% begin
1
1 10
-1
%%%%
-1
%%%% end

%%%% begin
1
1 10
10000000000
%%%%
100000000000
%%%% end

%%%% begin
2
2 3
1 2
3 2
1 -2 1
%%%%
9
2
%%%% end
*/
