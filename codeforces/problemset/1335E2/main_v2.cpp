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
  int n; // <= 2 x 10^5
  cin >> n;
  vector<int> ls(n);
  cin >> ls;
  int k = *max_element(ALL(ls)); // <= 200

  vector<int> cnts(k + 1);
  for (auto x : ls) { cnts[x]++; }

  int res = *max_element(ALL(cnts));
  FOR(v0, 0, k + 1) {
    auto cnts_tmp = cnts;
    int c = 0;
    int i = 0, j = n - 1;
    while (true) {
      c++;
      while (i < n && ls[i] != v0) {
        cnts_tmp[ls[i]]--;
        i++;
      }
      while (j > i && ls[j] != v0) {
        cnts_tmp[ls[j]]--;
        j--;
      }
      if (i >= j) { break; }
      FOR(v1, 0, k + 1) {
        if (v1 == v0) { continue; }
        int cc = cnts_tmp[v1];
        res = max(res, 2 * c + cc); // NOTE: this hits O(n.k) times (not O(n.k^2))
      }
      i++; j--;
    }
  }
  cout << res << endl;
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
python misc/run.py codeforces/problemset/1335E2/main_v2.cpp --check

%%%% begin
1
6
1 5 6 3 2 3
%%%%
3
%%%% end

%%%% begin
1
8
1 1 2 2 3 2 1 1
%%%%
7
%%%% end

%%%% begin
6
8
1 1 2 2 3 2 1 1
3
1 3 3
4
1 10 10 1
1
26
2
2 1
3
1 1 1
%%%%
7
2
4
1
1
3
%%%% end
*/
