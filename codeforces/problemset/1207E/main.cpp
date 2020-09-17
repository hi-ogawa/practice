// AC

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
  const int n = 100;
  vector<int> ls1(n), ls2(n);

  //
  // PROP.
  //    x =  ls1[i] ^ p1 = ls2[j] ^ p2 <=> ls1[i] ^ ls2[j] = p1 ^ p2
  //

  // Generate ls1, ls2 s.t.
  //   (i, j) != (ii, jj)  ==>  ls1[i] ^ ls2[j] != ls1[ii] ^ ls2[jj]
  FOR(i, 0, n) {
    ls1[i] = (i + 1);      // [1, 101]   0000000*******
    ls2[i] = (i + 1) << 7; //            *******0000000
  }

  // Query
  int p1;
  cout << "?";
  for (auto x : ls1) { cout << " " << x; }
  cout << endl;
  cin >> p1;

  int p2;
  cout << "?";
  for (auto x : ls2) { cout << " " << x; }
  cout << endl;
  cin >> p2;

  // Answer
  vector<int> ps1(n), ps2(n);
  FOR(i, 0, n) { ps1[i] = p1 ^ ls1[i]; }
  FOR(i, 0, n) { ps2[i] = p2 ^ ls2[i]; }

  vector<int> isect;
  sort(ALL(ps1));
  sort(ALL(ps2));
  set_intersection(ALL(ps1), ALL(ps2), back_inserter(isect));
  assert(isect.size() == 1);

  int res = isect[0];
  cout << "! " << res << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  mainCase();
  return 0;
}

/*
python misc/run.py codeforces/problemset/1207E/main.cpp --check
*/
