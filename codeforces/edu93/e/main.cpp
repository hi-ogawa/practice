// AFTER EDITORIAL, AC

#include <bits/stdc++.h>
using namespace std;

// Utility
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, X, Y) for (int I = (X); I < (Y); I++)
using ll = int64_t;
using ull = uint64_t;
template<typename T> struct is_container {
template<typename C> static char test(typename C::const_iterator*); template<typename> static int test(...);
static bool const value = sizeof(test<T>(nullptr)) == sizeof(char) && !std::is_same<std::string, T>::value;
};
namespace std {
template<class ...Ts>        istream& operator>>(istream& i, tuple<Ts...>& x) { apply([&](auto&&... ys){ ((i >> ys), ...); }, x); return i; }
template<class T1, class T2> istream& operator>>(istream& i, pair<T1, T2>& x) { i >> x.first >> x.second; return i; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
istream& operator>>(istream& i, T& x) { for (auto& y : x) { i >> y; } return i; }
}

// Debugging
#ifndef DEBUG
#define DEBUG 0
#endif
#define dbg(X) do { if (DEBUG) { cout << #X ": " << (X) << endl << flush; } } while (0)
#define dbg2(X) do { if (DEBUG) { cout << #X ":" << endl; for (auto& __x : (X)) { cout << __x << endl << flush; } } } while (0)
#define dbgv(...) do { if (DEBUG) { cout << "(" #__VA_ARGS__ "): " << make_tuple(__VA_ARGS__) << endl << flush; } } while (0)
namespace std {
template<class ...Ts>        ostream& operator<<(ostream& o, const tuple<Ts...>& x) { o << "("; apply([&](auto&& y, auto&&... ys){ o << y; ((o << ", " << ys), ...); }, x); o << ")"; return o; }
template<class T1, class T2> ostream& operator<<(ostream& o, const pair<T1, T2>& x) { o << tie(x.first, x.second); return o; }
template<class T, enable_if_t<is_container<T>::value, int> = 0>
ostream& operator<<(ostream& o, const T& x) { o << "{"; for (auto it = x.begin(); it != x.end(); it++) { if (it != x.begin()) { o << ", "; } o << *it; } o << "}"; return o; }
}

// Main
void mainCase() {
  ll n; // <= 10^6
  cin >> n;
  vector<array<ll, 2>> qs(n, {0, 0}); // x <= 10^9
  cin >> qs;

  array<set<ll>, 2> sets;
  array<ll, 2> sums = {0, 0};
  set<ll> bigs, smalls;
  ll sum_bigs = 0, sum_smalls = 0;

  // Roughly track bigs/smalls and correct size later
  auto insert = [&](ll p) {
    if (bigs.empty() || *bigs.begin() > p) {
      smalls.insert(p);
      sum_smalls += p;
      return;
    }
    bigs.insert(p);
    sum_bigs += p;
  };

  auto erase = [&](ll p) {
    assert((bigs.count(p) || smalls.count(p)));
    if (bigs.count(p)) {
      bigs.erase(p);
      sum_bigs -= p;
      return;
    }
    smalls.erase(p);
    sum_smalls -= p;
  };

  // Move elements so that |big| = |sets[1]|
  auto correct = [&]() {
    int k = sets[1].size();
    while (k > (int)bigs.size()) { // smalls -> bigs
      int x = *smalls.rbegin();
      bigs.insert(x); sum_bigs += x;
      smalls.erase(x); sum_smalls -= x;
    }
    while (k < (int)bigs.size()) { // smalls <- bigs
      int x = *bigs.begin();
      bigs.erase(x); sum_bigs -= x;
      smalls.insert(x); sum_smalls += x;
    }
  };

  for (auto [t, q] : qs) {
    ll p = abs(q);
    if (q > 0) {
      sets[t].insert(p);
      insert(p);
    } else {
      sets[t].erase(p);
      erase(p);
    }
    sums[t] += q;
    correct();

    dbg(sets);
    dbgv(smalls, bigs);
    dbgv(sum_smalls, sum_bigs);

    // Double "bigs"
    ll res = sums[0] + sums[1] + sum_bigs;

    // But if "bigs" are all lightinings
    if (sets[1].size() > 0 && *sets[1].begin() == *bigs.begin()) {
      res -= *sets[1].begin(); // we don't double smallest lightning
      if (sets[0].size() > 0) {
        res += *sets[0].rbegin(); // we should double largest fire
      }
    }
    cout << res << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  mainCase();
  return 0;
  // [ Multiple cases ]
  // int t;
  // cin >> t;
  // FOR(i, 0, t) { mainCase(); }
  // return 0;
}

/*
python misc/run.py codeforces/edu93/e/main.cpp --check

%%%% begin
6
1 5
0 10
1 -5
0 5
1 11
0 -10
%%%%
5
25
10
15
36
21
%%%% end
*/
