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
  int n;
  cin >> n;
  vector<ll> ls(n);
  cin >> ls;

  // Special case
  if (n == 1) {
    cout << "1 1" << endl;
    cout << "0" << endl;
    cout << "1 1" << endl;
    cout << "0" << endl;
    cout << "1 1" << endl;
    cout << -ls[0] << endl;
    return;
  }

  //
  // Noting n - 1 = -1 \in Zn, we have
  //
  //   a1, a2, ..., an-1, an
  //   -----------------
  //    0, a2, ..., an-1,     \in Zn
  //
  //       -----------------
  //        0, ...,    0,  0  \in Zn
  //   ---------------------
  //    0,  0, ...,    0,  0  \in Z
  //
  vector<ll> res1(n), res2(n), res3(n);

  dbg(ls);
  {
    // 1 .. n-1
    ll k = (ls[0] % n) * (n - 1);
    res1[0] = k;
    ls[0] += k;
  }
  dbg(ls);
  {
    // 2 .. n
    FOR(i, 1, n) {
      ll k = (ls[i] % n) * (n - 1);
      res2[i] = k;
      ls[i] += k;
    }
  }
  dbg(ls);
  {
    // 1 .. n
    FOR(i, 0, n) {
      res3[i] -= ls[i];
    }
  }
  dbg(res1);
  dbg(res2);
  dbg(res3);

  vector<tuple<int, int, vector<ll>>> res(3);
  res[0] = {0, n - 1, res1};
  res[1] = {1, n, res2};
  res[2] = {0, n, res3};
  dbg2(res);

  FOR(j, 0, 3) {
    auto& [i0, i1, v] = res[j];
    cout << (i0 + 1) << " " << i1 << endl;
    FOR(i, i0, i1) {
      if (i > i0) cout << " ";
      cout << v[i];
    }
    cout << endl;
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
python misc/run.py codeforces/contest666/div2/c/main.cpp --check

%%%% begin
4
1 3 2 4
%%%%
1 1
-1
3 4
4 2
2 4
-3 -6 -6
%%%% end
*/
