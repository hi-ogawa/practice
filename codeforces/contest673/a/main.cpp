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
  int n; // [1, 3 x 10^5]
  cin >> n;
  vector<int> ls(n); // [1, n]
  cin >> ls;

  vector<vector<int>> ps(n + 1);
  for (auto& ids : ps) { ids.push_back(-1); }
  FOR(i, 0, n) {
    ps[ls[i]].push_back(i);
  }
  for (auto& ids : ps) { ids.push_back(n); }

  // Get maximum separation of each types
  const int kInf = 1e9;
  vector<int> res(n + 2, kInf);
  FOR(x, 1, n + 1) {
    auto& ids = ps[x];
    int t = 0;
    FOR(i, 0, (int)ids.size() - 1) {
      t = max(t, ids[i + 1] - ids[i]);
    }
    res[t] = min(res[t], x);
  }

  // Cum min
  FOR(i, 0, n) { res[i + 1] = min(res[i + 1], res[i]); }

  FOR(i, 1, n + 1) {
    cout << (res[i] == kInf ? -1 : res[i]) << " \n"[i == n];
  }
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  FOR(i, 0, t) { mainCase(); }
  return 0;
}

/*
python misc/run.py codeforces/contest673/a/main.cpp --check

%%%% begin
3
5
1 2 3 4 5
5
4 4 4 4 2
6
1 3 1 5 3 1
%%%%
-1 -1 3 2 1
-1 4 4 4 2
-1 -1 1 1 1 1
%%%% end
*/
