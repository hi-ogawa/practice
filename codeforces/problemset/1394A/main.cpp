// WA

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
  int n, d, m;
  cin >> n >> d >> m;
  vector<ll> ls(n);
  cin >> ls;

  // Partition
  sort(ALL(ls));
  auto ls_part = upper_bound(ALL(ls), m);
  vector<ll> ls1(ls.begin(), ls_part);
  vector<ll> ls2(ls_part, ls.end());
  int n1 = ls1.size(), n2 = ls2.size();
  reverse(ALL(ls2));
  dbg(ls1);
  dbg(ls2);

  // Cumsum
  vector<ll> ps1(n1 + 1), ps2(n2 + 1);
  FOR(i, 0, n1) { ps1[i + 1] = ps1[i] + ls1[i]; }
  FOR(i, 0, n2) { ps2[i + 1] = ps2[i] + ls2[i]; }
  dbg(ps1);
  dbg(ps2);

  if (n2 == 0) { cout << ps1[n1] << endl; return; }

  // Replace "c.d" from ls1 with "c" from ls2
  int c_res = 0;
  int c1 = min(n1 / d, n2 - 1);
  FOR(c, 1, c1 + 1) {
    ll a = ps1[c * d]; // smaller "c.d"
    ll b = ps2[c + 1] - ps2[1]; // larger "c" except largest
    if (a >= b) { break; }
    c_res = c;
  }
  dbg(c_res);

  // TODO: can do something about "left over ls1" even if not "d" block

  ll res = 0;
  res += ps1[n1] - ps1[c_res * d];
  res += ps2[c_res + 1];
  cout << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1394A/main.cpp --check

%%%% begin
5 2 11
8 10 15 23 5
%%%%
48
%%%% end

%%%% begin
20 2 16
20 5 8 2 18 16 2 16 16 1 5 16 2 13 6 16 4 17 21 7
%%%%
195
%%%% end
*/
