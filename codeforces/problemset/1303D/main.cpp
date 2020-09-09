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
  ll n, m; // n <= 10^18, m <= 10^5
  cin >> n >> m;
  vector<ll> ls(m);
  cin >> ls;

  const int lim = 60;
  // const int lim = 10; // [ for debug ]
  vector<int> bs(lim);
  FOR(i, 0, lim) {
    bs[i] += bool(n & (1LL << i));
  }
  dbg(bs);

  vector<int> ps(lim);
  FOR(i, 0, m) {
    FOR(j, 0, lim) {
      ps[j] += bool(ls[i] & (1LL << j));
    }
  }
  dbg(ps);

  // Solve from LSB
  bool ok = 1;
  int res = 0;
  FOR(i, 0, lim) {
    dbgv(i, ps);
    if (bs[i] == 1) {
      // Find smallest match
      int j0 = -1;
      FOR(j, i, lim) {
        if (ps[j] > 0) { j0 = j; break; }
      }
      if (j0 == -1) { ok = 0; break; } // not found

      // Split if large
      for (int j = j0; j > i; j--) {
        ps[j]--;
        ps[j - 1] += 2;
        res++;
      }
      ps[i]--;
    }
    // Carry what's left
    if (i < lim - 1) {
      ps[i + 1] += ps[i] / 2;
    }
  }
  dbgv(ok, res);

  cout << (ok ? res : -1) << endl;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  // [ Single case ]
  // mainCase();
  // return 0;
  // [ Multiple cases ]
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/problemset/1303D/main.cpp --check

%%%% begin
3
10 3
1 32 1
23 4
16 1 4 1
20 5
2 1 16 1 8
%%%%
2
-1
0
%%%% end
*/
