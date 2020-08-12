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
  ll n, k, nq; // n, nq <= 10^5,  k <= 10^9
  cin >> n >> k >> nq;

  vector<ll> ls(n, 0); // <= 10^9
  cin >> ls;

  vector<tuple<ll, ll>> qs(nq, {0, 0});
  // cin >> qs; // c++17
  RANGE(i, 0, nq) { cin >> get<0>(qs[i]) >> get<1>(qs[i]); }

  // Sort ls
  vector<ll> ls_arg(n, 0);
  iota(ALL(ls_arg), 0);
  sort(ALL(ls_arg), [&](auto x, auto y) { return ls[x] < ls[y]; });

  vector<ll> ls_arg_inv(n, 0);
  RANGE(i, 0, n) { ls_arg_inv[ls_arg[i]] = i; }
  // DD(ls);
  // DD(ls_arg);
  // DD(ls_arg_inv);

  // Connected components
  vector<ll> compo(n, 0);
  RANGE(i, 1, n) {
    compo[i] = compo[i - 1];
    if (ls[ls_arg[i]] - ls[ls_arg[i - 1]] > k) {
      compo[i]++;
    }
  }
  // DD(compo);

  // Answer queries
  RANGE(iq, 0, nq) {
    // auto [i0, i1] = qs[iq]; // c++17
    int i0, i1;
    tie(i0, i1) = qs[iq];
    i0--; i1--;  // zero-based index
    int l = ls_arg_inv[i0];
    int r = ls_arg_inv[i1];
    if (l > r) { swap(l, r); }
    cout << (compo[l] == compo[r] ? "Yes" : "No") << endl;
  }
}

int main() {
  // [ Single case ]
  mainCase();
  return 0;

  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // RANGE(i, 0, t) mainCase();
  // return 0;
}

/*
python misc/run.py codechef/LRNDSA07/FROGV/main_v2.cpp --check

%%%% begin
3 1 0
4 0 2
%%%%
%%%% end

%%%% begin
6 8 1
0 1 10 11 21 22
2 6
%%%%
No
%%%% end

%%%% begin
2 1 1
0 0 0 0
3 3
%%%%
Yes
%%%% end

%%%% begin
3 1 1
1 1 1
1 3
%%%%
Yes
%%%% end

%%%% begin
5 3 3
0 3 8 5 12
1 2
1 3
2 5
%%%%
Yes
Yes
No
%%%% end
*/
