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
  int n; // [1, 10^4]
  cin >> n;
  vector<int> ls(n); // [1, 10^4]
  cin >> ls;

  // PROP. solvable \iff n | sum
  int total = accumulate(ALL(ls), 0);
  if (total % n != 0) { cout << -1 << "\n"; return; }

  vector<array<int, 3>> res;

  // Move everything to a[1] (this is possible since a[i] >= 1)
  FOR(i, 2, n + 1) {
    int j = i - 1;
    // Move to a[i] so that i | a[i]
    int y = (i - ls[j] % i) % i;
    res.push_back({1, i, y});
    ls[0] -= y;
    ls[j] += y;
    // Move all back to a[1]
    assert(ls[0] >= 0);
    assert(ls[j] % i == 0);
    int z = ls[j] / i;
    ls[0] += i * z;
    ls[j] -= i * z;
    res.push_back({i, 1, z});
  }
  dbg(ls);
  dbg(res);

  // Move "total / n" from a[1] to a[i]
  int avg = total / n;
  FOR(i, 2, n + 1) {
    int j = i - 1;
    ls[0] -= avg;
    ls[j] += avg;
    res.push_back({1, i, avg});
  }
  dbg(ls);
  dbgv(res);
  assert((int)res.size() == 3 * (n - 1));

  cout << res.size() << endl;
  for (auto r : res) {
    FOR(i, 0, 3) { cout << r[i] << " \n"[i == 2]; }
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
python misc/run.py codeforces/contest673/b/main.cpp --check

%%%% begin
3
4
2 16 4 18
6
1 2 3 4 5 6
5
11 19 1 1 3
%%%%
2
4 1 2
2 3 3
-1
4
1 2 4
2 4 5
2 3 3
4 5 1
%%%% end
*/
