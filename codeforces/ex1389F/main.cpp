// AFTER EDITORIAL, WIP, WA

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
  ll n; // <= 10^6
  cin >> n;

  vector<pair<ll,ll>> ls1;
  vector<pair<ll,ll>> ls2;
  FOR(i, 0, n) {
    ll x, y, z; // <= 10^9
    cin >> x >> y >> z;
    z == 1 ? ls1.push_back({x, y}) : ls2.push_back({x, y});
  }
  ll n1 = ls1.size();
  ll n2 = ls2.size();

  // Sort by right-end
  sort(ALL(ls1), [](auto x, auto y) { return tie(x.second, x.first) < tie(y.second, y.first); });
  sort(ALL(ls2), [](auto x, auto y) { return tie(x.second, x.first) < tie(y.second, y.first); });
  DD(tie(ls1, ls2));

  // Binary search max{ i | ls[i].second <= x }  ("-1" for "NOT FOUND")
  auto search = [](const vector<pair<ll, ll>>& ls, ll x) -> int {
    if (x < ls[0].second) { return -1; }

    // [i0, i1)
    int i0 = 0;
    int i1 = ls.size();
    while (i0 + 1 < i1) {
      int i = (i0 + i1) / 2;
      if (ls[i].second <= x ) { i0 = i; } else { i1 = i; }
    }
    return i0;
  };

  // Right-bounded interval subsets dp
  vector<ll> dp1(n1, 0);
  vector<ll> dp2(n2, 0);
  set<tuple<ll, ll>, greater<tuple<ll, ll>>> misc1;
  set<tuple<ll, ll>, greater<tuple<ll, ll>>> misc2;
  int i1 = 0;
  int i2 = 0;
  while (i1 < n1 || i2 < n2) {
    // Progress ls1 or ls2
    int t = -1;
    if (i1 == n1) { t = 2; }
    if (i2 == n2) { t = 1; }
    if (t == -1 && ls1[i1].second <  ls2[i2].second) { t = 1; }
    if (t == -1 && ls1[i1].second >= ls2[i2].second) { t = 2; }
    // Progress ls1
    if (t == 1) {
      auto [l, _r] = ls1[i1];
      ll res = 0;
      // Incorrect
      // if (i1 - 1 >= 0) { res = max(res, dp1[i1 - 1]); }

      // Still incorrect
      DD(misc1);
      auto it = misc1.lower_bound({l, 1e9});
      if (it != misc1.end()) { res = max(res, get<1>(*it)); }

      int j = search(ls2, l);
      if (j != -1) { res = max(res, dp2[j]); }

      res++;
      misc1.insert({l, res});
      dp1[i1] = res;
      DD(tie(i1, res));
      i1++;
    }
    // Progress ls2
    if (t == 2) {
      auto [l, _r] = ls2[i2];
      ll res = 0;
      // Incorrect
      // if (i2 - 1 >= 0) { res = max(res, dp2[i2 - 1]); }

      // Still incorrect
      DD(misc2);
      auto it = misc2.lower_bound({l, 1e9});
      if (it != misc2.end()) { res = max(res, get<1>(*it)); }

      int j = search(ls1, l);
      if (j != -1) { res = max(res, dp1[j]); }

      res++;
      misc2.insert({l, res});
      dp2[i2] = res;
      DD(tie(i2, res));
      i2++;
    }
  }
  DD(tie(dp1, dp2));

  ll res = 0;
  if (n1 > 0) { res = max(res, *max_element(ALL(dp1))); }
  if (n2 > 0) { res = max(res, *max_element(ALL(dp2))); }
  // if (n1 > 0) { res = max(res, dp1.back()); }
  // if (n2 > 0) { res = max(res, dp2.back()); }
  cout << res << endl;
}

int main() {
  // [ Single case ]
  mainCase();
  return 0;

  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) mainCase();
  // return 0;
}

/*
python misc/run.py codeforces/ex1389F/main.cpp --check

%%%% begin
12
1 2 2
6 7 2
2 4 1
3 7 2
5 5 2
1 5 1
2 2 1
4 7 2
3 6 1
4 6 2
2 5 1
4 6 1
%%%%
%%%% end

%%%% begin
3
1 3 1
4 6 2
2 5 1
%%%%
2
%%%% end

%%%% begin
5
5 8 1
1 3 2
3 4 2
6 6 1
2 10 2
%%%%
4
%%%% end

%%%% begin
7
19 20 1
13 15 2
6 11 2
4 10 1
14 17 1
13 13 2
5 9 1
%%%%
5
%%%% end
*/
