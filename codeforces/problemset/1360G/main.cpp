// AC

// NOTE: see main_v2.cpp for provable construction

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
  int n, m, a, b;
  cin >> n >> m >> a >> b;

  // TODO: is this sufficient?
  bool ok = n * a == m * b;
  if (!ok) {
    cout << "NO" << endl; return;
  }

  //
  // CONJ.
  //  such construction exists.
  //
  vector<vector<int>> res(n, vector<int>(m, 0));
  vector<int> cnts(m, 0);
  FOR(i, 0, n) {
    FOR(j, 0, a) {
      res[i][j] = 1;
    }
  }
  FOR(j, 0, m) {
    cnts[j] = j < a ? n : 0;
  }
  dbg(cnts);
  dbg2(res);

  FOR(j, 0, m) {
    while (cnts[j] > b) {
      FOR(i, 0, n) {
        if (res[i][j] == 1) {
          FOR(jj, j + 1, m) {
            if (res[i][jj] == 0) {
              swap(res[i][j], res[i][jj]);
              cnts[j]--;
              cnts[jj]++;
              break;
            }
          }
        }
        if (cnts[j] == b) { break; }
      }
    }
  }
  dbg(cnts);
  dbg2(res);

  cout << "YES" << endl;
  FOR(i, 0, n) {
    FOR(j, 0, m) {
      cout << res[i][j];
    }
    cout << endl;
  }
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
python misc/run.py codeforces/problemset/1360G/main.cpp --check

%%%% begin
1
7 7 6 6
%%%%
%%%% end

%%%% begin
1
3 6 2 1
%%%%
%%%% end

%%%% begin
5
3 6 2 1
2 2 2 1
2 2 2 2
4 4 2 2
2 1 1 2
%%%%
YES
010001
100100
001010
NO
YES
11
11
YES
1100
1100
0011
0011
YES
1
1
%%%% end
*/
